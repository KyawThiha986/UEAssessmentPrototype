// Fill out your copyright notice in the Description page of Project Settings.


#include "MagazinePickup.h"

#include "PickupManagerSubsystem.h"
#include "../Characters/PlayerCharacter.h"
#include "Net/UnrealNetwork.h"

void AMagazinePickup::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ROLE_Authority)
	{
		GenerateMagazinePickup();
	}
	UpdateMagazinePickupMaterial();
}

void AMagazinePickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	//Super::OnPickupOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, HitInfo);
	// UE_LOG(LogTemp, Display, TEXT("Overlap event occurred on WeaponPickup"))

	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		Player->EquipMagazine(MagazineStats);
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

void AMagazinePickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMagazinePickup, MagazineRarity);
	DOREPLIFETIME(AMagazinePickup, MagazineStats);
}

void AMagazinePickup::GenerateMagazinePickup()
{MagazineRarity = MagazineRarityPicker();
	TArray<bool> GoodStats;
	switch (MagazineRarity)
	{
	case EMagazineRarity::Legendary:
		MagazineStats.MagazineSize = FMath::RandRange(9, 12);
		GoodStats = MagazineStatPicker(2, 5);
		break;
	case EMagazineRarity::Master:
		MagazineStats.MagazineSize = FMath::RandRange(8, 11);
		GoodStats = MagazineStatPicker(1, 5);
		break;
	case EMagazineRarity::Rare:
		MagazineStats.MagazineSize = FMath::RandRange(4, 7);
		GoodStats = MagazineStatPicker(1, 5);
		break;
	default:
		MagazineStats.MagazineSize = FMath::RandRange(3, 6);
		GoodStats = MagazineStatPicker(0, 5);
		break;
	}

	MagazineStats.Accuracy += GoodStats[0] ? FMath::RandRange(0.004f, 0.008f) : 0.0f;
	MagazineStats.FireRate += GoodStats[1] ? FMath::RandRange(0.04f, 0.08f) : 0.0f;
	MagazineStats.BaseDamage += GoodStats[2] ? FMath::RandRange(3.0f, 6.0f) : 0.0f;
	MagazineStats.MagazineSize += GoodStats[3] ? FMath::RandRange(3, 6) : 0;
	MagazineStats.ReloadTime += GoodStats[4] ? FMath::RandRange(0.3f, 0.5f) : 0.0f;
}

EMagazineRarity AMagazinePickup::MagazineRarityPicker()
{
	// Rules:
	// 50% chance of Common
	// 30% chance of Rare
	// 15% chance of Master
	// 5% chance of Legendary
	const float RandPercent = FMath::RandRange(0.0f, 1.0f);
	
	if (RandPercent <= 0.5f)
	{
		return EMagazineRarity::Common;
	}
	if (RandPercent <= 0.8f)
	{
		return EMagazineRarity::Rare;
	}
	if (RandPercent <= 0.95f)
	{
		return EMagazineRarity::Master;
	}
	
	return EMagazineRarity::Legendary;
}

TArray<bool> AMagazinePickup::MagazineStatPicker(int32 NumOfGood, int32 NumOfStats)
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