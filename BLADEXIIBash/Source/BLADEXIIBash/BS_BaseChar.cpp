// Fill out your copyright notice in the Description page of Project Settings.


#include "BS_BaseChar.h"

#include "Components/CapsuleComponent.h"


// Sets default values
ABS_BaseChar::ABS_BaseChar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseBodyCompo = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BaseBodyCompo"));

	RootComponent = BaseBodyCompo;
}

// Called when the game starts or when spawned
void ABS_BaseChar::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABS_BaseChar::Movement(float DeltaTime)
{
	
}

void ABS_BaseChar::Sprint(bool isrunnig)
{
	
}

void ABS_BaseChar::Jump()
{
	
}

void ABS_BaseChar::Crouch(bool isCrouch)
{
	
}

void ABS_BaseChar::Rotate(float DeltaTime)
{
	FRotator TargetROtation = Controller->GetControlRotation();
	SetActorRotation(FRotator(PitchRotate ? TargetROtation.Pitch:GetActorRotation().Pitch,
		YawRotate ? TargetROtation.Yaw:GetActorRotation().Yaw,
		RollRotate ? TargetROtation.Roll:GetActorRotation().Roll));
}

// Called every frame
void ABS_BaseChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate(DeltaTime);
	Movement(DeltaTime);
}

// Called to bind functionality to input
void ABS_BaseChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputCompo = PlayerInputComponent;
}

