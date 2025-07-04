// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BS_BaseChar.h"
#include "GameFramework/Actor.h"
#include "Interface/IBSArmUSE.h"
#include "Interface/IUsingArmType.h"


#include "BSArmComponent.generated.h"

class USpringArmComponent;

UCLASS(Blueprintable,BlueprintType,meta=(BlueprintSpawnableComponent))
class BLADEXIIBASH_API ABSArmComponent_C : public AActor, public IIBSArmUSE
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABSArmComponent_C();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void SetHandPosTarget(FTransform BodyPos,FTransform TArgetPos);
	void ApplyHandPosTarget();
	void SetUpBodyJoint(UPrimitiveComponent* BodyCompo);
	void SetUpBodyJoint(UPrimitiveComponent* BodyCompo,FName BOneName);


	void SetHoldingItem(class ABSItemObjBase* ItemB);

	UFUNCTION(BlueprintCallable)
	void SetReverseArmComponent(class ABSArmComponent_C* ArmB)
	{
		ReverseArmComponent = ArmB;
	}
	
	protected:
	virtual class ABSArmComponent_C* UseArm_Implementation(AActor* Caller) override;
	
	
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void NoItemUseArm(AActor* Caller);

	void GrabArm(AActor* Caller);
public:
	UFUNCTION(BlueprintCallable)
	FHitResult GetHitResult();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABSItemObjBase* HoldingItem;
UFUNCTION(BLueprintCallable)
	void DropItem();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsRight = true;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="ArmPhysics")
	class UStaticMeshComponent* ArmTarget;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="__Hand")
	USceneComponent* InteractivePivot;
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="__Hand")
	// TObjectPtr<USpringArmComponent> SprArmCompo;
	 UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="__Hand")
	 TObjectPtr<class UPhysicsHandleComponent> PhysArmCompo;
protected:
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	// TObjectPtr<class UPhysicsConstraintComponent> BodyJoint;
	//
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	// TObjectPtr<class UStaticMeshComponent> HandPoint;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	TObjectPtr<class USceneComponent> TestCompo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	float GrabDistance = 1.8f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	 TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;
	

	// class ABSItemObjBase* HoldingItem;
	class AActor* OwningPawn;
	ABS_BaseChar* OwningChar;

	ABSArmComponent_C* ReverseArmComponent;
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	FTransform TargetPos;
	
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	// TObjectPtr<class UBoxComponent> Box;
};




