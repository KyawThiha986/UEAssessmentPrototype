// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PickupBase.h"
#include "WeaponComponent.h"

UENUM(BlueprintType)
enum class EStockRarity : uint8
{
	Common,
	Rare,
	Master,
	Legendary
};
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StockPickup.generated.h"

UCLASS()
class AGP_API AStockPickup : public APickupBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UPROPERTY(BlueprintReadWrite)
	EStockRarity StockRarity = EStockRarity::Common;

	FStockStats StockPickupStats;
	void GenerateStockPickup();
	void RollBonuses();
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStockPickupMaterial();
	int32 MaxBonusRoll;

};
