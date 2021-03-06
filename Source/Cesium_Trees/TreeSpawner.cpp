// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeSpawner.h"
// #include "trees-100000.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "TreeGenerator.h"


// Sets default values
ATreeSpawner::ATreeSpawner()
{
	TreeHISM = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("TreeHISM"));
}

// Called when the game starts or when spawned
void ATreeSpawner::BeginPlay()
{
	Super::BeginPlay();
	MyTreeGenerator = new TreeGenerator;
	MyTreeGenerator->GenerateTrees(TreesToSpawn);
	SpawnTrees();
}

void ATreeSpawner::SpawnTrees()
{
	if (!TreeHISM->GetStaticMesh())
	{
		UE_LOG(LogTemp, Error, TEXT("Static mesh for instanced component was not set in TreeSpawner!"));
		return;
	}
	FVector StaticMeshSize = TreeHISM->GetStaticMesh()->GetBoundingBox().GetExtent();
	UE_LOG(LogTemp, Warning, TEXT("Static mesh size: %s"), *StaticMeshSize.ToString());
	// As a rough estimate of the tree's radius, take the bounding box size, get the average of its X and Y axes, and divide by 2.
	TreeStaticMeshRadius = (StaticMeshSize.Y + StaticMeshSize.X) / 4;
	TreeStaticMeshHeight = StaticMeshSize.Z;

	std::vector<Tree>& Trees = MyTreeGenerator->trees;
	for (SIZE_T i = 0; i < Trees.size(); i++)
	{
		Tree* Tree = &Trees[i];
		FVector TreeLocation = FVector(Tree->positionX, Tree->positionY, Tree->positionZ);
		// Scale the tree to match the canopy radius and height requirements. E.g., apply a ratio of the current static mesh
		// radius, to the desired one
		FVector TreeScale = FVector(Tree->canopyRadius / TreeStaticMeshRadius,
		                            Tree->canopyRadius / TreeStaticMeshRadius,
		                            Tree->height / TreeStaticMeshHeight);

		FTransform TreeTransform = FTransform(FRotator::ZeroRotator, TreeLocation, TreeScale);

		TreeHISM->AddInstanceWorldSpace(TreeTransform);
	}
}

void ATreeSpawner::AddTree(FVector TreeLocation)
{
	if (!TreeHISM->GetStaticMesh())
	{
		UE_LOG(LogTemp, Error, TEXT("Static mesh for instanced component was not set in TreeSpawner!"));
		return;
	}
	TreeHISM->AddInstanceWorldSpace(FTransform(TreeLocation));
}

bool ATreeSpawner::GetTreeInfo(SIZE_T Index, float& Height, float& CanopyRadius) const
{
	std::vector<Tree>& Trees = MyTreeGenerator->trees;

	if (Index >= Trees.size())
	{
		return false;
	}
	Tree* Tree = &Trees[Index];
	Height = Tree->height;
	CanopyRadius = Tree->canopyRadius;
	return true;
}
