// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "WeaponPickup.h"
#include "../Characters/BaseCharacter.h"
#include "../Characters/EnemyCharacter.h"
#include "AGP/Characters/HealthComponent.h"

// Sets default values
UWeaponComponent::UWeaponComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeSinceLastShot += DeltaTime;
	if (IsReloading == true)
	{
		CurrentReloadTime += DeltaTime;
	}
	
	if (CurrentReloadTime > FinalWeaponStats.ReloadTime && IsReloading == true)
	{
		Ammo = FinalWeaponStats.MagazineSize;
		IsReloading = false;
		UE_LOG(LogTemp, Warning, TEXT("Weapon Reloaded!"));
	}
}

bool UWeaponComponent::Fire(const FVector& BulletStart, const FVector& FireAtLocation)
{
	// Determine if the character is able to fire.
	if (TimeSinceLastShot < FinalWeaponStats.FireRate)
	{
		return false;
	}

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
	FVector AccuracyAdjustedFireAt = FMath::Lerp(RandomFireAt, FireAtLocation, FinalWeaponStats.Accuracy);
	
	if (Ammo > 0)
	{
		FHitResult HitResult;
    	FCollisionQueryParams QueryParams;
    	QueryParams.AddIgnoredActor(GetOwner());
    	if (GetWorld()->LineTraceSingleByChannel(HitResult, BulletStart, AccuracyAdjustedFireAt, ECC_Pawn, QueryParams))
    	{
    		if (ABaseCharacter* HitCharacter = Cast<ABaseCharacter>(HitResult.GetActor()))
    		{
    			if (UHealthComponent* HitCharacterHealth = HitCharacter->GetComponentByClass<UHealthComponent>())
    			{
    				HitCharacterHealth->ApplyDamage(FinalWeaponStats.BaseDamage);
    			}
    			DrawDebugLine(GetWorld(), BulletStart, HitResult.ImpactPoint, FColor::Green, false, 1.0f);
    		}
    		else
    		{
    			DrawDebugLine(GetWorld(), BulletStart, HitResult.ImpactPoint, FColor::Orange, false, 1.0f);
    		}
    		
    	}
    	else
    	{
    		DrawDebugLine(GetWorld(), BulletStart, AccuracyAdjustedFireAt, FColor::Red, false, 1.0f);
    	}
		TimeSinceLastShot = 0.0f;
		Ammo -= 1;
		return true;
	}
	else
	{
		return false;
	}
}

void UWeaponComponent::Reload()
{
	CurrentReloadTime = 0.0f;
	Ammo = 0;
	IsReloading = true;
	//Ammo = WeaponStats.MagazineSize;
	//UE_LOG(LogTemp, Warning, TEXT("Weapon Reloaded!"));
}

