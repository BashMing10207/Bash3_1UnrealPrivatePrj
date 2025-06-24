// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BSItemObjBase.h"
#include "AdvencedInteractableObjCompo.h"
#include "BS_BaseChar.h"

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
	Cast<ABS_BaseChar>(Caller)->GetSkeletalMeshComponent()->GetAnimInstance()->Montage_Play(UseItemAnim);
	// Cast<ABS_BaseChar>(Caller)->GetSkeletalMeshComponent()->GetAnimInstance()->Montage_JumpToSection()
	Cast<ABS_BaseChar>(Caller)->GetSkeletalMeshComponent()->GetAnimInstance()->Montage_JumpToSection(
		UsingArm->bIsRight ? FName(TEXT("Default")):FName(TEXT("Mirror")),UseItemAnim);
	return this;
}

ABSItemObjBase* ABSItemObjBase::ALTUseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller)
{
	
	// Cast<ABS_BaseChar>(Caller)->GetSkeletalMeshComponent()->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(AltUseItemAnim,
	// UsingArm->bIsRight ? FName(TEXT("Default")):FName(TEXT("Mirror")),0.1f,0.1f,1,1);
	Cast<ABS_BaseChar>(Caller)->GetSkeletalMeshComponent()->GetAnimInstance()->Montage_Play(AltUseItemAnim);
	Cast<ABS_BaseChar>(Caller)->GetSkeletalMeshComponent()->GetAnimInstance()->Montage_JumpToSection(
		UsingArm->bIsRight ? FName(TEXT("Default")):FName(TEXT("Mirror")),AltUseItemAnim);

	return this;
}

ABSItemObjBase* ABSItemObjBase::ReleaseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller)
{
	// Cast<ABS_BaseChar>(Caller)->GetSkeletalMeshComponent()->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(ReleaseItemAnim,
	//UsingArm->bIsRight ? FName(TEXT("Default")):FName(TEXT("Mirror")),0.1f,0.1f,1,1);
	Cast<ABS_BaseChar>(Caller)->GetSkeletalMeshComponent()->GetAnimInstance()->Montage_Play(ReleaseItemAnim);
	// (ReleaseItemAnim,
	// FName(TEXT("Default")),0.1f,0.1f,1,1);
	Cast<ABS_BaseChar>(Caller)->GetSkeletalMeshComponent()->GetAnimInstance()->Montage_JumpToSection(
			UsingArm->bIsRight ? FName(TEXT("Default")):FName(TEXT("Mirror")),ReleaseItemAnim);

	BeAttach(false);
	
	return this;
}

ABSItemObjBase* ABSItemObjBase::RealUseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller)
{
	
	return this;
}

ABSItemObjBase* ABSItemObjBase::RealAltUseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller)
{
	
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



