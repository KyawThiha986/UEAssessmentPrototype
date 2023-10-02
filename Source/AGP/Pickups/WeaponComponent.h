// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponComponent.generated.h"

enum class EWeaponType : uint8
{
	Rifle,
	Pistol
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()
public:
	EWeaponType WeaponType = EWeaponType::Rifle;
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
	void SetWeaponStats(FWeaponStats NewWeaponStats)
	{
		WeaponStats.Accuracy = NewWeaponStats.Accuracy;
		WeaponStats.FireRate = NewWeaponStats.FireRate;
		WeaponStats.BaseDamage = NewWeaponStats.BaseDamage;
		WeaponStats.MagazineSize = NewWeaponStats.MagazineSize;
		WeaponStats.ReloadTime = NewWeaponStats.ReloadTime;
	}
	
	void SetBarrelStats(FBarrelStats NewBarrelStats)
	{
		BarrelStats.Accuracy = NewBarrelStats.Accuracy;
		BarrelStats.FireRate = NewBarrelStats.FireRate;
		BarrelStats.BaseDamage = NewBarrelStats.BaseDamage;
		BarrelStats.MagazineSize = NewBarrelStats.MagazineSize;
		BarrelStats.ReloadTime = NewBarrelStats.ReloadTime;
	}

	void SetSightsStats(FSightsStats NewSightsStats)
	{
		SightsStats.Accuracy = NewSightsStats.Accuracy;
		SightsStats.FireRate = NewSightsStats.FireRate;
		SightsStats.BaseDamage = NewSightsStats.BaseDamage;
		SightsStats.MagazineSize = NewSightsStats.MagazineSize;
		SightsStats.ReloadTime = NewSightsStats.ReloadTime;
	}

	void SetMagazineStats(FMagazineStats NewMagazineStats)
	{
		MagazineStats.Accuracy = NewMagazineStats.Accuracy;
		MagazineStats.FireRate = NewMagazineStats.FireRate;
		MagazineStats.BaseDamage = NewMagazineStats.BaseDamage;
		MagazineStats.MagazineSize = NewMagazineStats.MagazineSize;
		MagazineStats.ReloadTime = NewMagazineStats.ReloadTime;
	}

	void SetGripStats(FGripStats NewGripStats)
	{
		GripStats.Accuracy = NewGripStats.Accuracy;
		GripStats.FireRate = NewGripStats.FireRate;
		GripStats.BaseDamage = NewGripStats.BaseDamage;
		GripStats.MagazineSize = NewGripStats.MagazineSize;
		GripStats.ReloadTime = NewGripStats.ReloadTime;
	}

	void SetStockStats(FStockStats NewStockStats)
	{
		StockStats.Accuracy = NewStockStats.Accuracy;
		StockStats.FireRate = NewStockStats.FireRate;
		StockStats.BaseDamage = NewStockStats.BaseDamage;
		StockStats.MagazineSize = NewStockStats.MagazineSize;
		StockStats.ReloadTime = NewStockStats.ReloadTime;
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
	
	int32 Ammo;
	bool IsReloading = false;
	float CurrentReloadTime;
	float EnemyReloadTime; 
	void Reload();

	//Declare stats for weapon and attachments
	FWeaponStats WeaponStats;
	FBarrelStats BarrelStats;
	FSightsStats SightsStats;
	FSightsStats MagazineStats;
	FSightsStats GripStats;
	FStockStats StockStats;

	//Declare combined stats
	FFinalWeaponStats FinalWeaponStats;
	
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
