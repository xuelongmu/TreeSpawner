// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "FlyingPawn.generated.h"

/**
 * 
 */
UCLASS()
class CESIUM_TREES_API AFlyingPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	/** Traces a line to a world static object and adds another item to the TreeSpawner HISM at that location. */
	UFUNCTION(BlueprintCallable)
	bool PlaceItem();

	/** Traces a line, if it hits a HISM instance then retrieves and displays the tree info for the instance */
	UFUNCTION(BlueprintCallable)
	void GetItemInfo();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTreeInfoWidgetComponent> TreeInfoWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float InteractionRange = 10000.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bDrawDebug = false;

protected:
	/** Helper method to trace a line directly facing outwards from the center of the player's viewport. */
	bool PerformLineTrace(FHitResult& OutHit, ECollisionChannel TraceChannel);

	TWeakObjectPtr<class ATreeSpawner> TreeSpawner;

	TWeakObjectPtr<class UTreeInfoWidgetComponent> TreeInfoComponent;
};
