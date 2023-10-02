// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponComponent.h"

UENUM(BlueprintType)
enum class ESightsRarity : uint8
{
	Common,
	Rare,
	Master,
	Legendary
};

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "SightsPickup.generated.h"

UCLASS()
class AGP_API ASightsPickup : public APickupBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UPROPERTY(BlueprintReadWrite)
	ESightsRarity SightsRarity = ESightsRarity::Common;

	FSightsStats SightsPickupStats;
	void GenerateSightsPickup();
	void RollBonuses();
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSightsPickupMaterial();
	int32 MaxBonusRoll;
};
