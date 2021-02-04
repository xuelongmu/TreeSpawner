#pragma once

#include "CoreMinimal.h"

#include "Components/WidgetComponent.h"
#include "TreeInfoWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class CESIUM_TREES_API UTreeInfoWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetInfo(float Height, float CanopyRadius);
};
