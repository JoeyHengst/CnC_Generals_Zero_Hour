// Copyright 2025 Electronic Arts, Inc. All rights reserved.

#include "ZeroHourLocomotorComponent.h"
#include "GameFramework/Actor.hh"
#include "GameFramework/Pawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UZeroHourLocomotorComponent::UZeroHourLocomotorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxSpeed = 100.0f;
	Acceleration = 50.0f;
	Braking = 100.0f;
	TurnRate = 90.0f;
	Appearance = ELocomotorAppearance::Treads;
	bIsMoving = false;
	MovementComponent = nullptr;
}


// Called when the game starts
void UZeroHourLocomotorComponent::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent = Cast<UPawnMovementComponent>(GetOwner()->GetComponentByClass(UPawnMovementComponent::StaticClass()));
	if (!MovementComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("ZeroHourLocomotorComponent requires a UPawnMovementComponent on the owner Actor."));
	}
}


// Called every frame
void UZeroHourLocomotorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsMoving && MovementComponent)
	{
		switch (Appearance)
		{
		case ELocomotorAppearance::Treads:
			MoveTreads(DeltaTime);
			break;
		case ELocomotorAppearance::Wheels:
			// Implementation for Wheels
			break;
		case ELocomotorAppearance::Legs:
			// Implementation for Legs
			break;
		case ELocomotorAppearance::Hover:
			// Implementation for Hover
			break;
		case ELocomotorAppearance::Wings:
			// Implementation for Wings
			break;
		case ELocomotorAppearance::Thrust:
			// Implementation for Thrust
			break;
		case ELocomotorAppearance::Other:
			// Implementation for Other
			break;
		}
	}
}

void UZeroHourLocomotorComponent::MoveTo(const FVector& NewTargetLocation)
{
	TargetLocation = NewTargetLocation;
	bIsMoving = true;
}

void UZeroHourLocomotorComponent::MoveTreads(float DeltaTime)
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	FVector CurrentLocation = Owner->GetActorLocation();
	FRotator CurrentRotation = Owner->GetActorRotation();

	// --- Rotation ---
	FVector DirectionToTarget = (TargetLocation - CurrentLocation).GetSafeNormal();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation);

	float RelAngleDegrees = FMath::FindDeltaAngleDegrees(CurrentRotation.Yaw, TargetRotation.Yaw);

	float TurnRateThisFrame = TurnRate * DeltaTime;
	float TurnAmount = FMath::Clamp(RelAngleDegrees, -TurnRateThisFrame, TurnRateThisFrame);

	FRotator NewRotation = CurrentRotation;
	NewRotation.Yaw += TurnAmount;
	Owner->SetActorRotation(NewRotation);

	// --- Speed and Acceleration ---
	// The original code used QUARTERPI (45 degrees) for this calculation.
	float AngleCoeff = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, 45.0f), FVector2D(0.0f, 1.0f), FMath::Abs(RelAngleDegrees));

	float GoalSpeed = (1.0f - AngleCoeff) * MaxSpeed;

	float CurrentSpeed = MovementComponent->Velocity.Size();

	// Simplified braking logic
	float DistToTarget = FVector::Dist(CurrentLocation, TargetLocation);
	float SlowDownDist = (CurrentSpeed * CurrentSpeed) / (2 * Braking);
	if (DistToTarget < SlowDownDist)
	{
		GoalSpeed = FMath::Min(GoalSpeed, (DistToTarget / SlowDownDist) * MaxSpeed);
	}

	if (DistToTarget < 10.0f) // Stop if close enough
	{
		bIsMoving = false;
		MovementComponent->Velocity = FVector::ZeroVector;
		return;
	}

	float SpeedDelta = GoalSpeed - CurrentSpeed;
	float AccelThisFrame = (SpeedDelta > 0 ? Acceleration : Braking) * DeltaTime;

	float NewSpeed = FMath::Clamp(CurrentSpeed + AccelThisFrame, 0.0f, MaxSpeed);

	MovementComponent->Velocity = Owner->GetActorForwardVector() * NewSpeed;
}
