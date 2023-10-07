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
		MagazinePickupStats.MagazineSize = FMath::RandRange(3, 6);
	}

	//Determine the stats depending on whether it is good or bad
}

void AMagazinePickup::RollBonuses()
{
	int32 BonusPick;
	int32 BonusRoll = 1;

	//booleans to ensure the same bonus rolls are never picked twice
	bool AccuracyUp = false;
	bool FireRateUp = false;
	bool DamageUp = false;
	bool MagSizeUp = false;
	bool ReloadTimeUp = false;

	//Until the bonus roll exceeds the maximum roll, randomly pick one of the five additional bonus stats to apply for the pickup
	while (BonusRoll <= MaxBonusRoll)
	{
		while (true)
		{
			BonusPick = FMath::RandRange(1, 5);
			if (BonusPick == 1 && AccuracyUp == false)
			{
				MagazinePickupStats.Accuracy += FMath::RandRange(0.008f, 0.016f);
				BonusRoll += 1;
				AccuracyUp = true;
				break;
			}
			if (BonusPick == 2 && FireRateUp == false)
			{
				MagazinePickupStats.FireRate += FMath::RandRange(0.05f, 0.1f);
				BonusRoll += 1;
				FireRateUp = true;
				break;
				
			}
			if (BonusPick == 3 && DamageUp == false)
			{
				MagazinePickupStats.BaseDamage += FMath::RandRange(4.0f, 8.0f);
				BonusRoll += 1;
				DamageUp = true;
				break;
			}
			if (BonusPick == 4 && MagSizeUp == false)
			{
				MagazinePickupStats.MagazineSize += FMath::RandRange(3, 6);
				BonusRoll += 1;
				MagSizeUp = true;
				break;
			}
			if (BonusPick == 5 && ReloadTimeUp == false)
			{
				MagazinePickupStats.ReloadTime += FMath::RandRange(0.4f, 0.8f);
				BonusRoll += 1;
				ReloadTimeUp = true;
				break;
			}
		}		
	}
}
