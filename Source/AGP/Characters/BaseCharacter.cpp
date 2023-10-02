// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "HealthComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletStartPosition = CreateDefaultSubobject<USceneComponent>("Bullet Start");
	BulletStartPosition->SetupAttachment(GetRootComponent());
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Health Component");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

bool ABaseCharacter::Fire(const FVector& FireAtLocation)
{
	if (HasWeapon())
	{
		return WeaponComponent->Fire(BulletStartPosition->GetComponentLocation(),FireAtLocation);
	}
	return false;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABaseCharacter::HasWeapon()
{
	if (WeaponComponent)
	{
		return true;
	}
	return false;
}

void ABaseCharacter::EquipWeapon(bool bEquipWeapon, const FWeaponStats NewWeaponStats)
{
	// If the player or enemy tries to equip a weapon and currently doesn't have one, add and register weapon component 
	if (bEquipWeapon && !HasWeapon())
	{
		WeaponComponent = NewObject<UWeaponComponent>(this);
		WeaponComponent->RegisterComponent();
		IsWeaponEquipped = true;
	}
	else if (!bEquipWeapon && HasWeapon())
	// If the player or enemy tries to unequip a weapon and currently has one equipped, unregister weapon component and remove it completely 
	{
		WeaponComponent->UnregisterComponent();
		WeaponComponent = nullptr;
		IsWeaponEquipped = false;
	}

	// At this point we should have a WeaponComponent if we are trying to equip a weapon.
	if (HasWeapon())
	{
		// Set the weapons stats to the given weapon stats.
		WeaponComponent->SetWeaponStats(NewWeaponStats);
		WeaponComponent -> SetFinalStats();
		WeaponComponent -> Ammo = WeaponComponent -> FinalWeaponStats.MagazineSize;
		CheckStatCap();
		if(WeaponComponent)
		{
			OutputStatLog();
		}
	}
	
	EquipWeaponGraphical(bEquipWeapon);
}

void ABaseCharacter::EquipBarrel(const FBarrelStats NewBarrelStats)
{
	// If weapon component exists, change the barrel's stats to the new one. Then, calculate the gun's new final stats
	if(WeaponComponent != nullptr)
	{
		WeaponComponent -> SetBarrelStats(NewBarrelStats);
		WeaponComponent -> SetFinalStats();
		CheckStatCap();
		OutputStatLog();
	}
}

void ABaseCharacter::EquipSights(const FSightsStats NewSightsStats)
{
	// If weapon component exists, change the sight's stats to the new one. Then, calculate the gun's new final stats
	if(WeaponComponent != nullptr)
	{
		WeaponComponent -> SetSightsStats(NewSightsStats);
		WeaponComponent -> SetFinalStats();
		CheckStatCap();
		OutputStatLog();
	}
}

void ABaseCharacter::EquipMagazine(const FMagazineStats NewMagazineStats)
{
	// If weapon component exists, change the magazine's stats to the new one. Then, calculate the gun's new final stats
	if(WeaponComponent != nullptr)
	{
		WeaponComponent -> SetMagazineStats(NewMagazineStats);
		WeaponComponent -> SetFinalStats();
		CheckStatCap();
		OutputStatLog();
	}
}

void ABaseCharacter::EquipGrip(const FGripStats NewGripStats)
{
	// If weapon component exists, change the grip's stats to the new one. Then, calculate the gun's new final stats
	if(WeaponComponent != nullptr)
	{
		WeaponComponent -> SetGripStats(NewGripStats);
		WeaponComponent -> SetFinalStats();
		CheckStatCap();
		OutputStatLog();
	}
}

void ABaseCharacter::EquipStock(const FStockStats NewStockStats)
{
	// If weapon component exists, change the grip's stats to the new one. Then, calculate the gun's new final stats
	if(WeaponComponent != nullptr)
	{ 
		WeaponComponent -> SetStockStats(NewStockStats);
		WeaponComponent -> SetFinalStats();
		CheckStatCap();
		OutputStatLog();
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

