// Fill out your copyright notice in the Description page of Project Settings.


#include "GripPickup.h"

#include "../Characters/PlayerCharacter.h"

void AGripPickup::BeginPlay()
{
	Super::BeginPlay();
	GenerateGripPickup();
	UpdateGripPickupMaterial();
}

void AGripPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	//Super::OnPickupOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, HitInfo);
	// UE_LOG(LogTemp, Display, TEXT("Overlap event occurred on WeaponPickup"))

	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		Player->EquipGrip(GripPickupStats);
		Destroy();
	}
}

void AGripPickup::GenerateGripPickup()
{
	float Odds = FMath::RandRange(0, 100);

	if(Odds <= 5.0f)
	{
		GripRarity = EGripRarity::Legendary;
		GripPickupStats.FireRate += FMath::RandRange(0.21f, 0.24f);
		MaxBonusRoll = 2;
		RollBonuses();
	}

	else if(Odds > 5.0f && Odds <= 20.0f)
	{
		GripRarity = EGripRarity::Master;
		GripPickupStats.FireRate += FMath::RandRange(0.16f, 0.21f);
		MaxBonusRoll = 1;
		RollBonuses();
	}

	else if(Odds > 20.0f && Odds <= 50.0f)
	{
		GripRarity = EGripRarity::Rare;
		GripPickupStats.FireRate += FMath::RandRange(0.08f, 0.13f);
		MaxBonusRoll = 1;
		RollBonuses();
	}

	else
	{
		GripRarity = EGripRarity::Common;
		GripPickupStats.FireRate += FMath::RandRange(0.05f, 0.1f);
	}

	//Determine the stats depending on whether it is good or bad
}

void AGripPickup::RollBonuses()
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
				GripPickupStats.Accuracy += FMath::RandRange(0.008f, 0.016f);
				BonusRoll += 1;
				AccuracyUp = true;
				break;
			}
			if (BonusPick == 2 && FireRateUp == false)
			{
				GripPickupStats.FireRate += FMath::RandRange(0.05f, 0.1f);
				BonusRoll += 1;
				FireRateUp = true;
				break;
				
			}
			if (BonusPick == 3 && DamageUp == false)
			{
				GripPickupStats.BaseDamage += FMath::RandRange(4.0f, 8.0f);
				BonusRoll += 1;
				DamageUp = true;
				break;
			}
			if (BonusPick == 4 && MagSizeUp == false)
			{
				GripPickupStats.MagazineSize += FMath::RandRange(3, 6);
				BonusRoll += 1;
				MagSizeUp = true;
				break;
			}
			if (BonusPick == 5 && ReloadTimeUp == false)
			{
				GripPickupStats.ReloadTime += FMath::RandRange(0.4f, 0.8f);
				BonusRoll += 1;
				ReloadTimeUp = true;
				break;
			}
		}		
	}
}

