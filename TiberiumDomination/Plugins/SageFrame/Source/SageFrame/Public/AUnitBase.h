// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/SelectableInterface.h"
#include "AUnitBase.generated.h"

class UHealthComponent;
class UCommandQueueComponent;
class USpringArmComponent;
class UCameraComponent;

/**
 * The base class for all units and structures in the game.
 * This class provides the fundamental behaviors and properties that are shared
 * across all selectable and commandable actors.
 *
 * It also serves as the base for the player's camera pawn.
 */
UCLASS()
class SAGEFRAME_API AUnitBase : public APawn, public ISelectableInterface
{
	GENERATED_BODY()

public:
	AUnitBase();

	//~ ISelectableInterface
	virtual void OnSelected_Implementation() override;
	virtual void OnDeselected_Implementation() override;
	//~ End ISelectableInterface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCommandQueueComponent> CommandQueueComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
