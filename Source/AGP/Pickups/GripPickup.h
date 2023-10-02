// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PickupBase.h"
#include "WeaponComponent.h"

UENUM(BlueprintType)
enum class EGripRarity : uint8
{
	Common,
	Rare,
	Master,
	Legendary
};

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GripPickup.generated.h"

UCLASS()
class AGP_API AGripPickup : public APickupBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UPROPERTY(BlueprintReadWrite)
	EGripRarity GripRarity = EGripRarity::Common;

	FGripStats GripPickupStats;
	void GenerateGripPickup();
	void RollBonuses();
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateGripPickupMaterial();
	int32 MaxBonusRoll;

};
