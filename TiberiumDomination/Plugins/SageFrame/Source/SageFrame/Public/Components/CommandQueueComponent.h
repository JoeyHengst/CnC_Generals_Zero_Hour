// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommandQueueComponent.generated.h"


/**
 * Manages a queue of commands for a unit, allowing for sequential order execution.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAGEFRAME_API UCommandQueueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCommandQueueComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Issues a move command to the owning unit.
	 * @param TargetLocation The world location to move to.
	 */
	UFUNCTION(BlueprintCallable, Category = "Commands")
	void QueueMoveCommand(const FVector& TargetLocation);

	// TODO: Add a TArray to hold FCommandData structs
	// TODO: Add functions to AddCommand, ClearCommands, and process the current command
};
