// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponAttachment.h"

#include "BarrelPickup.h"
#include "Net/UnrealNetwork.h"

void ABaseWeaponAttachment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ABaseWeaponAttachment, WeaponRarity);
	DOREPLIFETIME(ABaseWeaponAttachment, BarrelRarity);
	DOREPLIFETIME(ABaseWeaponAttachment, SightRarity);
	DOREPLIFETIME(ABaseWeaponAttachment, MagazineRarity);
	DOREPLIFETIME(ABaseWeaponAttachment, GripRarity);
	DOREPLIFETIME(ABaseWeaponAttachment, StockRarity);
	
	DOREPLIFETIME(ABaseWeaponAttachment, WeaponStats);
	DOREPLIFETIME(ABaseWeaponAttachment, BarrelStats);
	DOREPLIFETIME(ABaseWeaponAttachment, SightStats);
	DOREPLIFETIME(ABaseWeaponAttachment, MagazineStats);
	DOREPLIFETIME(ABaseWeaponAttachment, GripStats);
	DOREPLIFETIME(ABaseWeaponAttachment, StockStats);
	
}
