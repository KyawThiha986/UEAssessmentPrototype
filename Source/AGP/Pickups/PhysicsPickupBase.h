// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMeshActor.h"
#include "PhysicsPickupBase.generated.h"

class USphereComponent;

/**
 * 
 */
UCLASS()
class AGP_API APhysicsPickupBase : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsPickupBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PickupMesh;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* PickupCollider;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* PickupRoot;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
