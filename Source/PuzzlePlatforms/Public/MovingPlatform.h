// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AMovingPlatform();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

protected: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float Speed = 5.f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation = FVector::ZeroVector;

	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;

	UPROPERTY(EditAnywhere)
		int ActiveTriggers = 1;
};
