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

	ABSItemObjBase* ItemHolderInteractive(class ABSItemHolder* Holder,bool HoldOn);
	
public:
UMeshComponent* GetMeshComponent()
{
	return MeshCompo;
}
protected:	
	virtual class ABSItemObjBase* DOInteractive_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;

	
	virtual ABSItemObjBase* UseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;

	virtual ABSItemObjBase* ALTUseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;

	virtual ABSItemObjBase* ReleaseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;
	
	virtual ABSItemObjBase* RealUseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;

	virtual ABSItemObjBase* RealAltUseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller) override;
	
	virtual void BeAttach(bool isAttach);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMeshComponent> MeshCompo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UAdvencedInteractableObjCompo> InteractableObjCompo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ABSArmComponent_C> HoldingArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ABSItemHolder> ItemHolder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UAnimMontage> UseItemAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UAnimMontage> AltUseItemAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UAnimMontage> ReleaseItemAnim;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanHold = true;
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