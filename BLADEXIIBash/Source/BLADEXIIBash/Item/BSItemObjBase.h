// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Interface/IBSHoldingInteractiveable.h"
#include "Interface/IBSInteractiveable.h"
#include "BSItemObjBase.generated.h"

class UPhysicsConstraintComponent;

UCLASS()
class BLADEXIIBASH_API ABSItemObjBase : public AActor, public IIBSInteractiveable, public IIBSHoldingInteractiveable
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

protected:	
	virtual class ABSItemObjBase* DOInteractive_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;

	
	virtual ABSItemObjBase* UseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;

	virtual ABSItemObjBase* ALTUseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;

	virtual ABSItemObjBase* ReleaseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;
	

	virtual void BeAttach(bool isAttach);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UMeshComponent> MeshCompo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UAdvencedInteractableObjCompo> InteractableObjCompo;

	TObjectPtr<class ABSArmComponent_C> HoldingArm;
};



UCLASS(Blueprintable)
class BLADEXIIBASH_API ASkeltalMeshItemObjBase : public ABSItemObjBase
{
	GENERATED_BODY()

	public: ASkeltalMeshItemObjBase();
};

UCLASS(Blueprintable)
class BLADEXIIBASH_API AStaticMeshItemObjBase : public ABSItemObjBase
{
	GENERATED_BODY()

public: AStaticMeshItemObjBase();
};