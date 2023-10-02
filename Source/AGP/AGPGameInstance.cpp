// Fill out your copyright notice in the Description page of Project Settings.


#include "AGPGameInstance.h"
#include "Pickups/WeaponPickup.h"

UClass* UAGPGameInstance::GetWeaponPickupClass() const
{
	return WeaponPickupClass.Get();
}

UClass* UAGPGameInstance::GetBarrelPickupClass() const
{
	return BarrelPickupClass.Get();
}

UClass* UAGPGameInstance::GetSightsPickupClass() const
{
	return SightsPickupClass.Get();
}

UClass* UAGPGameInstance::GetMagazinePickupClass() const
{
	return MagazinePickupClass.Get();
}

UClass* UAGPGameInstance::GetGripPickupClass() const
{
	return GripPickupClass.Get();
}

UClass* UAGPGameInstance::GetStockPickupClass() const
{
	return StockPickupClass.Get();
}
