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

	// Equip weapon and assign its stats
	void EquipWeapon(bool bEquipWeapon, const FWeaponStats NewWeaponStats);

	// Equip attachments and then assign their stats in the parameter if the player has a weapon equipped
	void EquipBarrel(const FBarrelStats NewBarrelStats);
	void EquipSights(const FSightsStats NewSightsStats);
	void EquipMagazine(const FMagazineStats NewMagazineStats);
	void EquipGrip(const FGripStats NewGripStats);
	void EquipStock(const FStockStats NewStockStats);

	// To visually indicate if a weapon is equipped
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

	//Sets the weapon's final accuracy, firerate, and reload time to the specified limit values if they exceed or goes below it.
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

	//Output the stats of the weapon, attachments and final stats
	void OutputWeaponStatLog()
	{
		AccuracyPercentage = WeaponComponent -> WeaponStats.Accuracy * 100.0f;
		UE_LOG(LogTemp, Warning, TEXT("Weapon Stats"));
		UE_LOG(LogTemp, Log, TEXT("Accuracy: %f%%"), AccuracyPercentage);
		UE_LOG(LogTemp, Log, TEXT("FireRate: %fs"), WeaponComponent -> WeaponStats.FireRate);
		UE_LOG(LogTemp, Log, TEXT("BaseDamage: %f"), WeaponComponent -> WeaponStats.BaseDamage);
		UE_LOG(LogTemp, Log, TEXT("Magazine Size: %i"), WeaponComponent -> WeaponStats.MagazineSize);
		UE_LOG(LogTemp, Log, TEXT("Reload Time: %fs"), WeaponComponent -> WeaponStats.ReloadTime);
	}

	//For this and all other attachments bonus logs below, only show stats with value greater than 0
	void OutputBarrelBonusesLog()
	{
		AccuracyPercentage = WeaponComponent -> BarrelStats.Accuracy * 100.0f;
		
		UE_LOG(LogTemp, Warning, TEXT("Barrel Bonuses"));
		if (WeaponComponent -> BarrelStats.BaseDamage > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("BaseDamage: +%f"), WeaponComponent -> BarrelStats.BaseDamage);
		}
		if (WeaponComponent -> BarrelStats.Accuracy > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Accuracy: +%f%%"), AccuracyPercentage);
		}
		if (WeaponComponent -> BarrelStats.FireRate > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("FireRate: -%fs"), WeaponComponent -> BarrelStats.FireRate);
		}
		if (WeaponComponent -> BarrelStats.MagazineSize > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Magazine Size: +%i"), WeaponComponent -> BarrelStats.MagazineSize);
		}
		if (WeaponComponent -> BarrelStats.ReloadTime > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Reload Time: -%fs"), WeaponComponent -> BarrelStats.ReloadTime);
		}
	}

	void OutputSightsBonusesLog()
	{
		AccuracyPercentage = WeaponComponent -> SightsStats.Accuracy * 100.0f;
		
		UE_LOG(LogTemp, Warning, TEXT("Sights Bonuses"));
		if (WeaponComponent -> SightsStats.Accuracy > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Accuracy: +%f%%"), AccuracyPercentage);
		}
		if (WeaponComponent -> SightsStats.FireRate > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("FireRate: -%fs"), WeaponComponent -> SightsStats.FireRate);
		}
		if (WeaponComponent -> SightsStats.BaseDamage > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("BaseDamage: +%f"), WeaponComponent -> SightsStats.BaseDamage);
		}
		if (WeaponComponent -> SightsStats.MagazineSize > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Magazine Size: +%i"), WeaponComponent -> SightsStats.MagazineSize);
		}
		if (WeaponComponent -> SightsStats.ReloadTime > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Reload Time: -%fs"), WeaponComponent -> SightsStats.ReloadTime);
		}
	}

	void OutputMagazineBonusesLog()
	{
		AccuracyPercentage = WeaponComponent -> MagazineStats.Accuracy * 100.0f;
		
		UE_LOG(LogTemp, Warning, TEXT("Magazine Bonuses"));
		if (WeaponComponent -> MagazineStats.MagazineSize > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Magazine Size: +%i"), WeaponComponent -> MagazineStats.MagazineSize);
		}
		if (WeaponComponent -> MagazineStats.Accuracy > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Accuracy: +%f%%"), AccuracyPercentage);
		}
		if (WeaponComponent -> MagazineStats.FireRate > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("FireRate: -%fs"), WeaponComponent -> MagazineStats.FireRate);
		}
		if (WeaponComponent -> MagazineStats.BaseDamage > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("BaseDamage: +%f"), WeaponComponent -> MagazineStats.BaseDamage);
		}
		if (WeaponComponent -> MagazineStats.ReloadTime > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Reload Time: -%fs"), WeaponComponent -> MagazineStats.ReloadTime);
		}
	}

	void OutputGripBonusesLog()
	{
		AccuracyPercentage = WeaponComponent -> GripStats.Accuracy * 100.0f;
		
		UE_LOG(LogTemp, Warning, TEXT("Grip Bonuses"));
		if (WeaponComponent -> GripStats.FireRate > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("FireRate: -%fs"), WeaponComponent -> GripStats.FireRate);
		}
		if (WeaponComponent -> GripStats.Accuracy > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Accuracy: +%f%%"), AccuracyPercentage);
		}
		if (WeaponComponent -> GripStats.BaseDamage > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("BaseDamage: +%f"), WeaponComponent -> GripStats.BaseDamage);
		}
		if (WeaponComponent -> GripStats.MagazineSize > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Magazine Size: +%i"), WeaponComponent -> GripStats.MagazineSize);
		}
		if (WeaponComponent -> GripStats.ReloadTime > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Reload Time: -%fs"), WeaponComponent -> GripStats.ReloadTime);
		}
	}

	void OutputStockBonusesLog()
	{
		AccuracyPercentage = WeaponComponent -> StockStats.Accuracy * 100.0f;
		
		UE_LOG(LogTemp, Warning, TEXT("Stock Bonuses"));
		if (WeaponComponent -> StockStats.ReloadTime > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Reload Time: -%fs"), WeaponComponent -> StockStats.ReloadTime);
		}
		if (WeaponComponent -> StockStats.Accuracy > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Accuracy: +%f%%"), AccuracyPercentage);
		}
		if (WeaponComponent -> StockStats.FireRate > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("FireRate: -%fs"), WeaponComponent -> StockStats.FireRate);
		}
		if (WeaponComponent -> StockStats.BaseDamage > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("BaseDamage: +%f"), WeaponComponent -> StockStats.BaseDamage);
		}
		if (WeaponComponent -> StockStats.MagazineSize > 0.0f)
		{
			UE_LOG(LogTemp, Log, TEXT("Magazine Size: +%i"), WeaponComponent -> StockStats.MagazineSize);
		}
	}

	//Display the final stats of your weapon in the log
	void OutputStatLog()
	{
		AccuracyPercentage = WeaponComponent -> FinalWeaponStats.Accuracy * 100.0f;

		UE_LOG(LogTemp, Warning, TEXT("Final Stats"));
		UE_LOG(LogTemp, Log, TEXT("Accuracy: %f%%"), AccuracyPercentage);
		UE_LOG(LogTemp, Log, TEXT("FireRate: %fs"), WeaponComponent -> FinalWeaponStats.FireRate);
		UE_LOG(LogTemp, Log, TEXT("BaseDamage: %f"), WeaponComponent -> FinalWeaponStats.BaseDamage);
		UE_LOG(LogTemp, Log, TEXT("Magazine Size: %i"), WeaponComponent -> FinalWeaponStats.MagazineSize);
		UE_LOG(LogTemp, Log, TEXT("Reload Time: %fs"), WeaponComponent -> FinalWeaponStats.ReloadTime);
	}

	// Call all of the output log stats
	void OutputAllLogs()
	{
		OutputWeaponStatLog();
		OutputBarrelBonusesLog();
		OutputSightsBonusesLog();
		OutputMagazineBonusesLog();
		OutputGripBonusesLog();
		OutputStockBonusesLog();
		OutputStatLog();
	}

	UPROPERTY();
	UWeaponComponent* WeaponComponent = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// To change the value of the accuracy stats so they are more user-friendly
	float AccuracyPercentage;
};
