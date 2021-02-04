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

	UFUNCTION(BlueprintCallable)
	bool PlaceItem();

	UFUNCTION(BlueprintCallable)
	void GetItemInfo();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UTreeInfoWidgetComponent> TreeInfoWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float InteractionRange = 10000.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bDrawDebug = false;

protected:
	bool PerformLineTrace(FHitResult& OutHit, ECollisionChannel TraceChannel);

	TWeakObjectPtr<class ATreeSpawner> TreeSpawner;

	TWeakObjectPtr<class UTreeInfoWidgetComponent> TreeInfoComponent;
};
