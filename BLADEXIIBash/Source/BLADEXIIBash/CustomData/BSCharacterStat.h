// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BSCharacterStat.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBSCharacterStat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
public:
	FBSCharacterStat() 
		: MaxHp(0.f), Attack(0.f), Stemina(0.f), Hungry(0.f), AttackSpeed(0.f), Defence(0.f), MovementSpeed(0.f) {}

public:
	FBSCharacterStat operator+(const FBSCharacterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FBSCharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);

		int32 StatNumber = sizeof(FBSCharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNumber; ++i)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}
		return Result;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = Stat)
	float Attack;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = Stat)
	float Stemina;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = Stat)
	float Hungry;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = Stat)
	float AttackSpeed;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = Stat)
	float Defence;

	UPROPERTY(EditAnywhere , BlueprintReadWrite , Category = Stat)
	float MovementSpeed;
};
