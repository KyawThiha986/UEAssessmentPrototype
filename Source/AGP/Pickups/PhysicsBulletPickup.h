// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsPickupBase.h"
#include "AGP/Characters/WeaponComponent.h"
#include "PhysicsBulletPickup.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API APhysicsBulletPickup : public APhysicsPickupBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo) override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateBulletPickupMaterial();

	void DestroySelf();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	//void CreateBulletPickup();
};
