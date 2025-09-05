// Copyright 2025 Electronic Arts, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ZeroHourTestPawn.generated.h"

class UZeroHourLocomotorComponent;

UCLASS()
class ZEROHOURPORT_API AZeroHourTestPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AZeroHourTestPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UZeroHourLocomotorComponent* LocomotorComponent;
};
