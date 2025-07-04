// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IKeyUseable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,Blueprintable, BlueprintType)
class UIKeyUseable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLADEXIIBASH_API IIKeyUseable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	AActor* UseKey(int id);
};
