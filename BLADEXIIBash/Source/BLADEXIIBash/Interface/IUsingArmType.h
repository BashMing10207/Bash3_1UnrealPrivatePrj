// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IUsingArmType.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIUsingArmType : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLADEXIIBASH_API IIUsingArmType
{
	GENERATED_BODY()

public:
	UFUNCTION(Blueprintable,BlueprintNativeEvent)
	uint8 GetUsingArm();
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
