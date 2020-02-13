// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			FVector Location = GetActorLocation();
			FVector NormalizedDirection = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			FVector NextLocation = Location + NormalizedDirection * Speed;

			float DistanceToTarget = FVector::Distance(Location, GlobalTargetLocation);
			float DistanceToNextLocation = FVector::Distance(Location, NextLocation);

			if (DistanceToTarget <= DistanceToNextLocation)
			{
				FVector Temp = GlobalStartLocation;
				GlobalStartLocation = GlobalTargetLocation;
				GlobalTargetLocation = Temp;
			}
			else
			{
				SetActorLocation(NextLocation);
			}
		}
	}
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers += 1;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if(ActiveTriggers > 0)
	ActiveTriggers -= 1;
}
