// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "WeaponComponent.h"

UENUM(BlueprintType)
enum class EBarrelRarity : uint8
{
	Common,
	Rare,
	Master,
	Legendary
};

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "BarrelPickup.generated.h"

UCLASS()
class AGP_API ABarrelPickup : public APickupBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UPROPERTY(BlueprintReadWrite)
	EBarrelRarity BarrelRarity = EBarrelRarity::Common;

	// Retrieves the barrel stat enum from WeaponComponent to set the pickup's stats
	FBarrelStats BarrelPickupStats;
	void GenerateBarrelPickup();

	// For rolling bonuses in addition to pickup's main bonus
	void RollBonuses();

	// For determining the pickup's appearance depending on rarity
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBarrelPickupMaterial();

	// For determining the number of times additional bonuses will be rolled in RollBonuses method
	int32 MaxBonusRoll;
};




