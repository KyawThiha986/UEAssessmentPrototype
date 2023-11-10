// Fill out your copyright notice in the Description page of Project Settings.


#include "GripPickup.h"

#include "PickupManagerSubsystem.h"
#include "../Characters/PlayerCharacter.h"
#include "Net/UnrealNetwork.h"

void AGripPickup::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		GenerateGripPickup();
	}
	UpdateGripPickupMaterial();
}

void AGripPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		Player->EquipGrip(GripStats);
		// We only want to delete it in the authority version.
		if (GetLocalRole() == ROLE_Authority)
		{
			// Get the PickupManager subsystem.
			if (UPickupManagerSubsystem* PickupManager = GetWorld()->GetSubsystem<UPickupManagerSubsystem>())
			{
				PickupManager->PickupConsumed(this);
			}
		}
	}
}

void AGripPickup::GenerateGripPickup()
{GripRarity = GripRarityPicker();
	TArray<bool> GoodStats;
	switch (GripRarity)
	{
	case ERarity::Legendary:
		GripStats.FireRate = FMath::RandRange(0.11f, 0.15f);
		GoodStats = GripStatPicker(2, 5);
		break;
	case ERarity::Master:
		GripStats.FireRate = FMath::RandRange(0.1f, 0.14f);
		GoodStats = GripStatPicker(1, 5);
		break;
	case ERarity::Rare:
		GripStats.FireRate = FMath::RandRange(0.05f, 0.09f);
		GoodStats = GripStatPicker(1, 5);
		break;
	default:
		GripStats.FireRate = FMath::RandRange(0.04f, 0.08f);
		GoodStats = GripStatPicker(0, 5);
		break;
	}

	GripStats.Accuracy += GoodStats[0] ? FMath::RandRange(0.004f, 0.008f) : 0.0f;
	GripStats.FireRate += GoodStats[1] ? FMath::RandRange(0.04f, 0.08f) : 0.0f;
	GripStats.BaseDamage += GoodStats[2] ? FMath::RandRange(3.0f, 6.0f) : 0.0f;
	GripStats.MagazineSize += GoodStats[3] ? FMath::RandRange(3, 6) : 0;
	GripStats.ReloadTime += GoodStats[4] ? FMath::RandRange(0.3f, 0.5f) : 0.0f;
}

ERarity AGripPickup::GripRarityPicker()
{
	// Rules:
	// 50% chance of Common
	// 30% chance of Rare
	// 15% chance of Master
	// 5% chance of Legendary
	const float RandPercent = FMath::RandRange(0.0f, 1.0f);
	
	if (RandPercent <= 0.5f)
	{
		return ERarity::Common;
	}
	if (RandPercent <= 0.8f)
	{
		return ERarity::Rare;
	}
	if (RandPercent <= 0.95f)
	{
		return ERarity::Master;
	}
	
	return ERarity::Legendary;
}

TArray<bool> AGripPickup::GripStatPicker(int32 NumOfGood, int32 NumOfStats)
{
	// Fill the array with the correct number of good and bad stats.
	TArray<bool> GoodStats;
	for (int32 i = 0; i < NumOfStats; i++)
	{
		// Ternary condition: Will add true if I < NumOfGood otherwise add false.
		GoodStats.Add(i < NumOfGood ? true : false);
	}

	// Array shuffling algorithm.
	for (int32 i = 0; i < GoodStats.Num(); i++)
	{
		// Get a random index from the GoodStats array.
		const int32 RandIndex = FMath::RandRange(0, GoodStats.Num() - 1);
		// Then swap the item at that random index with the item in the i index.
		const bool Temp = GoodStats[i];
		GoodStats[i] = GoodStats[RandIndex];
		GoodStats[RandIndex] = Temp;
	}

	return GoodStats;
}