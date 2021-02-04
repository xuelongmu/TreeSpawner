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

	UFUNCTION(BlueprintCallable)
	void SpawnTrees();

	UFUNCTION(BlueprintCallable)
	void AddTree(FVector TreeLocation);

	bool GetTreeInfo(SIZE_T Index, OUT float& Height, OUT float& CanopyRadius) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/** Using a Hierarchical Instanced Static Mesh Component batches objects on the draw thread,
	* dramatically reducing the number of draw calls required.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UHierarchicalInstancedStaticMeshComponent* TreeHISM;

private:
	float TreeStaticMeshHeight;
	float TreeStaticMeshRadius;

	class TreeGenerator* MyTreeGenerator;
};
