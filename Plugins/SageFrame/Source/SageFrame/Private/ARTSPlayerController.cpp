// Fill out your copyright notice in the Description page of Project Settings.


#include "ARTSPlayerController.h"
#include "AUnitBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/SelectableInterface.h"
#include "Components/CommandQueueComponent.h"

// A constructor is required for the UCLASS macro to function properly.
ARTSPlayerController::ARTSPlayerController()
{
    // Constructor logic can go here if needed.
}

void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get the Enhanced Input subsystem
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			// Add the RTS mapping context
			if (RTSMappingContext)
			{
				Subsystem->AddMappingContext(RTSMappingContext, 0);
			}
		}
	}

    // Store the pawn for easy access
    PossessedPawn = GetPawn();
}

void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Cast the input component to the Enhanced Input component
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Bind the input actions
		if (IA_CameraPan) EnhancedInputComponent->BindAction(IA_CameraPan, ETriggerEvent::Triggered, this, &ARTSPlayerController::HandleCameraPan);
		if (IA_CameraRotate) EnhancedInputComponent->BindAction(IA_CameraRotate, ETriggerEvent::Triggered, this, &ARTSPlayerController::HandleCameraRotate);
		if (IA_CameraZoom) EnhancedInputComponent->BindAction(IA_CameraZoom, ETriggerEvent::Triggered, this, &ARTSPlayerController::HandleCameraZoom);
		if (IA_Select) EnhancedInputComponent->BindAction(IA_Select, ETriggerEvent::Started, this, &ARTSPlayerController::HandleSelect);
		if (IA_Command) EnhancedInputComponent->BindAction(IA_Command, ETriggerEvent::Started, this, &ARTSPlayerController::HandleCommand);
	}
}

void ARTSPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // Tick logic can go here if needed.
}


// --- Input Handler Implementations ---

void ARTSPlayerController::HandleCameraPan(const FInputActionValue& Value)
{
    const FVector2D PanVector = Value.Get<FVector2D>();
    if (PossessedPawn && !PanVector.IsZero())
    {
        const FVector Forward = PossessedPawn->GetActorForwardVector();
        const FVector Right = PossessedPawn->GetActorRightVector();
        PossessedPawn->AddMovementInput(Forward, PanVector.Y * CameraPanSpeed * GetWorld()->GetDeltaSeconds());
        PossessedPawn->AddMovementInput(Right, PanVector.X * CameraPanSpeed * GetWorld()->GetDeltaSeconds());
        UE_LOG(LogTemp, Log, TEXT("Handling Camera Pan: %s"), *PanVector.ToString());
    }
}

void ARTSPlayerController::HandleCameraRotate(const FInputActionValue& Value)
{
    const float RotateValue = Value.Get<float>();
    if (PossessedPawn && RotateValue != 0.0f)
    {
        PossessedPawn->AddControllerYawInput(RotateValue * CameraRotateSpeed * GetWorld()->GetDeltaSeconds());
        UE_LOG(LogTemp, Log, TEXT("Handling Camera Rotate: %f"), RotateValue);
    }
}

void ARTSPlayerController::HandleCameraZoom(const FInputActionValue& Value)
{
	const float ZoomValue = Value.Get<float>();
	if (PossessedPawn)
	{
		if (AUnitBase* CameraPawn = Cast<AUnitBase>(PossessedPawn))
		{
			if (CameraPawn->CameraSpringArm)
			{
				float NewArmLength = CameraPawn->CameraSpringArm->TargetArmLength + (ZoomValue * -1 * CameraZoomSpeed);
				// Clamp the zoom level
				NewArmLength = FMath::Clamp(NewArmLength, 300.f, 3000.f);
				CameraPawn->CameraSpringArm->TargetArmLength = NewArmLength;
			}
		}
	}
}

void ARTSPlayerController::HandleSelect(const FInputActionValue& Value)
{
	// Deselect currently selected actors
	for (AActor* SelectedActor : CurrentlySelectedActors)
	{
		if (ISelectableInterface* Selectable = Cast<ISelectableInterface>(SelectedActor))
		{
			Selectable->Execute_OnDeselected(SelectedActor);
		}
	}
	CurrentlySelectedActors.Empty();

	// Perform a line trace under the cursor
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			// Check if the actor implements the selectable interface
			if (HitActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
			{
				ISelectableInterface* Selectable = Cast<ISelectableInterface>(HitActor);
				Selectable->Execute_OnSelected(HitActor);
				CurrentlySelectedActors.Add(HitActor);
				UE_LOG(LogTemp, Log, TEXT("Selected Actor: %s"), *HitActor->GetName());
			}
		}
	}
}

void ARTSPlayerController::HandleCommand(const FInputActionValue& Value)
{
	// Ensure we have units selected
	if (CurrentlySelectedActors.Num() == 0)
	{
		return;
	}

	// Get the location on the ground under the cursor
	FHitResult HitResult;
	if (GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
	{
		const FVector TargetLocation = HitResult.Location;

		// Issue a move command to all selected units
		for (AActor* SelectedActor : CurrentlySelectedActors)
		{
			if (SelectedActor)
			{
				UCommandQueueComponent* CommandQueue = SelectedActor->FindComponentByClass<UCommandQueueComponent>();
				if (CommandQueue)
				{
					CommandQueue->QueueMoveCommand(TargetLocation);
				}
			}
		}
	}
}
