// Fill out your copyright notice in the Description page of Project Settings.


#include "SightPickup.h"

#include "PickupManagerSubsystem.h"
#include "../Characters/PlayerCharacter.h"
#include "Net/UnrealNetwork.h"

void ASightPickup::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		GenerateSightPickup();
	}
	UpdateSightPickupMaterial();
}

void ASightPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	//Super::OnPickupOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, HitInfo);
	// UE_LOG(LogTemp, Display, TEXT("Overlap event occurred on WeaponPickup"))

	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		Player->EquipSight(SightStats);
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

void ASightPickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASightPickup, SightRarity);
	DOREPLIFETIME(ASightPickup, SightStats);
}

void ASightPickup::GenerateSightPickup()
{SightRarity = SightRarityPicker();
	TArray<bool> GoodStats;
	switch (SightRarity)
	{
	case ESightRarity::Legendary:
		SightStats.Accuracy = FMath::RandRange(0.011f, 0.015f);
		GoodStats = SightStatPicker(2, 5);
		break;
	case ESightRarity::Master:
		SightStats.Accuracy = FMath::RandRange(0.01f, 0.014f);
		GoodStats = SightStatPicker(1, 5);
		break;
	case ESightRarity::Rare:
		SightStats.Accuracy = FMath::RandRange(0.005f, 0.009f);
		GoodStats = SightStatPicker(1, 5);
		break;
	default:
		SightStats.Accuracy = FMath::RandRange(0.004f, 0.008f);
		GoodStats = SightStatPicker(0, 5);
		break;
	}

	SightStats.Accuracy += GoodStats[0] ? FMath::RandRange(0.004f, 0.008f) : 0.0f;
	SightStats.FireRate += GoodStats[1] ? FMath::RandRange(0.04f, 0.08f) : 0.0f;
	SightStats.BaseDamage += GoodStats[2] ? FMath::RandRange(3.0f, 6.0f) : 0.0f;
	SightStats.MagazineSize += GoodStats[3] ? FMath::RandRange(3, 6) : 0;
	SightStats.ReloadTime += GoodStats[4] ? FMath::RandRange(0.3f, 0.5f) : 0.0f;
}

ESightRarity ASightPickup::SightRarityPicker()
{
	// Rules:
	// 50% chance of Common
	// 30% chance of Rare
	// 15% chance of Master
	// 5% chance of Legendary
	const float RandPercent = FMath::RandRange(0.0f, 1.0f);
	
	if (RandPercent <= 0.5f)
	{
		return ESightRarity::Common;
	}
	if (RandPercent <= 0.8f)
	{
		return ESightRarity::Rare;
	}
	if (RandPercent <= 0.95f)
	{
		return ESightRarity::Master;
	}
	
	return ESightRarity::Legendary;
}

TArray<bool> ASightPickup::SightStatPicker(int32 NumOfGood, int32 NumOfStats)
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