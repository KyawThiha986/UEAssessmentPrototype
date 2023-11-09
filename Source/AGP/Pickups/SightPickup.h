// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponAttachment.h"
#include "PickupBase.h"
#include "AGP/Characters/WeaponComponent.h"
#include "SightPickup.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API ASightPickup : public ABaseWeaponAttachment
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSightPickupMaterial();
	
private:

	void GenerateSightPickup();
	ERarity SightRarityPicker();
	TArray<bool> SightStatPicker(int32 NumOfGood, int32 NumOfStats);
	
};
