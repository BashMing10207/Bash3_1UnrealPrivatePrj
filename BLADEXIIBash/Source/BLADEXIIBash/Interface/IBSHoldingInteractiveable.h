// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSArmComponent.h"
#include "Item/BSItemObjBase.h"
#include "UObject/Interface.h"
#include "IBSHoldingInteractiveable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIBSHoldingInteractiveable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLADEXIIBASH_API IIBSHoldingInteractiveable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	ABSItemObjBase* UseItemObj(ABSArmComponent* UsingArm, AActor* Caller);
};
