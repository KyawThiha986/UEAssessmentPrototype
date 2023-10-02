// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PickupManagerSystem.generated.h"

/**
 * 
 */
UCLASS()
class AGP_API UPickupManagerSystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	public:
	TStatId GetStatId() const override
	{
		return GetStatID();
	}

	TArray<FVector> PossibleSpawnLocations;
	void PopulateSpawnLocations();

	protected:
	float PickupSpawnRate = 5.0f;
	float TimeSinceLastSpawn = 0.0f;
	
	private:
	void SpawnPickups();
	void Tick(float DeltaTime) override;
};
