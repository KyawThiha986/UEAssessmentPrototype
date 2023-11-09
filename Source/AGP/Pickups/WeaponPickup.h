// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponAttachment.h"
#include "PickupBase.h"
#include "AGP/Characters/WeaponComponent.h"
#include "WeaponPickup.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API AWeaponPickup : public ABaseWeaponAttachment
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateWeaponPickupMaterial();
	
private:

	void GenerateWeaponPickup();
	ERarity WeaponRarityPicker();
	TArray<bool> WeaponStatPicker(int32 NumOfGood, int32 NumOfStats);
	
};
