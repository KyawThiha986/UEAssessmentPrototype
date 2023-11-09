// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponAttachment.h"
#include "PickupBase.h"
#include "AGP/Characters/WeaponComponent.h"
#include "GripPickup.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API AGripPickup : public ABaseWeaponAttachment
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateGripPickupMaterial();
	
private:

	void GenerateGripPickup();
	ERarity GripRarityPicker();
	TArray<bool> GripStatPicker(int32 NumOfGood, int32 NumOfStats);
	
};
