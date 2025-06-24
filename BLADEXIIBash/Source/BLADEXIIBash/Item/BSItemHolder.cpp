// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BSItemHolder.h"

// Sets default values
ABSItemHolder::ABSItemHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshCompo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshCompo;
}

// Called when the game starts or when spawned
void ABSItemHolder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABSItemHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ABSItemObjBase* ABSItemHolder::HoldItem(ABSItemObjBase* ItemH)
{
	// if (ItemH == nullptr)
	// {
	// 	ABSItemObjBase* ItemTMP =HoldingItemObj;
	// 	DropItem();
	// 	
	// 	return HoldingItemObj;
	// }
	if (HoldingItemObj != nullptr)
	{
		ABSItemObjBase* ItemObj = HoldingItemObj;
		DropItem();
		GrabItem(ItemH);
		return ItemObj;
	}
	GrabItem(ItemH);
	return nullptr;
}

void ABSItemHolder::GrabItem(ABSItemObjBase* Item)
{
	HoldingItemObj =Item;
	

	// if (!!GEngine)
	// 	GEngine->AddOnScreenDebugMessage(-1,0.8f,FColor::Red,"HoldingItemObj");
	GEngine->AddOnScreenDebugMessage(-1,0.9f,FColor::Red,TEXT("DSF"));
	//UE_LOG(LogTemp, Warning, TEXT("Hello Unreal!"));
	if (HoldingItemObj != nullptr)
	{
		HoldingItemObj->ItemHolderInteractive(this,true);
		HoldingItemObj->AttachToComponent(MeshCompo,FAttachmentTransformRules::SnapToTargetNotIncludingScale
);//,bIsRight ? FName(TEXT("RightHand")):FName(TEXT("LeftHand"))
		if (HoldingItemObj->GetMeshComponent()->DoesSocketExist("Pivot"))
		{
			FTransform PivotTransform =HoldingItemObj->GetMeshComponent()->GetSocketTransform("Pivot");
			FTransform Delta = MeshCompo->GetComponentTransform().GetRelativeTransform(PivotTransform);
			// HoldingItem->SetActorRelativeTransform(PivotTransform * ScaleTrm);
						
			HoldingItemObj->GetMeshComponent()->SetRelativeLocation(-Delta.GetLocation());
			HoldingItemObj->GetMeshComponent()->SetRelativeRotation(Delta.GetRotation().Inverse());
		}
	}
	
}

ABSItemObjBase* ABSItemHolder::DropItem()
{
	if (HoldingItemObj ==nullptr)
		return nullptr;
	HoldingItemObj->ItemHolderInteractive(this,false);
	
	
	
	return nullptr;
}

class ABSItemObjBase* ABSItemHolder::DOInteractive_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller)
{
	ABSItemObjBase* ItemObj = HoldingItemObj;
	ABSItemObjBase* ItemObj2 =UsingArm->HoldingItem;
	UsingArm->DropItem();
	DropItem();
	HoldItem(ItemObj2);

	if (!!ItemObj)
	ItemObj = IIBSInteractiveable::Execute_DOInteractive(ItemObj,UsingArm,UsingArm->Owner);

	return ItemObj;
}

