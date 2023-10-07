// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponComponent.generated.h"

//Declare weapon's stats
USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.9f;
	float FireRate = 0.5f;
	float BaseDamage = 10.0f;
	int32 MagazineSize = 8;
	float ReloadTime = 4.0f;
};

USTRUCT(BlueprintType)
struct FBarrelStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.0f;
	float FireRate = 0.0f;
	float BaseDamage = 0.0f;
	int32 MagazineSize = 0;
	float ReloadTime = 0.0f;
};

USTRUCT(BlueprintType)
struct FSightsStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.0f;
	float FireRate = 0.0f;
	float BaseDamage = 0.0f;
	int32 MagazineSize = 0;
	float ReloadTime = 0.0f;
};

USTRUCT(BlueprintType)
struct FMagazineStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.0f;
	float FireRate = 0.0f;
	float BaseDamage = 0.0f;
	int32 MagazineSize = 0;
	float ReloadTime = 0.0f;
};

USTRUCT(BlueprintType)
struct FGripStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.0f;
	float FireRate = 0.0f;
	float BaseDamage = 0.0f;
	int32 MagazineSize = 0;
	float ReloadTime = 0.0f;
};

USTRUCT(BlueprintType)
struct FStockStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.0f;
	float FireRate = 0.0f;
	float BaseDamage = 0.0f;
	int32 MagazineSize = 0;
	float ReloadTime = 0.0f;
};

USTRUCT(BlueprintType)
struct FFinalWeaponStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.0f;
	float FireRate = 0.0f;
	float BaseDamage = 0.0f;
	int32 MagazineSize = 0;
	float ReloadTime = 0.0f;
};

UCLASS()
class AGP_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	UWeaponComponent();

	//Declare stats for weapon and attachments
	FWeaponStats WeaponStats;
	FBarrelStats BarrelStats;
	FSightsStats SightsStats;
	FSightsStats MagazineStats;
	FSightsStats GripStats;
	FStockStats StockStats;

	//Declare combined stats
	FFinalWeaponStats FinalWeaponStats;

	//Set stats
	void SetWeaponStats(FWeaponStats NewMainWeaponStats)
	{
		WeaponStats.Accuracy = NewMainWeaponStats.Accuracy;
		WeaponStats.FireRate = NewMainWeaponStats.FireRate;
		WeaponStats.BaseDamage = NewMainWeaponStats.BaseDamage;
		WeaponStats.MagazineSize = NewMainWeaponStats.MagazineSize;
		WeaponStats.ReloadTime = NewMainWeaponStats.ReloadTime;
	}
	
	void SetBarrelStats(FBarrelStats NewWepBarrelStats)
	{
		BarrelStats.FireRate = NewWepBarrelStats.FireRate;
		BarrelStats.BaseDamage = NewWepBarrelStats.BaseDamage;
		BarrelStats.MagazineSize = NewWepBarrelStats.MagazineSize;
		BarrelStats.ReloadTime = NewWepBarrelStats.ReloadTime;
	}

	void SetSightsStats(FSightsStats NewWepSightsStats)
	{
		SightsStats.Accuracy = NewWepSightsStats.Accuracy;
		SightsStats.FireRate = NewWepSightsStats.FireRate;
		SightsStats.BaseDamage = NewWepSightsStats.BaseDamage;
		SightsStats.MagazineSize = NewWepSightsStats.MagazineSize;
		SightsStats.ReloadTime = NewWepSightsStats.ReloadTime;
	}

	void SetMagazineStats(FMagazineStats NewWepMagazineStats)
	{
		MagazineStats.Accuracy = NewWepMagazineStats.Accuracy;
		MagazineStats.FireRate = NewWepMagazineStats.FireRate;
		MagazineStats.BaseDamage = NewWepMagazineStats.BaseDamage;
		MagazineStats.MagazineSize = NewWepMagazineStats.MagazineSize;
		MagazineStats.ReloadTime = NewWepMagazineStats.ReloadTime;
	}

	void SetGripStats(FGripStats NewWepGripStats)
	{
		GripStats.Accuracy = NewWepGripStats.Accuracy;
		GripStats.FireRate = NewWepGripStats.FireRate;
		GripStats.BaseDamage = NewWepGripStats.BaseDamage;
		GripStats.MagazineSize = NewWepGripStats.MagazineSize;
		GripStats.ReloadTime = NewWepGripStats.ReloadTime;
	}

	void SetStockStats(FStockStats NewWepStockStats)
	{
		StockStats.Accuracy = NewWepStockStats.Accuracy;
		StockStats.FireRate = NewWepStockStats.FireRate;
		StockStats.BaseDamage = NewWepStockStats.BaseDamage;
		StockStats.MagazineSize = NewWepStockStats.MagazineSize;
		StockStats.ReloadTime = NewWepStockStats.ReloadTime;
	}

	//Calculate total stats from combining all other stats
	void SetFinalStats()
	{
		FinalWeaponStats.Accuracy = WeaponStats.Accuracy + BarrelStats.Accuracy + SightsStats.Accuracy + MagazineStats.Accuracy + GripStats.Accuracy + StockStats.Accuracy;
		FinalWeaponStats.FireRate = WeaponStats.FireRate - ( BarrelStats.FireRate + SightsStats.FireRate + MagazineStats.FireRate + GripStats.FireRate + StockStats.FireRate );
		FinalWeaponStats.BaseDamage = WeaponStats.BaseDamage + BarrelStats.BaseDamage + SightsStats.BaseDamage + MagazineStats.BaseDamage + GripStats.BaseDamage + StockStats.BaseDamage;
		FinalWeaponStats.MagazineSize = WeaponStats.MagazineSize + BarrelStats.MagazineSize + SightsStats.MagazineSize + MagazineStats.MagazineSize + GripStats.MagazineSize + StockStats.MagazineSize;
		FinalWeaponStats.ReloadTime = WeaponStats.ReloadTime - ( BarrelStats.ReloadTime + SightsStats.ReloadTime + MagazineStats.ReloadTime + GripStats.ReloadTime + StockStats.ReloadTime );
	}
	
	// Declare the player and enemy weapon's ammo count and reload time, and a boolean to ensure they can't reload when are still reloading
	int32 Ammo;
	bool IsReloading = false;
	float CurrentReloadTime;
	float EnemyReloadTime;

	//Reloads your weapon, and if the ammo is greater than zero, set that to zero when reloading
	void Reload();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	int32 RoundsRemainingInMagazine;
	float TimeSinceLastShot = 0.0f;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool Fire(const FVector& BulletStart, const FVector& FireAtLocation);
};
