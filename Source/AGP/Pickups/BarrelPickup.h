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

	FBarrelStats BarrelPickupStats;
	void GenerateBarrelPickup();
	void RollBonuses();
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBarrelPickupMaterial();
	int32 MaxBonusRoll;
};




