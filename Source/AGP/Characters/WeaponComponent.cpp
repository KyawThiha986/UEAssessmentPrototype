// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "BaseCharacter.h"
#include "EnemyCharacter.h"
#include "HealthComponent.h"
#include "PlayerCharacter.h"
#include "AGP/AGPGameInstance.h"
#include "AGP/Pickups/PhysicsBulletPickup.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	// ...
}

void UWeaponComponent::Fire(const FVector& BulletStart, const FVector& FireAtLocation)
{
	ServerFire(BulletStart, FireAtLocation);
}

void UWeaponComponent::Reload()
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		ReloadImplementation();
	} else
	{
		ServerReload();
	}
}

void UWeaponComponent::ReloadImplementation()
{
	// Shouldn't be able to reload if you are already reloading.
	if (bIsReloading) return;
	
	UE_LOG(LogTemp, Display, TEXT("Start Reload"))
	bIsReloading = true;
}

void UWeaponComponent::ServerReload_Implementation()
{
	ReloadImplementation();
}

void UWeaponComponent::CompleteReload()
{
	UE_LOG(LogTemp, Display, TEXT("Reload Complete"))
	if (GetOwner() == Cast<APlayerCharacter>(GetOwner()))
	{
		if (FinalStats.ReserveAmmo > 0)
		{
			if (FinalStats.ReserveAmmo >= FinalStats.MagazineSize)
			{
				FinalStats.ReserveAmmo -= FinalStats.MagazineSize - RoundsRemainingInMagazine;
				RoundsRemainingInMagazine = FinalStats.MagazineSize;
				ReserveAmmoLeft = FinalStats.ReserveAmmo;
			}
			else if (FinalStats.ReserveAmmo < FinalStats.MagazineSize)
			{
				/*
				if (RoundsRemainingInMagazine > FinalStats.MagazineSize)
				{
					ExcessAmmo = RoundsRemainingInMagazine - FinalStats.MagazineSize;
					RoundsRemainingInMagazine = FinalStats.MagazineSize;
				}
				else
				{
					ExcessAmmo = 0;
				}
				*/
				
				RoundsRemainingInMagazine += FinalStats.ReserveAmmo;
				FinalStats.ReserveAmmo = RoundsRemainingInMagazine - FinalStats.MagazineSize;
				if (FinalStats.ReserveAmmo < 0)
				{
					FinalStats.ReserveAmmo = 0;
				}
				RoundsRemainingInMagazine -= FinalStats.ReserveAmmo;
				//FinalStats.ReserveAmmo -= FinalStats.MagazineSize - RoundsRemainingInMagazine;
				
				ReserveAmmoLeft = FinalStats.ReserveAmmo;
			}
		}
	}
	else if (GetOwner() == Cast<AEnemyCharacter>(GetOwner()))
	{
		RoundsRemainingInMagazine = FinalStats.MagazineSize;
	}
	UpdateAmmoUI();
}

bool UWeaponComponent::FireImplementation(const FVector& BulletStart, const FVector& FireAtLocation,
	FWeaponHitInfo& OutHitInfo)
{
	// Determine if the weapon is able to fire.
	if (TimeSinceLastShot < FinalStats.FireRate || IsMagazineEmpty() || bIsReloading)
	{
		return false;
	}

	// In order to integrate the weapon accuracy, we will need some logic to shift the FireAtLocation.
	// The general rule for the accuracy stat is:
	// An accuracy of 1.0f will not change the FireAtLocation and it will hit directly where they are aiming.
	// An accuracy of 0.0f will fire in some random direction completely disregarding the FireAtLocation.
	// The closer to 1.0f, the closer the shot will land to their fire at location.
	
	// Creates a random direction vector.
	FVector RandomFireAt = FMath::VRand();
	float CurrentShotDistance = FVector::Distance(BulletStart, FireAtLocation);
	// Makes that random direction vector the same length as the current shot between the bullet start and fire at location.
	RandomFireAt *= CurrentShotDistance;
	// Offsets the direction vector by the Bullet Start position making this RandomFireAt now contain a random position
	// somewhere on the surface a sphere surrounding the bullet start position. The original FireAtLocation is also on
	// the surface of this same sphere.
	RandomFireAt += BulletStart;
	// Now we just need to blend between these two positions based on the accuracy value.
	FVector AccuracyAdjustedFireAt = FMath::Lerp(RandomFireAt, FireAtLocation, FinalStats.Accuracy);
	

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	QueryParams.AddIgnoredActor(ECC_WorldDynamic);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, BulletStart, AccuracyAdjustedFireAt, ECC_WorldDynamic, QueryParams))
	{
		OutHitInfo.HitLocation = HitResult.ImpactPoint;
		if (ABaseCharacter* HitCharacter = Cast<ABaseCharacter>(HitResult.GetActor()))
		{
			OutHitInfo.HitType = EWeaponHitType::Character;
			if (UHealthComponent* HitCharacterHealth = HitCharacter->GetComponentByClass<UHealthComponent>())
			{
				HitCharacterHealth->ApplyDamage(FinalStats.BaseDamage);
			}
			//DrawDebugLine(GetWorld(), BulletStart, HitResult.ImpactPoint, FColor::Green, false, 1.0f);
		}
		else
		{
			OutHitInfo.HitType = EWeaponHitType::Dirt;
			//DrawDebugLine(GetWorld(), BulletStart, HitResult.ImpactPoint, FColor::Orange, false, 1.0f);
		}
	}
	else
	{
		OutHitInfo.HitLocation = AccuracyAdjustedFireAt;
		OutHitInfo.HitType = EWeaponHitType::NoHit;
		//DrawDebugLine(GetWorld(), BulletStart, AccuracyAdjustedFireAt, FColor::Red, false, 1.0f);
	}

	TimeSinceLastShot = 0.0f;
	RoundsRemainingInMagazine--;
	UpdateAmmoUI();
	
	return true;
}

void UWeaponComponent::FireVisualImplementation(const FVector& BulletStart, const FWeaponHitInfo& HitInfo)
{
	FVector SpawnPosition = HitInfo.HitLocation;
	SpawnPosition.Z += 10.0f;
	DrawDebugLine(GetWorld(), BulletStart, HitInfo.HitLocation, FColor::Yellow, false, 0.2f, 0, 3.0f);
	if (UAGPGameInstance* GameInstance = Cast<UAGPGameInstance>(GetWorld()->GetGameInstance()))
	{
		// Determine which particle effect to spawn
		switch (HitInfo.HitType)
		{
		case EWeaponHitType::Dirt:
			GameInstance->SpawnGroundHitParticles(HitInfo.HitLocation);
			break;
		case EWeaponHitType::Character:
			GameInstance->SpawnCharacterHitParticles(HitInfo.HitLocation);
			break;
		default: break;
		}
		
		// Get the pawn owner of this weapon component.
		if (const APawn* OwnerPawn = Cast<APawn>(GetOwner()))
		{
			// If the pawn owner is locally controlled then we want to play the sound in 2D (i.e. not a location
			// based sound).
			if (OwnerPawn->IsLocallyControlled())
			{
				GameInstance->PlayGunshotSound2D();
			} else
			{
				// Otherwise we want to play it at a particular 3d location so that we can detect which direction
				// the gunshot has come from through our speakers or headphones.
				GameInstance->PlayGunshotSoundAtLocation(BulletStart);
			}
			if (GetOwnerRole() == ROLE_Authority)
			{
				if (GetOwner() == Cast<APlayerCharacter>(GetOwner()))
				{
					GetWorld()->SpawnActor<APhysicsBulletPickup>(
                    				GameInstance->GetBulletPickupClass(), SpawnPosition, FRotator::ZeroRotator);
				}
			}
		}
		if (ABaseCharacter* OwnerCharacter = Cast<ABaseCharacter>(GetOwner()))
		{
			OwnerCharacter->FireWeaponGraphical();
		}
	}
}

void UWeaponComponent::ServerFire_Implementation(const FVector& BulletStart, const FVector& FireAtLocation)
{
	FWeaponHitInfo HitInfo;
	if (FireImplementation(BulletStart, FireAtLocation, HitInfo))
	{
		MulticastFire(BulletStart, HitInfo);
	}
}

void UWeaponComponent::MulticastFire_Implementation(const FVector& BulletStart, const FWeaponHitInfo& HitInfo)
{
	FireVisualImplementation(BulletStart, HitInfo);
}

void UWeaponComponent::SetWeaponStats(const FWeaponStats& WeaponInfo)
{
	this->WeaponStats = WeaponInfo;

	FinalStats.ReserveAmmo += RoundsRemainingInMagazine;
	ReserveAmmoLeft = FinalStats.ReserveAmmo;

	ResetAttachments();
	
	this->FinalStats.MagazineSize = WeaponStats.MagazineSize + BarrelStats.MagazineSize + SightStats.MagazineSize+ MagazineStats.MagazineSize + GripStats.MagazineSize + StockStats.MagazineSize;
	
	// Set the number of bullets to the magazine size
	RoundsRemainingInMagazine = FinalStats.MagazineSize;
}

void UWeaponComponent::ResetAttachments()
{
	BarrelStats.Accuracy = 0.0f; SightStats.Accuracy = 0.0f; MagazineStats.Accuracy = 0.0f; GripStats.Accuracy = 0.0f; StockStats.Accuracy = 0.0f;
	BarrelStats.FireRate = 0.0f; SightStats.FireRate = 0.0f; MagazineStats.FireRate = 0.0f; GripStats.FireRate = 0.0f; StockStats.FireRate = 0.0f;
	BarrelStats.BaseDamage = 0.0f; SightStats.BaseDamage = 0.0f; MagazineStats.BaseDamage = 0.0f; GripStats.BaseDamage = 0.0f; StockStats.BaseDamage = 0.0f;
	BarrelStats.MagazineSize = 0; SightStats.MagazineSize = 0; MagazineStats.MagazineSize = 0; GripStats.MagazineSize = 0; StockStats.MagazineSize = 0;
	BarrelStats.ReloadTime = 0.0f; SightStats.ReloadTime = 0.0f; MagazineStats.ReloadTime = 0.0f; GripStats.ReloadTime = 0.0f; StockStats.ReloadTime = 0.0f;
}

void UWeaponComponent::SetBarrelStats(const FAttachmentStats& BarrelInfo)
{
	this->BarrelStats = BarrelInfo;
}

void UWeaponComponent::SetSightStats(const FAttachmentStats& SightInfo)
{
	this->SightStats = SightInfo;
}

void UWeaponComponent::SetMagazineStats(const FAttachmentStats& MagazineInfo)
{
	this->MagazineStats = MagazineInfo;
}

void UWeaponComponent::SetGripStats(const FAttachmentStats& GripInfo)
{
	this->GripStats = GripInfo;
}

void UWeaponComponent::SetStockStats(const FAttachmentStats& StockInfo)
{
	this->StockStats = StockInfo;
}

void UWeaponComponent::SetFinalStats()
{
	this->FinalStats.Accuracy = WeaponStats.Accuracy + BarrelStats.Accuracy + SightStats.Accuracy + MagazineStats.Accuracy + GripStats.Accuracy + StockStats.Accuracy;
	this->FinalStats.FireRate = WeaponStats.FireRate - (BarrelStats.FireRate + SightStats.FireRate + MagazineStats.FireRate + GripStats.FireRate + StockStats.FireRate);
	this->FinalStats.BaseDamage = WeaponStats.BaseDamage + BarrelStats.BaseDamage + SightStats.BaseDamage + MagazineStats.BaseDamage + GripStats.BaseDamage + StockStats.BaseDamage;
	this->FinalStats.MagazineSize = WeaponStats.MagazineSize + BarrelStats.MagazineSize + SightStats.MagazineSize+ MagazineStats.MagazineSize + GripStats.MagazineSize + StockStats.MagazineSize;
	this->FinalStats.ReloadTime = WeaponStats.ReloadTime - (BarrelStats.ReloadTime + SightStats.ReloadTime + MagazineStats.ReloadTime + GripStats.ReloadTime + StockStats.ReloadTime);
	
	if(FinalStats.Accuracy > 0.999f)
	{
		FinalStats.Accuracy = 0.999f;
	}
		
	if(FinalStats.FireRate < 0.015f)
	{
		FinalStats.FireRate = 0.075f;
	}
		
	if(FinalStats.ReloadTime < 0.2f)
	{
		FinalStats.ReloadTime = 0.2f;
	}

	if(RoundsRemainingInMagazine > FinalStats.MagazineSize)
	{
		FinalStats.ReserveAmmo += RoundsRemainingInMagazine - FinalStats.MagazineSize;
		ReserveAmmoLeft = FinalStats.ReserveAmmo;
		RoundsRemainingInMagazine = FinalStats.MagazineSize;
	}
	
	UpdateAmmoUI();
}

void UWeaponComponent::PickUpBullet()
{
	FinalStats.ReserveAmmo += 1;
	ReserveAmmoLeft = FinalStats.ReserveAmmo;
	UpdateAmmoUI();
}

bool UWeaponComponent::IsMagazineEmpty()
{
	return RoundsRemainingInMagazine <= 0;
}

void UWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UWeaponComponent, RoundsRemainingInMagazine)
	DOREPLIFETIME(UWeaponComponent, ReserveAmmoLeft)
	DOREPLIFETIME(UWeaponComponent, WeaponStats);
	DOREPLIFETIME(UWeaponComponent, BarrelStats);
	DOREPLIFETIME(UWeaponComponent, SightStats);
	DOREPLIFETIME(UWeaponComponent, MagazineStats);
	DOREPLIFETIME(UWeaponComponent, GripStats);
	DOREPLIFETIME(UWeaponComponent, StockStats);
	DOREPLIFETIME(UWeaponComponent, FinalStats);
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


void UWeaponComponent::UpdateAmmoUI()
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner()))
	{
		PlayerCharacter->UpdateAmmoUI(RoundsRemainingInMagazine, FinalStats.MagazineSize, ReserveAmmoLeft);
	}
}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeSinceLastShot += DeltaTime;

	// Logic that delays the call to CompleteReload if the weapon is currently being reloaded.
	if (bIsReloading)
	{
		CurrentReloadDuration += DeltaTime;
		if (CurrentReloadDuration >= WeaponStats.ReloadTime)
		{
			bIsReloading = false;
			CompleteReload();
			CurrentReloadDuration = 0.0f;
		}
	}
}

