// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupManagerSubsystem.h"

#include "BarrelPickup.h"
#include "GripPickup.h"
#include "MagazinePickup.h"
#include "SightPickup.h"
#include "StockPickup.h"
#include "WeaponPickup.h"
#include "AGP/AGPGameInstance.h"
#include "AGP/Pathfinding/PathfindingSubsystem.h"



void UPickupManagerSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// We don't want this pickup manager to do any spawning if it isn't
	// on the server.
	// A value < NM_Client is any type of server. So if it is >=
	// to NM_Client or == NM_Client then we know it is the client
	// and we don't want to spawn.
	if (GetWorld()->GetNetMode() >= NM_Client)
	{
		return;
	}

	if (PossibleSpawnLocations.IsEmpty())
	{
		PopulateSpawnLocations();
	}

	TimeSinceLastSpawn += DeltaTime;
	if (TimeSinceLastSpawn >= PickupSpawnRate)
	{
		SpawnWeaponPickup();
		TimeSinceLastSpawn = 0.0f;
	}
}

void UPickupManagerSubsystem::SpawnWeaponPickup()
{
	if (PossibleSpawnLocations.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to spawn weapon pickup."))
		return;
	}
	
	if (const UAGPGameInstance* GameInstance =
		GetWorld()->GetGameInstance<UAGPGameInstance>())
	{
		int32 Index = FMath::RandRange(0, PossibleSpawnLocations.Num()-1);
		FVector SpawnPosition = PossibleSpawnLocations[Index];
		SpawnPosition.Z += 50.0f;
		int32 PickPool = FMath::RandRange(1, 6);

		// If the map contains a pickup at this index key then destroy it.
		// Otherwise get the map ready to store the about to be spawned pickup.
		if (SpawnedPickups.Contains(Index))
		{
			// Destroy the WeaponPickup at that location in the Map if one already exists.
			GetWorld()->DestroyActor(SpawnedPickups[Index]);
			SpawnedPickups[Index] = nullptr;
		} else
		{
			// If it doesn't exist, then add a section to the map that includes this Index position.
			SpawnedPickups.Add(Index, nullptr);
		}

		// Now we are here, we know that there is a free slot at the given Index key position to spawn a new
		// weapon pickup.
		switch(PickPool)
		{
		default:
			SpawnedPickups[Index] = GetWorld()->SpawnActor<AWeaponPickup>(
			GameInstance->GetWeaponPickupClass(), SpawnPosition, FRotator::ZeroRotator);
			break;
		case 1:
			SpawnedPickups[Index] = GetWorld()->SpawnActor<AWeaponPickup>(
			GameInstance->GetWeaponPickupClass(), SpawnPosition, FRotator::ZeroRotator);
			break;
		case 2:
			SpawnedPickups[Index] = GetWorld()->SpawnActor<ABarrelPickup>(
			GameInstance->GetBarrelPickupClass(), SpawnPosition, FRotator::ZeroRotator);
			break;
		case 3:
			SpawnedPickups[Index] = GetWorld()->SpawnActor<ASightPickup>(
			GameInstance->GetSightPickupClass(), SpawnPosition, FRotator::ZeroRotator);
			break;
		case 4:
			SpawnedPickups[Index] = GetWorld()->SpawnActor<AMagazinePickup>(
			GameInstance->GetMagazinePickupClass(), SpawnPosition, FRotator::ZeroRotator);
			break;
		case 5:
			SpawnedPickups[Index] = GetWorld()->SpawnActor<AGripPickup>(
			GameInstance->GetGripPickupClass(), SpawnPosition, FRotator::ZeroRotator);
			break;
		case 6:
			SpawnedPickups[Index] = GetWorld()->SpawnActor<AStockPickup>(
			GameInstance->GetStockPickupClass(), SpawnPosition, FRotator::ZeroRotator);
			break;
		}
	}
}

void UPickupManagerSubsystem::PickupConsumed(APickupBase* Pickup)
{
	int32 IndexToRemove = -1;
	// Find the pickup in the map
	for (auto IndexPickupPair : SpawnedPickups)
	{
		if (IndexPickupPair.Value == Pickup)
		{
			GetWorld()->DestroyActor(IndexPickupPair.Value);
			IndexToRemove = IndexPickupPair.Key;
			break;
		}
	}
	// Some fail state that occurs if it can't find the weapon pickup.
	if (IndexToRemove == -1)
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't find a pickup in the SpawnedPickup map. This shouldn't happen."));
		return;
	}

	SpawnedPickups.Remove(IndexToRemove);
}

void UPickupManagerSubsystem::PopulateSpawnLocations()
{
	PossibleSpawnLocations.Empty();
	if (const UPathfindingSubsystem* PathfindingSubsystem = GetWorld()->GetSubsystem<UPathfindingSubsystem>())
	{
		PossibleSpawnLocations = PathfindingSubsystem->GetWaypointPositions();
	}
}
