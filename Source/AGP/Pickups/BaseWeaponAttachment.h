// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "AGP/Characters/WeaponComponent.h"
#include "BaseWeaponAttachment.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API ABaseWeaponAttachment : public APickupBase
{
	GENERATED_BODY()

protected:
	
	//Declare rarity and attribute variables of weapon and attachments to be used by its corresponding child pickup classes
	UPROPERTY(BlueprintReadOnly, Replicated)
	ERarity WeaponRarity = ERarity::Common;
	UPROPERTY(BlueprintReadOnly, Replicated)
	ERarity BarrelRarity = ERarity::Common;
	UPROPERTY(BlueprintReadOnly, Replicated)
	ERarity SightRarity = ERarity::Common;
	UPROPERTY(BlueprintReadOnly, Replicated)
	ERarity MagazineRarity = ERarity::Common;
	UPROPERTY(BlueprintReadOnly, Replicated)
	ERarity GripRarity = ERarity::Common;
	UPROPERTY(BlueprintReadOnly, Replicated)
	ERarity StockRarity = ERarity::Common;
	
	UPROPERTY(Replicated)
	FWeaponStats WeaponStats;
	UPROPERTY(Replicated)
	FAttachmentStats BarrelStats;
	UPROPERTY(Replicated)
	FAttachmentStats SightStats;
	UPROPERTY(Replicated)
	FAttachmentStats MagazineStats;
	UPROPERTY(Replicated)
	FAttachmentStats GripStats;
	UPROPERTY(Replicated)
	FAttachmentStats StockStats;

	//Replicates all rarities and stats to server and clients       
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
