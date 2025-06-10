// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PTISoundListenable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPTISoundListenable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLADEXIIBASH_API IPTISoundListenable
{
	GENERATED_BODY()
protected:
	UFUNCTION(Blueprintable, BlueprintNativeEvent)
	void ListenSound(FVector Pos);
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
