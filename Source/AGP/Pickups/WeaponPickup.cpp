// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickup.h"

#include "PickupManagerSubsystem.h"
#include "../Characters/PlayerCharacter.h"
#include "Net/UnrealNetwork.h"

void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		GenerateWeaponPickup();
	}
	UpdateWeaponPickupMaterial();
}

void AWeaponPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	//Super::OnPickupOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, HitInfo);
	// UE_LOG(LogTemp, Display, TEXT("Overlap event occurred on WeaponPickup"))

	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		Player->EquipWeapon(true, WeaponStats);
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

void AWeaponPickup::GenerateWeaponPickup()
{
	WeaponRarity = WeaponRarityPicker();
	TArray<bool> GoodStats;
	switch (WeaponRarity)
	{
	case ERarity::Legendary:
		GoodStats = WeaponStatPicker(4, 5);
		break;
	case ERarity::Master:
		GoodStats = WeaponStatPicker(3, 5);
		break;
	case ERarity::Rare:
		GoodStats = WeaponStatPicker(2, 5);
		break;
	default:
		GoodStats = WeaponStatPicker(0, 5);
		break;
	}

	WeaponStats.Accuracy = GoodStats[0] ? FMath::RandRange(0.95f, 0.98f) : FMath::RandRange(0.9f, 0.95f);
	WeaponStats.FireRate = GoodStats[1] ? FMath::RandRange(0.1f, 0.3f) : FMath::RandRange(0.3f, 0.6f);
	WeaponStats.BaseDamage = GoodStats[2] ? FMath::RandRange(15.0f, 30.0f) : FMath::RandRange(5.0f, 15.0f);
	WeaponStats.MagazineSize = GoodStats[3] ? FMath::RandRange(15, 30) : FMath::RandRange(6, 15);
	WeaponStats.ReloadTime = GoodStats[4] ? FMath::RandRange(1.5f, 3.0f) : FMath::RandRange(2.5f, 4.0f);
}

ERarity AWeaponPickup::WeaponRarityPicker()
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

TArray<bool> AWeaponPickup::WeaponStatPicker(int32 NumOfGood, int32 NumOfStats)
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
