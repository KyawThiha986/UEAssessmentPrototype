// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "PickupManagerSubsystem.h"
#include "AGP/Characters/WeaponComponent.h"
#include "BarrelPickup.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API ABarrelPickup : public APickupBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Replicated)
	ERarity BarrelRarity = ERarity::Common;
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
	ERarity BarrelRarityPicker();
	TArray<bool> BarrelStatPicker(int32 NumOfGood, int32 NumOfStats);
	
};
