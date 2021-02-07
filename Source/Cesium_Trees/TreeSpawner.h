// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TreeSpawner.generated.h"


UCLASS()
class CESIUM_TREES_API ATreeSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATreeSpawner();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 TreesToSpawn = 10000;

	/** Adds a single tree instance to the HISM */
	UFUNCTION(BlueprintCallable)
	void AddTree(FVector TreeLocation);

	/** Retrieves the tree info from the instance at a specified index in the HISM */
	bool GetTreeInfo(SIZE_T Index, OUT float& Height, OUT float& CanopyRadius) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Using a Hierarchical Instanced Static Mesh Component batches objects on the draw thread,
	* dramatically reducing the number of draw calls required. */
	UPROPERTY()
	class UHierarchicalInstancedStaticMeshComponent* TreeHISM;

private:
	class TreeGenerator* MyTreeGenerator;

	TArray<FTransform> TreeTransforms;

	/** Calculates transforms based on random generator output */
	void CalculateTreeTransforms();

	/** Add all randomly generated tree transforms to HISM. Must run on game thread. */
	void AddTreesInternal();
};
