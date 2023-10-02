// Fill out your copyright notice in the Description page of Project Settings.


#include "ProceduralLandscape.h"

#include <SceneExport.h>

#include "EngineUtils.h"
#include "Kismet/KismetSystemLibrary.h"
#include "KismetProceduralMeshLibrary.h"
#include "Pathfinding/NavigationNode.h"
#include "MeshBuild.h"
#include "StaticMeshOperations.h"

// Sets default values
AProceduralLandscape::AProceduralLandscape()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
	SetRootComponent(ProceduralMesh);
}

//Clears previous landscape assets when a new landscape is generated
void AProceduralLandscape::ClearLandscape()
{
	Vertices.Empty();
	Triangles.Empty();
	UVCoords.Empty();
	Nodes.Empty();
	for (TActorIterator<ANavigationNode> It(GetWorld()); It; ++It)
	{
		(*It) -> Destroy();
	}
	UKismetSystemLibrary::FlushPersistentDebugLines(GetWorld());
}

void AProceduralLandscape::GenerateLandscape()
{
	//Generates an array of Vertices
	for (int32 Y = 0; Y < Height; Y++) {
		for (int32 X = 0; X < Width; X++) {
			float Z = FMath::PerlinNoise2D(FVector2D(X * VertexSpacing * PerlinRoughness + PerlinOffset, Y * VertexSpacing * PerlinRoughness + PerlinOffset)) * PerlinScale;
			FVector Position = FVector(X * VertexSpacing, Y * VertexSpacing, Z);
			Vertices.Add(Position);
			//DrawDebugSphere(GetWorld(), Position, 50.0f, 8, FColor::Blue, true, -1.0f, 0, 5.0f);
			UVCoords.Add(FVector2D(X, Y));

			//Spawn Nodes for each vertex
			ANavigationNode* SpawnNode;
			SpawnNode = GetWorld()->SpawnActor<ANavigationNode>();
			SpawnNode -> SetActorLocation(Position);
			Nodes.Add(SpawnNode);
		}
	}

	//Adds meshes to the vertices
	for (int32 Y = 0; Y < Height - 1; Y++) {
		for (int32 X = 0; X < Width - 1; X++) {
			const int32 Origin = Y * Width + X;
			const int32 Up = ( Y + 1 ) * Width + X;
			const int32 Down = ( Y - 1 ) * Width + X;
			const int32 Left = Y * Width + X + 1;
			const int32 Right = Y * Width + X - 1;
			const int32 UpLeft = ( Y + 1 ) * Width + X + 1;
			const int32 DownLeft = ( Y - 1 ) * Width + X + 1;
			const int32 UpRight = ( Y + 1 ) * Width + X - 1;
			const int32 DownRight = ( Y - 1 ) * Width + X - 1;
			Triangles.Add(Origin);
			Triangles.Add(Up);
			Triangles.Add(Left);
			Triangles.Add(Left);
			Triangles.Add(Up);
			Triangles.Add(UpLeft);
			if (Y != Height-1) {
				Nodes[Origin]->ConnectedNodes.Add(Nodes[Up]);
			}
			if (Y != 0) {
				Nodes[Origin]->ConnectedNodes.Add(Nodes[Down]);
			}
			if (X != Width-1) {
				Nodes[Origin]->ConnectedNodes.Add(Nodes[Left]);
			}
			if (X != 0) {
				Nodes[Origin]->ConnectedNodes.Add(Nodes[Right]);
			}
			if (Y != Height-1 && X != Width-1) {
				Nodes[Origin]->ConnectedNodes.Add(Nodes[UpLeft]);
			}
			if (Y != Height-1 && X != 0) {
				Nodes[Origin]->ConnectedNodes.Add(Nodes[UpRight]);
			}
			if (Y != 0 && X != Width-1) {
				Nodes[Origin]->ConnectedNodes.Add(Nodes[DownLeft]);
			}
			if (Y != 0 && X != 0) {
				Nodes[Origin]->ConnectedNodes.Add(Nodes[DownRight]);
			}
		}
	}

	PerlinOffset = FMath::FRandRange(-1000000.0f, 1000000.0f);

	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;
	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UVCoords, Normals, Tangents);
	
	ProceduralMesh -> CreateMeshSection(0, Vertices, Triangles, Normals, UVCoords,TArray<FColor>(), Tangents, true);
}

// Called when the game starts or when spawned
void AProceduralLandscape::BeginPlay()
{
	Super::BeginPlay();
	//CreateSimplePlane();
	///ProceduralMesh->ClearMeshSection(0);
	//UKismetSystemLibrary::FlushPersistentDebugLines(GetWorld());
	//GenerateLandscape();
}

/*
void AProceduralLandscape::CreateSimplePlane()
{
	Vertices.Add(FVector(0.0f, 0.0f, FMath::RandRange(-500.0f, 500.0f)));
	Vertices.Add(FVector(1000.0f, 0.0f, FMath::RandRange(-500.0f, 500.0f)));
	Vertices.Add(FVector(0.0f, 1000.0f, FMath::RandRange(-500.0f, 500.0f)));
	Vertices.Add(FVector(1000.0f, 1000.0f, FMath::RandRange(-500.0f, 500.0f)));

	DrawDebugSphere(GetWorld(), Vertices[0], 50.0f, 8, FColor::Blue, true, -1.0f, 0, 5.0f);
	DrawDebugSphere(GetWorld(), Vertices[1], 50.0f, 8, FColor::Blue, true, -1.0f, 0, 5.0f);
	DrawDebugSphere(GetWorld(), Vertices[2], 50.0f, 8, FColor::Blue, true, -1.0f, 0, 5.0f);
	DrawDebugSphere(GetWorld(), Vertices[3], 50.0f, 8, FColor::Blue, true, -1.0f, 0, 5.0f);

	Triangles.Add(0);
	Triangles.Add(2);
	Triangles.Add(1);
	Triangles.Add(1);
	Triangles.Add(2);
	Triangles.Add(3);

	UVCoords.Add(FVector2D(0.0f, 0.0f));
	UVCoords.Add(FVector2D(1.0f, 0.0f));
	UVCoords.Add(FVector2D(0.0f, 1.0f));
	UVCoords.Add(FVector2D(1.0f, 1.0f));

	if (ProceduralMesh)
	{
		ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UVCoords,
		TArray<FColor>(), TArray<FProcMeshTangent>(), true);
	}
}
*/

// Called every frame
void AProceduralLandscape::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//For regenerating the plane every time the "should regenerate" boolean is true
	if(bShouldRegenerate == true)
	{
		ClearLandscape();
		//CreateSimplePlane();
		GenerateLandscape();
		bShouldRegenerate = false;
	}
}

bool AProceduralLandscape::ShouldTickIfViewportsOnly() const
{
	return true;
}

