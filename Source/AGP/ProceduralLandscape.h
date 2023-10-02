// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Pathfinding/NavigationNode.h"
#include "ProceduralLandscape.generated.h"


UCLASS()
class AGP_API AProceduralLandscape : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralLandscape();
	void ClearLandscape();
	void GenerateLandscape();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* ProceduralMesh;

	void CreateSimplePlane();

	UPROPERTY()
	TArray<FVector> Vertices;

	UPROPERTY()
	TArray<int32> Triangles;

	UPROPERTY()
	TArray<FVector2D> UVCoords;

	UPROPERTY()
	TArray<ANavigationNode*> Nodes;

	UPROPERTY(EditAnywhere)
	bool bShouldRegenerate = false;

	UPROPERTY(EditAnywhere)
	int32 Width = 10;
	UPROPERTY(EditAnywhere)
	int32 Height = 10;

	UPROPERTY(EditAnywhere)
	float VertexSpacing = 1000.0f;

	UPROPERTY(EditAnywhere)
	float PerlinScale = 3000.0f;
	UPROPERTY(EditAnywhere)
	float PerlinRoughness = 0.00015f;

	UPROPERTY(VisibleAnywhere)
	float PerlinOffset = FMath::FRandRange(-1000000.0f, 1000000.0f);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool ShouldTickIfViewportsOnly() const override;
	
};
