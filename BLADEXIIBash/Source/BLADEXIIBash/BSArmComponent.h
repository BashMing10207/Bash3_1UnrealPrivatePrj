// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSArmComponent.generated.h"

UCLASS(Blueprintable,BlueprintType,meta=(BlueprintSpawnableComponent))
class BLADEXIIBASH_API ABSArmComponent_C : public AActor
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
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	TObjectPtr<class UPhysicsConstraintComponent> BodyJoint;
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	// TObjectPtr<USkeletalMeshComponent> Visual;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	TObjectPtr<class UStaticMeshComponent> HandPoint;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	TObjectPtr<class USceneComponent> TestCompo;
	
	class ABSItemObjBase* HoldingItem;
	class AActor* OwningPawn;
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	FTransform TargetPos;
	
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	// TObjectPtr<class UBoxComponent> Box;
};


