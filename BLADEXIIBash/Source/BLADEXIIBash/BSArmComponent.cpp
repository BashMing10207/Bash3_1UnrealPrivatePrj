// Fill out your copyright notice in the Description page of Project Settings.


#include "BSArmComponent.h"

#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ABSArmComponent::ABSArmComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyJoint = CreateDefaultSubobject<UPhysicsConstraintComponent>("BodyJoint");

	HandPoint = CreateDefaultSubobject<UStaticMeshComponent>("HandPoint");
	
	
}	

// Called when the game starts or when spawned
void ABSArmComponent::BeginPlay()
{
	Super::BeginPlay();
	

	BodyJoint->UpdateConstraintFrames();	
}

// Called every frame
void ABSArmComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABSArmComponent::SetHandPosTarget(FTransform BodyPos)
{
	BodyJoint->SetLinearPositionTarget(HandPoint->GetComponentTransform().InverseTransformPosition(BodyPos.GetLocation()));
	BodyJoint->SetAngularOrientationTarget(HandPoint->GetComponentTransform().InverseTransformRotation(BodyPos.GetRotation()).Rotator());
	BodyJoint->UpdateConstraintFrames();
}
void ABSArmComponent::SetUpBodyJoint(UPrimitiveComponent* BodyCompo)
{
	BodyJoint->SetConstrainedComponents(HandPoint,NAME_None,BodyCompo,
	NAME_None);
}
void ABSArmComponent::SetUpBodyJoint(UPrimitiveComponent* BodyCompo,FName BOneName)
{
	BodyJoint->SetConstrainedComponents(HandPoint,NAME_None,BodyCompo,
	BOneName);
}