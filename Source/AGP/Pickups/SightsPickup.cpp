// Fill out your copyright notice in the Description page of Project Settings.


#include "SightsPickup.h"

#include "../Characters/PlayerCharacter.h"

void ASightsPickup::BeginPlay()
{
	Super::BeginPlay();
	GenerateSightsPickup();
	UpdateSightsPickupMaterial();
}

void ASightsPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	//Super::OnPickupOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, HitInfo);
	// UE_LOG(LogTemp, Display, TEXT("Overlap event occurred on WeaponPickup"))

	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		Player->EquipSights(SightsPickupStats);
		Destroy();
	}
}

void ASightsPickup::GenerateSightsPickup()
{
	float Odds = FMath::RandRange(0, 100);

	if(Odds <= 5.0f)
	{
		SightsRarity = ESightsRarity::Legendary;
		SightsPickupStats.Accuracy = FMath::RandRange(0.022f, 0.03f);
		MaxBonusRoll = 2;
		RollBonuses();
	}

	else if(Odds > 5.0f && Odds <= 20.0f)
	{
		SightsRarity = ESightsRarity::Master;
		SightsPickupStats.Accuracy = FMath::RandRange(0.02f, 0.028f);
		MaxBonusRoll = 1;
		RollBonuses();
	}

	else if(Odds > 20.0f && Odds <= 50.0f)
	{
		SightsRarity = ESightsRarity::Rare;
		SightsPickupStats.Accuracy = FMath::RandRange(0.01f, 0.018f);
		MaxBonusRoll = 1;
		RollBonuses();
	}

	else
	{
		SightsRarity = ESightsRarity::Common;
		SightsPickupStats.Accuracy = FMath::RandRange(0.008f, 0.016f);
	}

	//Determine the stats depending on whether it is good or bad
}

void ASightsPickup::RollBonuses()
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
				SightsPickupStats.Accuracy += FMath::RandRange(0.008f, 0.016f);
				AccuracyUp = true;
				BonusRoll += 1;
				break;
			}
			if (BonusPick == 2 && FireRateUp == false)
			{
				SightsPickupStats.FireRate += FMath::RandRange(0.05f, 0.1f);
				FireRateUp = true;
				BonusRoll += 1;
				break;
				
			}
			if (BonusPick == 3 && DamageUp == false)
			{
				SightsPickupStats.BaseDamage += FMath::RandRange(4.0f, 8.0f);
				DamageUp = true;
				BonusRoll += 1;
				break;
			}
			if (BonusPick == 4 && MagSizeUp == false)
			{
				SightsPickupStats.MagazineSize += FMath::RandRange(3, 6);
				MagSizeUp = true;
				BonusRoll += 1;
				break;
			}
			if (BonusPick == 5 && ReloadTimeUp == false)
			{
				SightsPickupStats.ReloadTime += FMath::RandRange(0.4f, 0.8f);
				ReloadTimeUp = true;
				BonusRoll += 1;
				break;
			}
		}		
	}
}
