// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Pickups/WeaponComponent.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;

UCLASS()
class AGP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UFUNCTION(BlueprintCallable)
	bool HasWeapon();

	void EquipWeapon(bool bEquipWeapon, const FWeaponStats NewWeaponStats);
	void EquipBarrel(const FBarrelStats NewBarrelStats);
	void EquipSights(const FSightsStats NewSightsStats);
	void EquipMagazine(const FMagazineStats NewMagazineStats);
	void EquipGrip(const FGripStats NewGripStats);
	void EquipStock(const FStockStats NewStockStats);
	UFUNCTION(BlueprintImplementableEvent)
	void EquipWeaponGraphical(bool bEquipWeapon);
	bool IsWeaponEquipped = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * A scene component to store the position that hit scan shots start from. For the enemy character this could
	 * be placed close to the guns position for example and for the player character it can be placed close to the
	 * camera position.
	 */
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BulletStartPosition;

	UPROPERTY(VisibleAnywhere)
	UHealthComponent* HealthComponent;

	/**
	 * Will fire at a specific location and handles the impact of the shot such as determining what it hit and
	 * deducting health if it hit a particular type of actor.
	 * @param FireAtLocation The location that you want to fire at.
	 * @return true if a shot was taken and false otherwise.
	 */
	bool Fire(const FVector& FireAtLocation);
	void CheckStatCap()
	{
		if(WeaponComponent -> FinalWeaponStats.Accuracy > 0.999f)
		{
			WeaponComponent -> FinalWeaponStats.Accuracy = 0.999f;
		}
		
		if(WeaponComponent -> FinalWeaponStats.FireRate < 0.015f)
		{
			WeaponComponent -> FinalWeaponStats.FireRate = 0.015f;
		}
		
		if(WeaponComponent -> FinalWeaponStats.ReloadTime < 0.2f)
		{
			WeaponComponent -> FinalWeaponStats.ReloadTime = 0.2f;
		}
	};

	void OutputStatLog()
	{
		BulletsPerSecond = 1.0f / WeaponComponent -> FinalWeaponStats.FireRate;
		AccuracyPercentage = WeaponComponent -> FinalWeaponStats.Accuracy * 100.0f;
		
		UE_LOG(LogTemp, Warning, TEXT("Accuracy: %f%%"), AccuracyPercentage);
		UE_LOG(LogTemp, Warning, TEXT("FireRate: %fbps"), BulletsPerSecond);
		UE_LOG(LogTemp, Warning, TEXT("BaseDamage: %f"), WeaponComponent -> FinalWeaponStats.BaseDamage);
		UE_LOG(LogTemp, Warning, TEXT("Magazine Size: %i"), WeaponComponent -> FinalWeaponStats.MagazineSize);
		UE_LOG(LogTemp, Warning, TEXT("Reload Time: %fs"), WeaponComponent -> FinalWeaponStats.ReloadTime);
	}

	UPROPERTY();
	UWeaponComponent* WeaponComponent = nullptr;

	int32 Ammo;
	bool IsReloading = false;
	float CurrentReloadTime;
	float EnemyReloadTime; 
	void Reload();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float BulletsPerSecond;
	float AccuracyPercentage;
};
