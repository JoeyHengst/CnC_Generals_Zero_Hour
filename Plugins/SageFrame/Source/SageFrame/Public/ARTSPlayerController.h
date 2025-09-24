// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ARTSPlayerController.generated.h"

class UInputMappingContext;
struct FInputActionValue;

/**
 * The core Player Controller for the RTS experience.
 * Handles camera movement, unit selection, and command inputs.
 */
UCLASS()
class SAGEFRAME_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSPlayerController();

	//~==============================================================================================
	//~ Input
	//~==============================================================================================

	/** The Input Mapping Context used for RTS controls. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<UInputMappingContext> RTSMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<class UInputAction> IA_CameraPan;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<class UInputAction> IA_CameraRotate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<class UInputAction> IA_CameraZoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<class UInputAction> IA_Select;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<class UInputAction> IA_Command;

	/** The list of actors currently selected by the player. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Selection")
	TArray<TObjectPtr<AActor>> CurrentlySelectedActors;

	//~==============================================================================================
	//~ Camera Controls
	//~==============================================================================================

	/** The speed at which the camera pans across the map. */
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float CameraPanSpeed = 3000.0f;

	/** The speed at which the camera rotates. */
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float CameraRotateSpeed = 10.0f;

	/** The speed at which the camera zooms in and out. */
	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float CameraZoomSpeed = 500.0f;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

	//~ Begin Input Action Handlers
	void HandleCameraPan(const FInputActionValue& Value);
	void HandleCameraRotate(const FInputActionValue& Value);
	void HandleCameraZoom(const FInputActionValue& Value);
	void HandleSelect(const FInputActionValue& Value);
	void HandleCommand(const FInputActionValue& Value);
	//~ End Input Action Handlers

	/** The pawn that provides the camera movement behavior. */
	UPROPERTY()
	TObjectPtr<APawn> PossessedPawn;
};
