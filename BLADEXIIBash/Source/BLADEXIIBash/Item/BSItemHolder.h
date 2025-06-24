// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BSItemObjBase.h"
#include "GameFramework/Actor.h"

#include "BSItemHolder.generated.h"

UCLASS()
class BLADEXIIBASH_API ABSItemHolder : public AActor,public IIBSInteractiveable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABSItemHolder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	ABSItemObjBase* HoldItem(ABSItemObjBase* ItemHolder);

	UFUNCTION(BlueprintCallable)
	void GrabItem(ABSItemObjBase* Item);

	UFUNCTION(BlueprintCallable)
	ABSItemObjBase* DropItem();
public:
	virtual class ABSItemObjBase* DOInteractive_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;
	
protected:
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<class ABSItemObjBase> HoldingItemObj;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshCompo;
};

