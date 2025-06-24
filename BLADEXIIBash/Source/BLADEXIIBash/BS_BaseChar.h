// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BS_BaseChar.generated.h"

UCLASS()
class BLADEXIIBASH_API ABS_BaseChar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABS_BaseChar();

protected:
	// Called when the game starts or when spawned
	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	virtual void Movement(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	virtual void Sprint(bool isrunning);
	UFUNCTION(BlueprintCallable)
	virtual void Jump();
	UFUNCTION(BlueprintCallable)
	virtual void Crouch(bool isCrouch);
	UFUNCTION(BlueprintCallable)
	virtual void Rotate(float DeltaTime);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	void TickV2(float DeltaTime);
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage , struct FDamageEvent const& DamageEvent , AController* EventInstigator , AActor* DamageCauser) override;
public:
	int32 GetLevel();
	
public:	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<class UCapsuleComponent> BaseBodyCompo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInventory = false;
protected:


	// UPROPERTY(BlueprintReadWrite,EditAnywhere)
	// TObjectPtr<class UCapsuleComponent> BaseBodyCompo;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<class UInputComponent> InputCompo;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool PitchRotate = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool YawRotate = false;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool RollRotate = false;
	// UPROPERTY(BlueprintReadWrite,EditAnywhere)
	// TObjectPtr<class UCapsuleComponent> BaseBodyCompo;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBSCharacterStatComponent> StatComponent;
public:
	UFUNCTION(BlueprintCallable)
	UBSCharacterStatComponent* GetStatComponent()
	{
		return StatComponent;
	}
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
	class USkeletalMeshComponent* GetSkeletalMeshComponent();
};
