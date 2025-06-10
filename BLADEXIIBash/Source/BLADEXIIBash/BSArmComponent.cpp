// Fill out your copyright notice in the Description page of Project Settings.


#include "BSArmComponent.h"

#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ABSArmComponent_C::ABSArmComponent_C()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TestCompo = CreateDefaultSubobject<USceneComponent>("TestCompo");
	RootComponent = TestCompo;
	HandPoint = CreateDefaultSubobject<UStaticMeshComponent>("HandPoint");
	BodyJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>("BodyJoint");
	//RootComponent = BodyJoint;
	BodyJoint->SetupAttachment(TestCompo);
	HandPoint->SetupAttachment(BodyJoint);
	
	
	
}	

// Called when the game starts or when spawned
void ABSArmComponent_C::BeginPlay()
{
	Super::BeginPlay();
	

	
	BodyJoint->UpdateConstraintFrames();	
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
	BodyJoint->SetConstrainedComponents(BodyCompo,NAME_None,HandPoint,
	NAME_None);
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
	BodyJoint->UpdateConstraintFrames();

	OwningPawn = (BodyCompo->GetOwner());
}
void ABSArmComponent_C::SetUpBodyJoint(UPrimitiveComponent* BodyCompo,FName BOneName)
{
	//BodyJoint->SetConstrainedComponents(HandPoint,NAME_None,BodyCompo,
	//BOneName);
}