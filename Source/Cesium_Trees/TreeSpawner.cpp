// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeSpawner.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "TreeGenerator.h"
#include "Async/Async.h"


// Sets default values
ATreeSpawner::ATreeSpawner()
{
	TreeHISM = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("TreeHISM"));
}

// Called when the game starts or when spawned
void ATreeSpawner::BeginPlay()
{
	Super::BeginPlay();
	// auto AddTrees = GET_FUNCTION_NAME_CHECKED(ATreeSpawner, AddTreesInternal);
	// this->OnTreeGenerationCompleted.BindUFunction(this, AddTrees, true);
	// this->OnTreeGenerationCompleted.BindUObject(this, &ATreeSpawner::AddTreesInternal);
	FSimpleDelegate OnGenerationCompleted = FSimpleDelegate::CreateUObject(this, &ATreeSpawner::AddTreesInternal);
	//
	// Lambda
	// FSimpleDelegate OnGenerationCompleted = FSimpleDelegate::CreateLambda([this]
	// {
	// 	this->AddTreesInternal();
	// });
	MyTreeGenerator = new TreeGenerator;
	Async<>(EAsyncExecution::ThreadPool, [=]
	{
		GenerateTreeTransforms(OnGenerationCompleted);
	});
}

void ATreeSpawner::GenerateTreeTransforms(const FSimpleDelegate& InOnGenerationCompleted)
{
	if (!TreeHISM->GetStaticMesh())
	{
		UE_LOG(LogTemp, Error, TEXT("Static mesh for instanced component was not set in TreeSpawner!"));
		return;
	}
	FVector StaticMeshSize = TreeHISM->GetStaticMesh()->GetBoundingBox().GetExtent();
	UE_LOG(LogTemp, Warning, TEXT("Static mesh size: %s"), *StaticMeshSize.ToString());
	// As a rough estimate of the tree's radius, take the bounding box size, get the average of its X and Y axes, and divide by 2.
	float TreeStaticMeshRadius = (StaticMeshSize.Y + StaticMeshSize.X) / 4;
	float TreeStaticMeshHeight = StaticMeshSize.Z;

	std::vector<Tree>& Trees = MyTreeGenerator->GenerateTrees(TreesToSpawn);
	TreeTransforms.Reserve(Trees.size());
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
		TreeTransforms.Push(TreeTransform);
	}


	/** Updating the HISM needs to run on the game thread due to internal IsOnGameThread() checks.
	 * Delegates cannot normally be used to communicate between threads; they will invoke callbacks on the same
	 * thread they're called from. So I create a tiny task on the task graph to execute the delegate. */
	AsyncTask(ENamedThreads::GameThread, [=]
	{
		InOnGenerationCompleted.ExecuteIfBound();
	});
}

void ATreeSpawner::AddTreesInternal()
{
	UE_LOG(LogTemp, Warning, TEXT("In game thread: %s"), IsInGameThread()?TEXT("True") : TEXT("False"));
	if (IsInGameThread())
	{
		TreeHISM->PreAllocateInstancesMemory(TreeTransforms.Num());
		TreeHISM->AddInstances(TreeTransforms, false);
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
