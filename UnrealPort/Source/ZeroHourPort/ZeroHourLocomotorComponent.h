// Copyright 2025 Electronic Arts, Inc. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZeroHourLocomotorComponent.generated.h"

class UPawnMovementComponent;

UENUM(BlueprintType)
enum class ELocomotorAppearance : uint8
{
	Treads,
	Wheels,
	Legs,
	Hover,
	Wings,
	Thrust,
	Other
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ZEROHOURPORT_API UZeroHourLocomotorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UZeroHourLocomotorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveTo(const FVector& TargetLocation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Braking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float TurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	ELocomotorAppearance Appearance;

private:
	FVector TargetLocation;
	bool bIsMoving;

	UPROPERTY()
	UPawnMovementComponent* MovementComponent;

	void MoveTreads(float DeltaTime);
};
