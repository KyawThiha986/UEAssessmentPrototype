// Fill out your copyright notice in the Description page of Project Settings.


#include "BarrelPickup.h"

#include "../Characters/PlayerCharacter.h"

void ABarrelPickup::BeginPlay()
{
	Super::BeginPlay();
	//As soon as the pickup actor spawns, generate the barrel pickup's stats and update its appearance depending on rarity
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
		// Call the function and set its parameter to the pickup's stats values which will then be used to set the player's barrel stats
		Player->EquipBarrel(BarrelPickupStats);
		Destroy();
	}
}

//Generates the stat bonuses of the barrel pickup
void ABarrelPickup::GenerateBarrelPickup()
{
	// Roll the pickup's rarity chances
	float Odds = FMath::RandRange(0, 100);

	// Depending on the landed odds value, set the rarity variable to the corresponding enum value and set its respective bonus stat value (Barrels for example will always give the base damage bonus)
	// Then, set the number of times additional bonuses will be rolled depending on rarity and call the roll bonuses method after
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
}

// Roll additional stat bonuses
void ABarrelPickup::RollBonuses()
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
				BarrelPickupStats.Accuracy += FMath::RandRange(0.008f, 0.016f);
				BonusRoll += 1;
				AccuracyUp = true;
				break;
			}
			if (BonusPick == 2 && FireRateUp == false)
			{
				BarrelPickupStats.FireRate += FMath::RandRange(0.05f, 0.1f);
				BonusRoll += 1;
				FireRateUp = true;
				break;
			}
			if (BonusPick == 3 && DamageUp == false)
			{
				BarrelPickupStats.BaseDamage += FMath::RandRange(4.0f, 8.0f);
				BonusRoll += 1;
				DamageUp = true;
				break;
			}
			if (BonusPick == 4 && MagSizeUp == false)
			{
				BarrelPickupStats.MagazineSize += FMath::RandRange(3, 6);
				BonusRoll += 1;
				MagSizeUp = true;
				break;
			}
			if (BonusPick == 5 && ReloadTimeUp == false)
			{
				BarrelPickupStats.ReloadTime += FMath::RandRange(0.4f, 0.8f);
				BonusRoll += 1;
				ReloadTimeUp = true;
				break;
			}
		}		
	}
}
