// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponComponent.h"

UENUM(BlueprintType)
enum class EMagazineRarity : uint8
{
	Common,
	Rare,
	Master,
	Legendary
};

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "GameFramework/Actor.h"
#include "MagazinePickup.generated.h"

UCLASS()
class AGP_API AMagazinePickup : public APickupBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UPROPERTY(BlueprintReadWrite)
	EMagazineRarity MagazineRarity = EMagazineRarity::Common;

	FMagazineStats MagazinePickupStats;
	void GenerateMagazinePickup();
	void RollBonuses();
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateMagazinePickupMaterial();
	int32 MaxBonusRoll;
};
