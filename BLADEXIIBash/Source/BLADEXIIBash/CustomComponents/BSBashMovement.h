// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BS_BaseChar.h"
#include "Components/ActorComponent.h"
#include "BSBashMovement.generated.h"


class ABS_BaseChar;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLADEXIIBASH_API UBSBashMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBSBashMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetOwnerChar(class ABS_BaseChar Character)
	{
		OwningChar =Character;
	}
	//UFUNCTION(BlueprintCallable)
	virtual void Movement(float DeltaTime,FVector InputDir);
	UFUNCTION(BlueprintCallable)
	virtual void Movement(float DeltaTime,FVector InputDir,float MaxSpeed1,float Accel1);
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<class ABS_BaseChar> OwningChar;
UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bCanJump;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsGround;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Dampening = 5.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CharHeight =1;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CharRadius = 0.2f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxSpeed =500.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Accelation = 250.f;
	
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Movement|Physics")
	TEnumAsByte<ECollisionChannel> GroundChannel = ECC_WorldStatic;

	
};
