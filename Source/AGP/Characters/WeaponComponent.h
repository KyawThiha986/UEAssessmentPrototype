// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8 {
	Rifle,
	Pistol
};

UENUM(BlueprintType)
enum class EWeaponHitType : uint8
{
	NoHit,
	Character,
	Dirt
};

USTRUCT(BlueprintType)
struct FWeaponHitInfo
{
	GENERATED_BODY()

	UPROPERTY()
	FVector HitLocation;
	UPROPERTY()
	EWeaponHitType HitType;
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()
public:
	
	EWeaponType WeaponType = EWeaponType::Rifle;
	float Accuracy = 1.0f;
	float FireRate = 0.2f;
	float BaseDamage = 10.0f;
	UPROPERTY()
	int32 MagazineSize = 5;
	float ReloadTime = 1.0f;

	/**
	 * A debug ToString function that allows the easier printing of the weapon stats.
	 * @return A string detailing the weapon stats stored in this struct.
	 */
	FString ToString() const
	{
		FString WeaponString = "";
		WeaponString += "Accuracy:      " + FString::SanitizeFloat(Accuracy) + "\n";
		WeaponString += "Fire Rate:     " + FString::SanitizeFloat(FireRate) + "\n";
		WeaponString += "Base Damage:   " + FString::SanitizeFloat(BaseDamage) + "\n";
		WeaponString += "Magazine Size: " + FString::FromInt(MagazineSize) + "\n";
		WeaponString += "Reload Time:   " + FString::SanitizeFloat(ReloadTime);
		return WeaponString;
	}
};

USTRUCT(BlueprintType)
struct FBarrelStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.0f;
	float FireRate = 0.0f;
	float BaseDamage = 0.0f;
	UPROPERTY()
	int32 MagazineSize = 0;
	float ReloadTime = 0.0f;

	/**
	 * A debug ToString function that allows the easier printing of the weapon stats.
	 * @return A string detailing the weapon stats stored in this struct.
	 */
	FString ToString() const
	{
		FString BarrelString = "";
		BarrelString += "Accuracy:      " + FString::SanitizeFloat(Accuracy) + "\n";
		BarrelString += "Fire Rate:     " + FString::SanitizeFloat(FireRate) + "\n";
		BarrelString += "Base Damage:   " + FString::SanitizeFloat(BaseDamage) + "\n";
		BarrelString += "Magazine Size: " + FString::FromInt(MagazineSize) + "\n";
		BarrelString += "Reload Time:   " + FString::SanitizeFloat(ReloadTime);
		return BarrelString;
	}
};

USTRUCT(BlueprintType)
struct FSightStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.0f;
	float FireRate = 0.0f;
	float BaseDamage = 0.0f;
	UPROPERTY()
	int32 MagazineSize = 5;
	float ReloadTime = 0.0f;

	/**
	 * A debug ToString function that allows the easier printing of the weapon stats.
	 * @return A string detailing the weapon stats stored in this struct.
	 */
	FString ToString() const
	{
		FString SightString = "";
		SightString += "Accuracy:      " + FString::SanitizeFloat(Accuracy) + "\n";
		SightString += "Fire Rate:     " + FString::SanitizeFloat(FireRate) + "\n";
		SightString += "Base Damage:   " + FString::SanitizeFloat(BaseDamage) + "\n";
		SightString += "Magazine Size: " + FString::FromInt(MagazineSize) + "\n";
		SightString += "Reload Time:   " + FString::SanitizeFloat(ReloadTime);
		return SightString;
	}
};

USTRUCT(BlueprintType)
struct FMagazineStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.0f;
	float FireRate = 0.0f;
	float BaseDamage = 0.0f;
	UPROPERTY()
	int32 MagazineSize = 0;
	float ReloadTime = 0.0f;

	/**
	 * A debug ToString function that allows the easier printing of the weapon stats.
	 * @return A string detailing the weapon stats stored in this struct.
	 */
	FString ToString() const
	{
		FString MagazineString = "";
		MagazineString += "Accuracy:      " + FString::SanitizeFloat(Accuracy) + "\n";
		MagazineString += "Fire Rate:     " + FString::SanitizeFloat(FireRate) + "\n";
		MagazineString += "Base Damage:   " + FString::SanitizeFloat(BaseDamage) + "\n";
		MagazineString += "Magazine Size: " + FString::FromInt(MagazineSize) + "\n";
		MagazineString += "Reload Time:   " + FString::SanitizeFloat(ReloadTime);
		return MagazineString;
	}
};

USTRUCT(BlueprintType)
struct FGripStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.0f;
	float FireRate = 0.0f;
	float BaseDamage = 0.0f;
	UPROPERTY()
	int32 MagazineSize = 0;
	float ReloadTime = 0.0f;

	/**
	 * A debug ToString function that allows the easier printing of the weapon stats.
	 * @return A string detailing the weapon stats stored in this struct.
	 */
	FString ToString() const
	{
		FString GripString = "";
		GripString += "Accuracy:      " + FString::SanitizeFloat(Accuracy) + "\n";
		GripString += "Fire Rate:     " + FString::SanitizeFloat(FireRate) + "\n";
		GripString += "Base Damage:   " + FString::SanitizeFloat(BaseDamage) + "\n";
		GripString += "Magazine Size: " + FString::FromInt(MagazineSize) + "\n";
		GripString += "Reload Time:   " + FString::SanitizeFloat(ReloadTime);
		return GripString;
	}
};

USTRUCT(BlueprintType)
struct FStockStats
{
	GENERATED_BODY()
public:
	float Accuracy = 0.0f;
	float FireRate = 0.0f;
	float BaseDamage = 0.0f;
	UPROPERTY()
	int32 MagazineSize = 0;
	float ReloadTime = 0.0f;

	/**
	 * A debug ToString function that allows the easier printing of the weapon stats.
	 * @return A string detailing the weapon stats stored in this struct.
	 */
	FString ToString() const
	{
		FString StockString = "";
		StockString += "Accuracy:      " + FString::SanitizeFloat(Accuracy) + "\n";
		StockString += "Fire Rate:     " + FString::SanitizeFloat(FireRate) + "\n";
		StockString += "Base Damage:   " + FString::SanitizeFloat(BaseDamage) + "\n";
		StockString += "Magazine Size: " + FString::FromInt(MagazineSize) + "\n";
		StockString += "Reload Time:   " + FString::SanitizeFloat(ReloadTime);
		return StockString;
	}
};

USTRUCT(BlueprintType)
struct FFinalStats
{
	GENERATED_BODY()
public:
	float Accuracy = 1.0f;
	float FireRate = 0.2f;
	float BaseDamage = 10.0f;
	UPROPERTY()
	int32 MagazineSize = 5;
	float ReloadTime = 1.0f;

	/**
	 * A debug ToString function that allows the easier printing of the weapon stats.
	 * @return A string detailing the weapon stats stored in this struct.
	 */
	FString ToString() const
	{
		FString FinalString = "";
		FinalString += "Accuracy:      " + FString::SanitizeFloat(Accuracy) + "\n";
		FinalString += "Fire Rate:     " + FString::SanitizeFloat(FireRate) + "\n";
		FinalString += "Base Damage:   " + FString::SanitizeFloat(BaseDamage) + "\n";
		FinalString += "Magazine Size: " + FString::FromInt(MagazineSize) + "\n";
		FinalString += "Reload Time:   " + FString::SanitizeFloat(ReloadTime);
		return FinalString;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AGP_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	void Fire(const FVector& BulletStart, const FVector& FireAtLocation);
	/**
	 * Starts the process of reloading.
	 */
	void Reload();
	void SetWeaponStats(const FWeaponStats& WeaponInfo);
	void SetBarrelStats(const FBarrelStats& BarrelInfo);
	void SetSightStats(const FSightStats& SightInfo);
	void SetMagazineStats(const FMagazineStats& MagazineInfo);
	void SetGripStats(const FGripStats& GripInfo);
	void SetStockStats(const FStockStats& StockInfo);
	void SetFinalStats();
	
	bool IsMagazineEmpty();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(ReplicatedUsing=UpdateAmmoUI)
	FFinalStats FinalStats;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(ReplicatedUsing=UpdateAmmoUI)
	FWeaponStats WeaponStats;
	UPROPERTY(ReplicatedUsing=UpdateAmmoUI)
	FBarrelStats BarrelStats;
	UPROPERTY(ReplicatedUsing=UpdateAmmoUI)
	FSightStats SightStats;
	UPROPERTY(ReplicatedUsing=UpdateAmmoUI)
	FMagazineStats MagazineStats;
	UPROPERTY(ReplicatedUsing=UpdateAmmoUI)
	FGripStats GripStats;
	UPROPERTY(ReplicatedUsing=UpdateAmmoUI)
	FStockStats StockStats;
	
	UPROPERTY(ReplicatedUsing=UpdateAmmoUI)
	int32 RoundsRemainingInMagazine;
	float TimeSinceLastShot;
	bool bIsReloading = false;

	UFUNCTION()
	void UpdateAmmoUI();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	/**
	 * Called after the reload has been started delayed by the weapon stats reload time.
	 */
	void CompleteReload();
	float CurrentReloadDuration = 0.0f;

	bool FireImplementation(const FVector& BulletStart, const FVector& FireAtLocation, FWeaponHitInfo& HitInfo);
	void FireVisualImplementation(const FVector& BulletStart, const FWeaponHitInfo& HitInfo);
	UFUNCTION(NetMulticast, Unreliable)
	void MulticastFire(const FVector& BulletStart, const FWeaponHitInfo& HitInfo);
	UFUNCTION(Server, Reliable)
	void ServerFire(const FVector& BulletStart, const FVector& FireAtLocation);

	// RELOAD FUNCTIONS
	void ReloadImplementation();
	UFUNCTION(Server, Reliable)
	void ServerReload();
	
};
