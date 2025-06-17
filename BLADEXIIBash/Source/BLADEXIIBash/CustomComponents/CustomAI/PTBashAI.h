// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PTBashAI.generated.h"

UCLASS(Blueprintable,BlueprintType,meta=(BlueprintSpawnableComponent))
class BLADEXIIBASH_API UPTBashAI : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPTBashAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
	FVector BashPathFind();

protected:
	bool IsRecentlyVisited(const FVector& Pos);
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector MyTargetLocation;
	
	FVector LastMoveDirection;
	TArray<FVector> VisitedPositions;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CheckRadius;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MoveDistance;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MoveSpeed;
};
