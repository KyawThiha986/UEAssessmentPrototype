// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "AGP/Characters/WeaponComponent.h"
#include "StockPickup.generated.h"

UENUM(BlueprintType)
enum class EStockRarity : uint8
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
class AGP_API AStockPickup : public APickupBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Replicated)
	EStockRarity StockRarity = EStockRarity::Common;
	UPROPERTY(Replicated)
	FStockStats StockStats;

	virtual void BeginPlay() override;
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateStockPickupMaterial();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:

	void GenerateStockPickup();
	EStockRarity StockRarityPicker();
	TArray<bool> StockStatPicker(int32 NumOfGood, int32 NumOfStats);
	
};
