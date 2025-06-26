// Fill out your copyright notice in the Description page of Project Settings.


#include "BSArmComponent.h"

#include "Enum/ArmInputType.h"
#include "GameFramework/SpringArmComponent.h"
#include "Item/BSItemObjBase.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Item/BSItemHolder.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values
ABSArmComponent_C::ABSArmComponent_C()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TestCompo = CreateDefaultSubobject<USceneComponent>("TestCompo");
	RootComponent = TestCompo;
	// HandPoint = CreateDefaultSubobject<UStaticMeshComponent>("HandPoint");
	// BodyJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>("BodyJoint");
	// //RootComponent = BodyJoint;
	// BodyJoint->SetupAttachment(TestCompo);
	// HandPoint->SetupAttachment(BodyJoint);

	// SprArmCompo = CreateDefaultSubobject<USpringArmComponent>("springArmCompo");
	//
	ArmTarget = CreateDefaultSubobject<UStaticMeshComponent>("ArmTarget");
	ArmTarget->SetupAttachment(TestCompo);
	// ArmTarget->SetupAttachment(SprArmCompo);
	
	PhysArmCompo = CreateDefaultSubobject<UPhysicsHandleComponent>("PhysArmCompo");
}	

// Called when the game starts or when spawned
void ABSArmComponent_C::BeginPlay()
{
	Super::BeginPlay();
	PhysArmCompo->GrabComponent(ArmTarget,NAME_None,ArmTarget->GetComponentLocation(),true);


	//BodyJoint->UpdateConstraintFrames();	
}

// Called every frame
void ABSArmComponent_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TestCompo->SetWorldTransform
	// SetActorTransform(OwningPawn->GetActorTransform());
	// BodyJoint->SetRelativeLocation(FVector(0, 0, 0));
	//TestCompo->SetWorldTransform(OwningPawn->GetActorTransform());
	ApplyHandPosTarget();
	// GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Red,
	// 	(FString::Printf(TEXT("%f,%f,%f"),BodyJoint->GetComponentLocation().X,BodyJoint->GetComponentLocation().Y,BodyJoint->GetComponentLocation().Z)));
	// ApplyHandPosTarget() 마지막에
	//BodyJoint->UpdateConstraintFrames();

}

void ABSArmComponent_C::SetHandPosTarget_Implementation(FTransform BodyPos,FTransform TArgetPos)
{
	PhysArmCompo->SetTargetLocationAndRotation(TargetPos.GetLocation(),TArgetPos.GetRotation().Rotator());
	//TArgetPos.SetScale3D(FVector(1.0f,1.0f,1.0f));
	// TargetPos= BodyJoint->GetComponentTransform().Inverse() * TArgetPos;
	// TargetPos.SetLocation(BodyJoint->GetComponentTransform().InverseTransformPosition(TargetPos.GetLocation())*-1);
}
void ABSArmComponent_C::ApplyHandPosTarget()
{
	// BodyJoint->SetLinearPositionTarget(TargetPos.GetLocation());
	// BodyJoint->SetAngularOrientationTarget(TargetPos.GetRotation().Rotator());
	// BodyJoint->UpdateConstraintFrames();

}
void ABSArmComponent_C::SetUpBodyJoint(UPrimitiveComponent* BodyCompo)
{
		// PhysArmCompo->GrabComponent(ArmTarget,NAME_None,ArmTarget->GetComponentLocation(),true);
		//
	
	// BodyJoint->SetConstrainedComponents(BodyCompo,NAME_None,HandPoint,
	// NAME_None);
	// Frame1: HandPoint 기준(로컬)
	// A) 컴포넌트 연결
	// BodyJoint->SetConstrainedComponents(
	// 	HandPoint, NAME_None,
	// 	BodyCompo,  NAME_None
	// );
	//
	// // B) Frame1: HandPoint 로컬 기준 (Identity)
	// BodyJoint->SetConstraintReferenceFrame(
	// 	EConstraintFrame::Frame1,
	// 	FTransform::Identity
	// );
	//
	// // C) Frame2: BodyCompo 기준, HandPoint 기준으로 상대 위치 계산
	// //    → 같은 기준점에서 목표를 해석하게 만듭니다.
	// FTransform HandWorld  = HandPoint->GetComponentTransform();
	// FTransform BodyWorld  = BodyCompo->GetComponentTransform();
	// FTransform Frame2     = BodyWorld.GetRelativeTransform(HandWorld);
	//
	// BodyJoint->SetConstraintReferenceFrame(
	// 	EConstraintFrame::Frame2,
	// 	Frame2
	// );
	//BodyJoint->UpdateConstraintFrames();

	OwningPawn = (BodyCompo->GetOwner());
	OwningChar = Cast<ABS_BaseChar>(OwningPawn);
}
void ABSArmComponent_C::SetUpBodyJoint(UPrimitiveComponent* BodyCompo,FName BOneName)
{
	//BodyJoint->SetConstrainedComponents(HandPoint,NAME_None,BodyCompo,
	//BOneName);
}

void ABSArmComponent_C::SetHoldingItem(ABSItemObjBase* ItemB)
{
	HoldingItem = ItemB;
}


void ABSArmComponent_C::GrabArm(AActor* Caller)
{

	//GEngine->AddOnScreenDebugMessage(-1,0.9f,FColor::Red,"Hit.GetActor()->GetName()");

	ABSItemObjBase* TempItemPtr = HoldingItem;
	// if (!!HoldingItem)
	// {
	// 	IIBSHoldingInteractiveable::Execute_ReleaseItemObj(HoldingItem,this,OwningPawn);
	// 	HoldingItem = nullptr;
	// }
		
	FVector Start = GetActorTransform().GetLocation();
	FVector End = GetActorTransform().GetLocation() + GetActorForwardVector()*GrabDistance;

	if (!!InteractivePivot)
	{
		Start = InteractivePivot->GetComponentLocation();
		End = InteractivePivot->GetComponentLocation() + InteractivePivot->GetForwardVector()*GrabDistance;
	
	}
	
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);           // 자기 자신 무시
	Params.AddIgnoredActor(OwningPawn);
	
	if (!!ReverseArmComponent)
		Params.AddIgnoredActor(ReverseArmComponent);
	Params.bTraceComplex = true;            // 정밀 충돌 검사
	Params.bReturnPhysicalMaterial = false;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,     // 사용할 채널
		Params
	);

	if (bHit)
	{
		if (!!Hit.GetActor())
		{
			IIBSInteractiveable* TargetItem = Cast<IIBSInteractiveable>(Hit.GetActor());
			if (TargetItem != nullptr)
			{
				
				
				GEngine->AddOnScreenDebugMessage(-1,0.9f,FColor::Red,Hit.GetActor()->GetName());
				HoldingItem = IIBSInteractiveable::Execute_DOInteractive(Hit.GetActor(),this,OwningPawn);
				
				
				if (!!HoldingItem)
				{
					HoldingItem->AttachToComponent(ArmTarget,FAttachmentTransformRules::SnapToTargetNotIncludingScale
						);//,bIsRight ? FName(TEXT("RightHand")):FName(TEXT("LeftHand"))
					if (HoldingItem->GetMeshComponent()->DoesSocketExist("Pivot"))
					{
						FTransform PivotTransform =HoldingItem->GetMeshComponent()->GetSocketTransform("Pivot");
	 					FTransform Delta = ArmTarget->GetComponentTransform().GetRelativeTransform(PivotTransform);
						// HoldingItem->SetActorRelativeTransform(PivotTransform * ScaleTrm);
						
						HoldingItem->GetMeshComponent()->SetRelativeLocation(-Delta.GetLocation());
						HoldingItem->GetMeshComponent()->SetRelativeRotation(Delta.GetRotation().Inverse());
					}
					else
					{
						
					}
				}
				else
				{
					
				}
			}
		}

	}
}

FHitResult ABSArmComponent_C::GetHitResult()
{
	FVector Start = GetActorTransform().GetLocation();
	FVector End = GetActorTransform().GetLocation() + GetActorForwardVector()*GrabDistance;

	if (!!InteractivePivot)
	{
		Start = InteractivePivot->GetComponentLocation();
		End = InteractivePivot->GetComponentLocation() + InteractivePivot->GetForwardVector()*GrabDistance;
	
	}
	
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);           // 자기 자신 무시
	Params.AddIgnoredActor(OwningPawn);
	
	if (!!ReverseArmComponent)
		Params.AddIgnoredActor(ReverseArmComponent);
	Params.bTraceComplex = true;            // 정밀 충돌 검사
	Params.bReturnPhysicalMaterial = false;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,     // 사용할 채널
		Params
	);
	return Hit;
}

void ABSArmComponent_C::DropItem()
{
	if (HoldingItem != nullptr)
	{
		IIBSHoldingInteractiveable::Execute_ReleaseItemObj(HoldingItem,this,OwningPawn);
		HoldingItem = nullptr;
	}
}

class ABSArmComponent_C* ABSArmComponent_C::UseArm_Implementation(AActor* Caller)
{
	// if (HoldingItem == nullptr)
	{
		if (!!Cast<IIUsingArmType>(Caller))
		{
			EArmInputType ArmType = (EArmInputType)IIUsingArmType::Execute_GetUsingArm(Caller);
			NoItemUseArm(Caller);

			switch (ArmType)
			{
			case EArmInputType::AttackUse:
				if (HoldingItem != nullptr)
				{
					IIBSHoldingInteractiveable::Execute_UseItemObj(HoldingItem,this,OwningPawn);
				}
				// else
				// {
				// 	GrabArm(Caller);
				// }// else
				// {
				// 	GrabArm(Caller);
				// }
				break;
			case EArmInputType::Grab:

				if (OwningChar->bIsInventory)
				{
					GrabArm(Caller);
				}
				else
				{
					if (HoldingItem != nullptr)
					{
						IIBSHoldingInteractiveable::Execute_ReleaseItemObj(HoldingItem,this,OwningPawn);
						HoldingItem = nullptr;
					}
					else
					{
						GrabArm(Caller);
					}
				}

			
				break;
			case EArmInputType::Block:
				if (HoldingItem != nullptr)
				{
					IIBSHoldingInteractiveable::Execute_ALTUseItemObj(HoldingItem,this,OwningPawn);
				}
				// else
				// {
				// 	GrabArm(Caller);
				// }
				break;
			case EArmInputType::Reload:
				if (HoldingItem != nullptr)
				{
					IIBSHoldingInteractiveable::Execute_ALTUseItemObj(HoldingItem,this,OwningPawn);
				}
				// if (HoldingItem != nullptr)
				// {
				// 	IIBSHoldingInteractiveable::Execute_ReleaseItemObj(HoldingItem,this,OwningPawn);
				// 	HoldingItem = nullptr;
				// }
				// else
				// {
				// 	GrabArm(Caller);
				// }
				break;
			}
		
		}
		else
		{
			IIBSHoldingInteractiveable::Execute_UseItemObj(HoldingItem,this,OwningPawn);
		}
	}
		
	
	
	return this;
}
