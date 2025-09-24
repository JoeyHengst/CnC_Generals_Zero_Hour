// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CommandQueueComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"

// Sets default values for this component's properties
UCommandQueueComponent::UCommandQueueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCommandQueueComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UCommandQueueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Process the command queue here
}

void UCommandQueueComponent::QueueMoveCommand(const FVector& TargetLocation)
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
	{
		return;
	}

	AController* Controller = OwnerPawn->GetController();
	if (Controller)
	{
		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		if (NavSys)
		{
			NavSys->SimpleMoveToLocation(Controller, TargetLocation);
			UE_LOG(LogTemp, Log, TEXT("Unit '%s' moving to location: %s"), *OwnerPawn->GetName(), *TargetLocation.ToString());
		}
	}
}
