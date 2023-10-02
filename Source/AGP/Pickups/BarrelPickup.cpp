// Fill out your copyright notice in the Description page of Project Settings.


#include "BarrelPickup.h"

#include "../Characters/PlayerCharacter.h"

void ABarrelPickup::BeginPlay()
{
	Super::BeginPlay();
	GenerateBarrelPickup();
	UpdateBarrelPickupMaterial();
}

void ABarrelPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	//Super::OnPickupOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, HitInfo);
	// UE_LOG(LogTemp, Display, TEXT("Overlap event occurred on WeaponPickup"))

	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		Player->EquipBarrel(BarrelPickupStats);
		Destroy();
	}
}

void ABarrelPickup::GenerateBarrelPickup()
{
	float Odds = FMath::RandRange(0, 100);

	if(Odds <= 5.0f)
	{
		BarrelRarity = EBarrelRarity::Legendary;
		BarrelPickupStats.BaseDamage = FMath::RandRange(11.0f, 16.0f);
		MaxBonusRoll = 2;
		RollBonuses();
	}

	else if(Odds > 5.0f && Odds <= 20.0f)
	{
		BarrelRarity = EBarrelRarity::Master;
		BarrelPickupStats.BaseDamage = FMath::RandRange(10.0f, 14.0f);
		MaxBonusRoll = 1;
		RollBonuses();
	}

	else if(Odds > 20.0f && Odds <= 50.0f)
	{
		BarrelRarity = EBarrelRarity::Rare;
		BarrelPickupStats.BaseDamage = FMath::RandRange(5.0f, 9.0f);
		MaxBonusRoll = 1;
		RollBonuses();
	}

	else
	{
		BarrelRarity = EBarrelRarity::Common;
		BarrelPickupStats.BaseDamage = FMath::RandRange(4.0f, 8.0f);
	}

	//Determine the stats depending on whether it is good or bad
}

void ABarrelPickup::RollBonuses()
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
				BarrelPickupStats.Accuracy += FMath::RandRange(0.008f, 0.016f);
				BonusRoll += 1;
				break;
			}
			if (BonusPick == 2)
			{
				BarrelPickupStats.FireRate += FMath::RandRange(0.05f, 0.1f);
				BonusRoll += 1;
				break;
				
			}
			if (BonusPick == 3)
			{
				BarrelPickupStats.BaseDamage += FMath::RandRange(4.0f, 8.0f);
				BonusRoll += 1;
				break;
			}
			if (BonusPick == 4)
			{
				BarrelPickupStats.MagazineSize += FMath::RandRange(3, 6);
				BonusRoll += 1;
				break;
			}
			if (BonusPick == 5)
			{
				BarrelPickupStats.ReloadTime += FMath::RandRange(0.4f, 0.8f);
				BonusRoll += 1;
				break;
			}
		}		
	}
}
