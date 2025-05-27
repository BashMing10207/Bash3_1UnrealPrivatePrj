// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSItemObjBase.generated.h"

class UPhysicsConstraintComponent;

UCLASS()
class BLADEXIIBASH_API ABSItemObjBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABSItemObjBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	inline UPhysicsConstraintComponent* GetPhysicsConstraint()
	{
		return PhysicsConstraint;
	}
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	TObjectPtr<class UPhysicsConstraintComponent> PhysicsConstraint;	
};
