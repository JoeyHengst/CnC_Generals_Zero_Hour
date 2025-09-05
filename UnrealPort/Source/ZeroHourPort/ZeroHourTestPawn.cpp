// Copyright 2025 Electronic Arts, Inc. All rights reserved.

#include "ZeroHourTestPawn.h"
#include "ZeroHourLocomotorComponent.h"

// Sets default values
AZeroHourTestPawn::AZeroHourTestPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LocomotorComponent = CreateDefaultSubobject<UZeroHourLocomotorComponent>(TEXT("LocomotorComponent"));
}

// Called when the game starts or when spawned
void AZeroHourTestPawn::BeginPlay()
{
	Super::BeginPlay();

	// Tell the pawn to move to a location
	if (LocomotorComponent)
	{
		FVector TargetLocation(1000.0f, 0.0f, 0.0f);
		LocomotorComponent->MoveTo(TargetLocation);
	}
}

// Called every frame
void AZeroHourTestPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZeroHourTestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
