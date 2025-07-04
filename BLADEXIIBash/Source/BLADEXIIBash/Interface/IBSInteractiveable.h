#pragma once

#include "CoreMinimal.h"
#include "BSArmComponent.h"
#include "UObject/Interface.h"
#include "IBSInteractiveable.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIBSInteractiveable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class BLADEXIIBASH_API IIBSInteractiveable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	UFUNCTION(Blueprintable, BlueprintNativeEvent)
	class ABSItemObjBase* DOInteractive(ABSArmComponent_C* UsingArm, AActor* Caller);
};
