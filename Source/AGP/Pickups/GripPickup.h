// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "AGP/Characters/WeaponComponent.h"
#include "GripPickup.generated.h"

UENUM(BlueprintType)
enum class EGripRarity : uint8
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
class AGP_API AGripPickup : public APickupBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Replicated)
	EGripRarity GripRarity = EGripRarity::Common;
	UPROPERTY(Replicated)
	FGripStats GripStats;

	virtual void BeginPlay() override;
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateGripPickupMaterial();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:

	void GenerateGripPickup();
	EGripRarity GripRarityPicker();
	TArray<bool> GripStatPicker(int32 NumOfGood, int32 NumOfStats);
	
};
