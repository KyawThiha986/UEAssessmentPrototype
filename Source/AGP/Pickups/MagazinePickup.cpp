// Fill out your copyright notice in the Description page of Project Settings.


#include "MagazinePickup.h"

#include "../Characters/PlayerCharacter.h"

void AMagazinePickup::BeginPlay()
{
	Super::BeginPlay();
	GenerateMagazinePickup();
	UpdateMagazinePickupMaterial();
}

void AMagazinePickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	//Super::OnPickupOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, HitInfo);
	// UE_LOG(LogTemp, Display, TEXT("Overlap event occurred on WeaponPickup"))

	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		Player->EquipMagazine(MagazinePickupStats);
		Destroy();
	}
}

void AMagazinePickup::GenerateMagazinePickup()
{
	float Odds = FMath::RandRange(0, 100);

	if(Odds <= 5.0f)
	{
		MagazineRarity = EMagazineRarity::Legendary;
		MagazinePickupStats.MagazineSize = FMath::RandRange(9, 12);
		MaxBonusRoll = 2;
		RollBonuses();
	}

	else if(Odds > 5.0f && Odds <= 20.0f)
	{
		MagazineRarity = EMagazineRarity::Master;
		MagazinePickupStats.MagazineSize = FMath::RandRange(8, 11);
		MaxBonusRoll = 1;
		RollBonuses();
	}

	else if(Odds > 20.0f && Odds <= 50.0f)
	{
		MagazineRarity = EMagazineRarity::Rare;
		MagazinePickupStats.MagazineSize = FMath::RandRange(4, 7);
		MaxBonusRoll = 1;
		RollBonuses();
	}

	else
	{
		MagazineRarity = EMagazineRarity::Common;
		MagazinePickupStats.MagazineSize = FMath::RandRange(0.4f, 0.8f);
	}

	//Determine the stats depending on whether it is good or bad
}

void AMagazinePickup::RollBonuses()
{
	int32 BonusPick;
	int32 BonusRoll = 1;

	while (BonusRoll <= MaxBonusRoll)
	{
		while (true)
		{
			BonusPick = FMath::RandRange(1, 5);
			if (BonusPick == 1)
			{
				MagazinePickupStats.Accuracy += FMath::RandRange(0.008f, 0.016f);
				BonusRoll += 1;
				break;
			}
			if (BonusPick == 2)
			{
				MagazinePickupStats.FireRate += FMath::RandRange(0.05f, 0.1f);
				BonusRoll += 1;
				break;
				
			}
			if (BonusPick == 3)
			{
				MagazinePickupStats.BaseDamage += FMath::RandRange(4.0f, 8.0f);
				BonusRoll += 1;
				break;
			}
			if (BonusPick == 4)
			{
				MagazinePickupStats.MagazineSize += FMath::RandRange(3, 6);
				BonusRoll += 1;
				break;
			}
			if (BonusPick == 5)
			{
				MagazinePickupStats.ReloadTime += FMath::RandRange(0.15f, 0.3f);
				BonusRoll += 1;
				break;
			}
		}		
	}
}
