// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSArmComponent.generated.h"

UCLASS()
class BLADEXIIBASH_API ABSArmComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABSArmComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetHandPosTarget(FTransform BodyPos);
	void SetUpBodyJoint(UPrimitiveComponent* BodyCompo);
	void SetUpBodyJoint(UPrimitiveComponent* BodyCompo,FName BOneName);
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	TObjectPtr<class UPhysicsConstraintComponent> BodyJoint;
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	// TObjectPtr<USkeletalMeshComponent> Visual;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	TObjectPtr<class UStaticMeshComponent> HandPoint;
	
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	FTransform TargetPos;
	
	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	// TObjectPtr<class UBoxComponent> Box;
};

