// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "IBSHoldingInteractiveable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI,Blueprintable, BlueprintType)
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
	UFUNCTION(BlueprintNativeEvent, Blueprintable,BlueprintCallable)
	class ABSItemObjBase* UseItemObj(class ABSArmComponent_C* UsingArm, AActor* Caller);
	UFUNCTION(BlueprintNativeEvent, Blueprintable,BlueprintCallable)
	ABSItemObjBase* ALTUseItemObj(ABSArmComponent_C* UsingArm, AActor* Caller);
	UFUNCTION(BlueprintNativeEvent, Blueprintable,BlueprintCallable)
	ABSItemObjBase* ReleaseItemObj(ABSArmComponent_C* UsingArm, AActor* Caller);
	UFUNCTION(BlueprintNativeEvent, Blueprintable,BlueprintCallable)
	ABSItemObjBase* ReloadItemObj(ABSArmComponent_C* UsingArm, AActor* Caller);
	UFUNCTION(BlueprintNativeEvent, Blueprintable,BlueprintCallable)
	ABSItemObjBase* RealUseItemObj(ABSArmComponent_C* UsingArm, AActor* Caller);
	UFUNCTION(BlueprintNativeEvent, Blueprintable,BlueprintCallable)
	ABSItemObjBase* RealAltUseItemObj(ABSArmComponent_C* UsingArm, AActor* Caller);
	UFUNCTION(BlueprintNativeEvent, Blueprintable,BlueprintCallable)
	ABSItemObjBase* RealReloadItemObj(ABSArmComponent_C* UsingArm, AActor* Caller);
	
};
