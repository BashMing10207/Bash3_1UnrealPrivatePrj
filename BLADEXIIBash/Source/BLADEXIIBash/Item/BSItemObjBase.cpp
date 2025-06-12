// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BSItemObjBase.h"
#include "AdvencedInteractableObjCompo.h"

// Sets default values
ABSItemObjBase::ABSItemObjBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractableObjCompo = CreateDefaultSubobject<UAdvencedInteractableObjCompo>("InteractableObjCompo");

	
}
ASkeltalMeshItemObjBase::ASkeltalMeshItemObjBase()
{
	MeshCompo = CreateDefaultSubobject<USkeletalMeshComponent>("MeshCompo");

	RootComponent = MeshCompo;
}

AStaticMeshItemObjBase::AStaticMeshItemObjBase()
{
	MeshCompo = CreateDefaultSubobject<UStaticMeshComponent>("MeshCompo");
	RootComponent = MeshCompo;	
}

// Called when the game starts or when spawned
void ABSItemObjBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABSItemObjBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ABSItemObjBase* ABSItemObjBase::DOInteractive_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller)
{
if (UsingArm == nullptr)
	return nullptr;
if (HoldingArm != nullptr)
	return nullptr;
	
	HoldingArm = UsingArm;
	BeAttach(true);
	

	
	return this;
}

ABSItemObjBase* ABSItemObjBase::UseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller)
{
	return this;
}

ABSItemObjBase* ABSItemObjBase::ALTUseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller)
{
	return this;
}

ABSItemObjBase* ABSItemObjBase::ReleaseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller)
{
	BeAttach(false);
	
	return this;
}

void ABSItemObjBase::BeAttach(bool isAttach)
{
	if (isAttach)
	{
		MeshCompo->SetSimulatePhysics(false);
		MeshCompo->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		MeshCompo->SetSimulatePhysics(true);
		MeshCompo->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		SetOwner(nullptr);
		HoldingArm = nullptr;
	}
}



