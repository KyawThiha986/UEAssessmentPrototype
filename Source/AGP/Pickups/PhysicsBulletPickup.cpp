// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsBulletPickup.h"
#include "PickupManagerSubsystem.h"
#include "../Characters/PlayerCharacter.h"
#include "Net/UnrealNetwork.h"

void APhysicsBulletPickup::BeginPlay()
{
	Super::BeginPlay();
	UpdateBulletPickupMaterial();
}

void APhysicsBulletPickup::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
									UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	//Super::OnPickupOverlap(OverlappedComponent, OtherActor, OtherComponent, OtherBodyIndex, bFromSweep, HitInfo);
	// UE_LOG(LogTemp, Display, TEXT("Overlap event occurred on WeaponPickup"))

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		//Player->PickBullet();
		// We only want to delete it in the authority version.
		if (GetLocalRole() == ROLE_Authority)
		{
			DestroySelf();
		}
	}
}

void APhysicsBulletPickup::DestroySelf()
{
	GetWorld() -> DestroyActor(this);
}

void APhysicsBulletPickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
