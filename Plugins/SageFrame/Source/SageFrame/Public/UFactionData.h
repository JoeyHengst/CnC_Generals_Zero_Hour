// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UFactionData.generated.h"

class AUnitBase;

/**
 * A Data Asset used to define a faction.
 * Contains all the information needed to describe a faction's identity,
 * available units, structures, and unique abilities. This asset-based
 * approach is designed to be easily extensible by modders.
 */
UCLASS(BlueprintType)
class SAGEFRAME_API UFactionData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** The display name of the faction. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Faction Info")
	FText FactionName;

	/** The icon representing the faction in the UI. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Faction Info")
	TObjectPtr<UTexture2D> FactionIcon;

	/** The list of units that this faction can produce. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Units")
	TArray<TSoftClassPtr<AUnitBase>> AvailableUnits;

	/** The list of structures that this faction can build. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Units")
	TArray<TSoftClassPtr<AUnitBase>> AvailableStructures;

	// In a full implementation, you would also have arrays for:
	// - General's Powers / Abilities
	// - Superweapons
	// - Tech Tree data
	// - AI personality references
};
