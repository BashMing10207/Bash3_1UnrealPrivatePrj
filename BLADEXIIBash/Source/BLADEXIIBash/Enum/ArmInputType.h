#pragma once
#include "CoreMinimal.h"
#include "ArmInputType.generated.h"

UENUM(BlueprintType)
enum class EArmInputType : uint8
{
	AttackUse		= 0			UMETA(DisplayName = "AttackUse"),
	Grab			= 1			UMETA(DisplayName = "Grab"),
	Block			= 2			UMETA(DisplayName = "Release"),
	Reload			= 3			UMETA(DisplayName = "Reload"),
};