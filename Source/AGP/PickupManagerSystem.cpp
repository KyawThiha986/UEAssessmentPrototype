// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupManagerSystem.h"

#include "AGPGameInstance.h"
#include "Pathfinding/PathfindingSubsystem.h"

//Retrieve waypoint positions and set them as possible pickup spawns
void UPickupManagerSystem::PopulateSpawnLocations()
{
	PossibleSpawnLocations.Empty();

	UPathfindingSubsystem* WaypointPos;
	WaypointPos = GetWorld()->GetSubsystem<UPathfindingSubsystem>();
	PossibleSpawnLocations = WaypointPos -> GetWaypointPositions();
}

void UPickupManagerSystem::SpawnPickups()
{
	//If possible spawn locations array is empty, write a log and return nothing
	if (PossibleSpawnLocations.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to spawn pickups."))
		return;
	}
	//Otherwise, Spawn pickups at a position designated by random range
	if (const UAGPGameInstance* GameInstance =
	GetWorld()->GetGameInstance<UAGPGameInstance>())
	{
		FVector SpawnPosition =
		PossibleSpawnLocations[FMath::RandRange(0, PossibleSpawnLocations.Num()-
		1)];
		SpawnPosition.Z += 50.0f;
		
		AWeaponPickup* WeaponPickup = GetWorld()->SpawnActor<AWeaponPickup>(
		GameInstance->GetWeaponPickupClass(),SpawnPosition,FRotator::ZeroRotator);

		SpawnPosition = PossibleSpawnLocations[FMath::RandRange(0, PossibleSpawnLocations.Num()-
		1)];
		SpawnPosition.Z += 50.0f;

		ABarrelPickup* BarrelPickup = GetWorld()->SpawnActor<ABarrelPickup>(
		GameInstance->GetBarrelPickupClass(),SpawnPosition,FRotator::ZeroRotator);

		SpawnPosition = PossibleSpawnLocations[FMath::RandRange(0, PossibleSpawnLocations.Num()-
		1)];
		SpawnPosition.Z += 50.0f;

		ASightsPickup* SightsPickup = GetWorld()->SpawnActor<ASightsPickup>(
		GameInstance->GetSightsPickupClass(),SpawnPosition,FRotator::ZeroRotator);

		SpawnPosition = PossibleSpawnLocations[FMath::RandRange(0, PossibleSpawnLocations.Num()-
		1)];
		SpawnPosition.Z += 50.0f;

		AMagazinePickup* MagazinePickup = GetWorld()->SpawnActor<AMagazinePickup>(
		GameInstance->GetMagazinePickupClass(),SpawnPosition,FRotator::ZeroRotator);

		SpawnPosition = PossibleSpawnLocations[FMath::RandRange(0, PossibleSpawnLocations.Num()-
		1)];
		SpawnPosition.Z += 50.0f;

		AGripPickup* GripPickup = GetWorld()->SpawnActor<AGripPickup>(
		GameInstance->GetGripPickupClass(),SpawnPosition,FRotator::ZeroRotator);

		SpawnPosition = PossibleSpawnLocations[FMath::RandRange(0, PossibleSpawnLocations.Num()-
		1)];
		SpawnPosition.Z += 50.0f;

		AStockPickup* StockPickup = GetWorld()->SpawnActor<AStockPickup>(
		GameInstance->GetStockPickupClass(),SpawnPosition,FRotator::ZeroRotator);
	}
}

void UPickupManagerSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeSinceLastSpawn += DeltaTime;
	if(PossibleSpawnLocations.IsEmpty())
	{
		PopulateSpawnLocations();
	}
	if (TimeSinceLastSpawn > PickupSpawnRate)
	{
		SpawnPickups();
		TimeSinceLastSpawn = 0.0f;
	}
}
