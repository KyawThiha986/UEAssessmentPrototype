// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "AGP/Characters/WeaponComponent.h"
#include "BarrelPickup.generated.h"

UENUM(BlueprintType)
enum class EBarrelRarity : uint8
{
	Common,
	Rare,
	Master,
	Legendary
};

/**
 * 
 */
UCLASS()
class AGP_API ABarrelPickup : public APickupBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Replicated)
	EBarrelRarity BarrelRarity = EBarrelRarity::Common;
	UPROPERTY(Replicated)
	FBarrelStats BarrelStats;

	virtual void BeginPlay() override;
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBarrelPickupMaterial();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:

	void GenerateBarrelPickup();
	EBarrelRarity BarrelRarityPicker();
	TArray<bool> BarrelStatPicker(int32 NumOfGood, int32 NumOfStats);
	
};
