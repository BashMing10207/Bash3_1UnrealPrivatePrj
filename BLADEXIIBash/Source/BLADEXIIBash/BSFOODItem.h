// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BSItemObjBase.h"
#include "BSFOODItem.generated.h"

/**
 * 
 */
UCLASS()
class BLADEXIIBASH_API ABSFOODItem : public AStaticMeshItemObjBase
{
	GENERATED_BODY()
	
	virtual ABSItemObjBase* UseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;

	virtual ABSItemObjBase* ALTUseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;

};
