// Fill out your copyright notice in the Description page of Project Settings.


#include "AUnitBase.h"
#include "Components/HealthComponent.h"
#include "Components/CommandQueueComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AUnitBase::AUnitBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Health Component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	// Create the Command Queue Component
	CommandQueueComponent = CreateDefaultSubobject<UCommandQueueComponent>(TEXT("CommandQueueComponent"));

	// Create a spring arm component for the camera
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraSpringArm->TargetArmLength = 1400.f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 10.0f;
	CameraSpringArm->bDoCollisionTest = false; // We don't want the camera to clip through the ground

	// Create and attach the camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void AUnitBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitBase::OnSelected_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Unit '%s' has been selected."), *GetName());
	// In a real implementation, you would spawn a selection decal or enable a highlight material here.
}

void AUnitBase::OnDeselected_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Unit '%s' has been deselected."), *GetName());
	// In a real implementation, you would destroy the selection decal or disable the highlight material here.
}
