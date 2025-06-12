// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PTActionNoiseComponent.generated.h"

/**
 * 
 */
UCLASS()
class BLADEXIIBASH_API UPTActionNoiseComponent : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Noise", meta=(WorldContext = "WorldContextObject"))
	static void SpawnNoiseAtLocation(const UObject* WorldContextObject, FVector NoiseSpawnPoint, float NoiseRange, bool bCanIgnoreWall = false, bool bISDrawDebug = false);
};
