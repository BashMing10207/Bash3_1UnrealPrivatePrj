// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSArmComponent.h"
#include "UObject/Interface.h"
#include "IBSArmUSE.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIBSArmUSE : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLADEXIIBASH_API IIBSArmUSE
{
	GENERATED_BODY()

	ABSArmComponent* UseArm(AActor* Caller);
public:
};
