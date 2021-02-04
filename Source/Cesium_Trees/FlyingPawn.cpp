// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingPawn.h"


#include "DrawDebugHelpers.h"
#include "TreeInfoWidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TreeSpawner.h"
#include "TreeInfoWidgetComponent.h"

void AFlyingPawn::BeginPlay()
{
	Super::BeginPlay();
	AActor* SpawnerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ATreeSpawner::StaticClass());
	if (SpawnerActor)
	{
		TreeSpawner = Cast<ATreeSpawner>(SpawnerActor);
	}
}

bool AFlyingPawn::PlaceItem()
{
	if (!TreeSpawner.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Flying pawn was unable to find a tree spawner in the world."));
		return false;
	}
	FHitResult HitResult;
	bool bIsHit = PerformLineTrace(HitResult, ECC_WorldStatic);
	if (bIsHit)
	{
		TreeSpawner->AddTree(HitResult.Location);
		return true;
	}

	return false;
}

void AFlyingPawn::GetItemInfo()
{
	if (!TreeInfoWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Tree Info Widget class not set in Flying Pawn!"));
		return;
	}
	FHitResult HitResult;
	bool bIsHit = PerformLineTrace(HitResult, ECC_Visibility);
	if (bIsHit)
	{
		ATreeSpawner* HitSpawner = Cast<ATreeSpawner>(HitResult.Actor);
		if (HitSpawner)
		{
			float Height, CanopyRadius;
			bool Success = HitSpawner->GetTreeInfo(HitResult.Item, Height, CanopyRadius);
			if (Success)
			{
				// If component doesn't exist, create it and attach it to the TreeSpawner. If it does, simply move it
				// and update its info.
				if (!TreeInfoComponent.IsValid())
				{
					TreeInfoComponent = NewObject<UTreeInfoWidgetComponent>(
						HitSpawner, TreeInfoWidgetClass);
					TreeInfoComponent->RegisterComponent();
					TreeInfoComponent->AttachToComponent(TreeSpawner->GetRootComponent(),
					                                     FAttachmentTransformRules::KeepRelativeTransform);
				}

				TreeInfoComponent->SetWorldLocation(HitResult.Location);
				TreeInfoComponent->SetInfo(Height, CanopyRadius);
			}
		}
	}
}

bool AFlyingPawn::PerformLineTrace(OUT FHitResult& OutHit, ECollisionChannel TraceChannel)
{
	// Get player location and look direction
	FVector PlayerLocation;
	FRotator PlayerRotation;
	this->GetController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	// Set trace params. Line trace extends from player out to where they're looking, with a maximum range.
	FVector Start = PlayerLocation;
	FVector End = Start + InteractionRange * PlayerRotation.Vector();
	FCollisionQueryParams TraceParams(FName(TEXT("TraceGround")), true, this);

	if (bDrawDebug)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.f);
	}

	return GetWorld()->LineTraceSingleByChannel(
		OutHit,
		Start,
		End,
		TraceChannel,
		TraceParams
	);
}
