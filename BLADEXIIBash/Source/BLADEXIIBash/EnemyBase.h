// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BS_BaseChar.h"

#include "GameFramework/Pawn.h"
#include "EnemyBase.generated.h"

UCLASS()
class BLADEXIIBASH_API AEnemyBase : public ABS_BaseChar
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanJump;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanMove;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanAttack;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bAttacking;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsHiding;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanDodge;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanHear;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsFighting;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsPeaceful;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsDead;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanRun;
	
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<AActor> TargetActor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class UPTBashAI> PathFinder;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class UBSBashMovement> MovementCompo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector InputVector;
};
