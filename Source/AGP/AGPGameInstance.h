// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Pickups/PhysicsBulletPickup.h"
#include "AGPGameInstance.generated.h"

class AStockPickup;
class AGripPickup;
class AMagazinePickup;
class ASightPickup;
class ABarrelPickup;
class AWeaponPickup;
/**
 * 
 */
UCLASS()
class AGP_API UAGPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UClass* GetWeaponPickupClass() const;
	UClass* GetBarrelPickupClass() const;
	UClass* GetSightPickupClass() const;
	UClass* GetMagazinePickupClass() const;
	UClass* GetGripPickupClass() const;
	UClass* GetStockPickupClass() const;
	UClass* GetBulletPickupClass() const;

	void SpawnGroundHitParticles(const FVector& Location);

	void PlayGunshotSoundAtLocation(const FVector& Location);
	void PlayGunshotSound2D();
	void PlayReloadStartAtLocation(const FVector& Location);
	void PlayReloadStart2D();
	void PlayReloadFinishAtLocation(const FVector& Location);
	void PlayReloadFinish2D();
	void SpawnCharacterHitParticles(const FVector& Location);
	void SpawnSparkleParticles(const FVector& Location);
	void SpawnExplosion(const FVector& Location);

protected:

	UPROPERTY(EditDefaultsOnly, Category="Pickup Classes")
	TSubclassOf<AWeaponPickup> WeaponPickupClass;
	UPROPERTY(EditDefaultsOnly, Category="Pickup Classes")
	TSubclassOf<ABarrelPickup> BarrelPickupClass;
	UPROPERTY(EditDefaultsOnly, Category="Pickup Classes")
	TSubclassOf<ASightPickup> SightPickupClass;
	UPROPERTY(EditDefaultsOnly, Category="Pickup Classes")
	TSubclassOf<AMagazinePickup> MagazinePickupClass;
	UPROPERTY(EditDefaultsOnly, Category="Pickup Classes")
	TSubclassOf<AGripPickup> GripPickupClass;
	UPROPERTY(EditDefaultsOnly, Category="Pickup Classes")
	TSubclassOf<AStockPickup> StockPickupClass;

	UPROPERTY(EditDefaultsOnly, Category="Pickup Classes")
	TSubclassOf<APhysicsBulletPickup> BulletPickupClass;

	/**
	 * Stores a reference to the particle system for a ground and character hit as well as pickup sparkles and death explosion. Needs to be set in the BP_AGPGameInstance.
	 */
	UPROPERTY(EditDefaultsOnly, Category="Particle Systems")
	class UNiagaraSystem* GroundHitParticles;
	UPROPERTY(EditDefaultsOnly, Category="Particle Systems")
	UNiagaraSystem* CharacterHitParticles;

	UPROPERTY(EditDefaultsOnly, Category="Particle Systems")
	UNiagaraSystem* SparkleParticles;

	UPROPERTY(EditDefaultsOnly, Category="Particle Systems")
	UNiagaraSystem* ExplosionParticles;

	UPROPERTY(EditDefaultsOnly, Category="Sound Effects")
	class USoundCue* GunshotSoundCue;

	UPROPERTY(EditDefaultsOnly, Category="Sound Effects")
	class USoundCue* ReloadStartCue;

	UPROPERTY(EditDefaultsOnly, Category="Sound Effects")
	class USoundCue* ReloadFinishCue;
	
};
