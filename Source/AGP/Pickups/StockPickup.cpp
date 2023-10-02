// Fill out your copyright notice in the Description page of Project Settings.


#include "StockPickup.h"

#include "../Characters/PlayerCharacter.h"

void AStockPickup::BeginPlay()
{
	Super::BeginPlay();
	GenerateStockPickup();
	UpdateStockPickupMaterial();
}

void AStockPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	//Super::OnPickupOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, HitInfo);
	// UE_LOG(LogTemp, Display, TEXT("Overlap event occurred on WeaponPickup"))

	if (ABaseCharacter* Player = Cast<ABaseCharacter>(OtherActor))
	{
		Player->EquipStock(StockPickupStats);
		Destroy();
	}
}

void AStockPickup::GenerateStockPickup()
{
	float Odds = FMath::RandRange(0, 100);

	if(Odds <= 5.0f)
	{
		StockRarity = EStockRarity::Legendary;
		StockPickupStats.ReloadTime += FMath::RandRange(1.55f, 1.95f);
		MaxBonusRoll = 2;
		RollBonuses();
	}

	else if(Odds > 5.0f && Odds <= 20.0f)
	{
		StockRarity = EStockRarity::Master;
		StockPickupStats.ReloadTime += FMath::RandRange(1.3f, 1.7f);
		MaxBonusRoll = 1;
		RollBonuses();
	}

	else if(Odds > 20.0f && Odds <= 50.0f)
	{
		StockRarity = EStockRarity::Rare;
		StockPickupStats.ReloadTime += FMath::RandRange(0.65f, 1.05f);
		MaxBonusRoll = 1;
		RollBonuses();
	}

	else
	{
		StockRarity = EStockRarity::Common;
		StockPickupStats.ReloadTime += FMath::RandRange(0.4f, 0.8f);
	}

	//Determine the stats depending on whether it is good or bad
}

void AStockPickup::RollBonuses()
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
				StockPickupStats.Accuracy += FMath::RandRange(0.008f, 0.016f);
				BonusRoll += 1;
				break;
			}
			if (BonusPick == 2)
			{
				StockPickupStats.FireRate += FMath::RandRange(0.05f, 0.1f);
				BonusRoll += 1;
				break;
				
			}
			if (BonusPick == 3)
			{
				StockPickupStats.BaseDamage += FMath::RandRange(4.0f, 8.0f);
				BonusRoll += 1;
				break;
			}
			if (BonusPick == 4)
			{
				StockPickupStats.MagazineSize += FMath::RandRange(3, 6);
				BonusRoll += 1;
				break;
			}
			if (BonusPick == 5)
			{
				StockPickupStats.ReloadTime += FMath::RandRange(0.4f, 0.8f);
				BonusRoll += 1;
				break;
			}
		}		
	}
}

