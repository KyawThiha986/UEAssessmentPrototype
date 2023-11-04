 // Fill out your copyright notice in the Description page of Project Settings.
#include "AGPGameInstance.h"
#include "Pickups/WeaponPickup.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Pickups/BarrelPickup.h"
#include "Pickups/GripPickup.h"
#include "Pickups/MagazinePickup.h"
#include "Pickups/SightPickup.h"
#include "Pickups/StockPickup.h"
#include "Sound/SoundCue.h"

 UClass* UAGPGameInstance::GetWeaponPickupClass() const
{
  return WeaponPickupClass.Get();
}

 UClass* UAGPGameInstance::GetBarrelPickupClass() const
 {
  return BarrelPickupClass.Get();
 }

 UClass* UAGPGameInstance::GetSightPickupClass() const
 {
  return SightPickupClass.Get();
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

 void UAGPGameInstance::SpawnGroundHitParticles(const FVector& Location)
{
 UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), GroundHitParticles, Location);
}

void UAGPGameInstance::SpawnCharacterHitParticles(const FVector& Location)
 {
  UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), CharacterHitParticles, Location);
 }

 void UAGPGameInstance::PlayGunshotSoundAtLocation(const FVector& Location)
 {
  UGameplayStatics::PlaySoundAtLocation(GetWorld(), GunshotSoundCue, Location, FRotator::ZeroRotator);
 }

 void UAGPGameInstance::PlayGunshotSound2D()
 {
  UGameplayStatics::PlaySound2D(GetWorld(), GunshotSoundCue);
 }





