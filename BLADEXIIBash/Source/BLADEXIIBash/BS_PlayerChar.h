// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BS_BaseChar.h"
#include "Enum/ArmInputType.h"
#include "Interface/IUsingArmType.h"
#include "BS_PlayerChar.generated.h"
/**
 * 
 */
UCLASS()
class BLADEXIIBASH_API ABS_PlayerChar : public ABS_BaseChar, public IIUsingArmType
{
	GENERATED_BODY()
	ABS_PlayerChar();
protected:
	// Called when the game starts or when spawned
	
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void Movement(float DeltaTIme) override;

	virtual void Sprint(bool isrunning) override;

	virtual void Jump() override;

	virtual void Crouch(bool isCrouch) override;

	UFUNCTION(BlueprintImplementableEvent)
	void CrouchNative(bool bIsCrouch);
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual uint8 GetUsingArm_Implementation() override;
	
	void Move(const struct FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void JumpPressed(const FInputActionValue& Value);
	void JumpReleased(const FInputActionValue& Value);
	
	void LMouseClicked(const FInputActionValue& Value);
	void RMouseClicked(const FInputActionValue& Value);

	void CrouchStart(const FInputActionValue& Value);
	void CrouchEnd(const FInputActionValue& Value);

	void DashInput(const FInputActionValue& Value);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// public:
// 	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Stat")
// 	float 

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	class UInputMappingContext* DefaultMappingContext;

	// 에디터에서 생성한 Input Action 자산들
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	class UInputAction* MoveAction;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* LookAction;
    
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* LeftMouse;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* RightMouse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* CrouchInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputAction* SprintInput;
	// …기존 코드 위쪽…

protected:

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cam")
	// class UCameraComponent* CameraComp;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cam")
	// class USpringArmComponent* SpringArmCompo;
	
	UPROPERTY(EditAnywhere, Category="Movement|Physics")
	float MaxSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category="Movement|Physics")
	float Acceleration = 2000.f;

	UPROPERTY(EditAnywhere, Category="Movement|Physics")
	float MaxSpeedModifi = 1.f;
	UPROPERTY(EditAnywhere, Category="Movement|Physics")
	float MaxSpeedModifiModif = 1.f;
	
	UPROPERTY(EditAnywhere, Category="Movement|Physics")
	float JumpImpulse = 350.f;

	UPROPERTY(EditAnywhere, Category="Movement|Physics")
	float Dampening = 3.f;

	// 캡슐 높이(대략 2m → 200cm 단위가 Unreal 기본)
	UPROPERTY(EditAnywhere, Category="Movement|Physics")
	float PlayerHeight = 180.f;

	UPROPERTY(EditAnywhere, Category="Movement|Physics")
	float PlayerRadius = 34.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Movement|Physics")
	TEnumAsByte<ECollisionChannel> GroundChannel = ECC_WorldStatic;

	// 입력 저장용
	FVector MovementInput;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="ArmPhysics")
	TArray<class ABSArmComponent_C*> ArmComponents;
	
	// UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="ArmPhysics")
	// class UStaticMeshComponent* TempArmTarget1;
	// UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="ArmPhysics")
	// class UStaticMeshComponent* TempArmTarget2;
	// 상태 플래그
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanJump = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsGround = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsCrouching = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsRealCrouching = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<ABSArmComponent_C*> ArmArray;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EArmInputType CurrentArmInputType;
	
	
};

