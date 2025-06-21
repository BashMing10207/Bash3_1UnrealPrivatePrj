// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/BSBashMovement.h"

#include "BS_BaseChar.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UBSBashMovement::UBSBashMovement()
{
	
}


// Called when the game starts
void UBSBashMovement::BeginPlay()
{
	Super::BeginPlay();
	if (OwningChar == nullptr)
		OwningChar = Cast<ABS_BaseChar>(GetOwner());
	
}


// Called every frame
void UBSBashMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UBSBashMovement::Movement(float DeltaTime,FVector InputDir)
{
	Movement(DeltaTime,InputDir,MaxSpeed,Accelation);
}

void UBSBashMovement::Movement(float DeltaTime, FVector InputDir, float MaxSpeed1, float Accel1)
{
	
    // --- 1) Ground 체크 (OverlapSphere + SweepSphere) ---
    FHitResult Hit;
    const FVector ActorLoc     = OwningChar-> GetActorLocation();
    const FVector SphereCenter = ActorLoc - FVector(0, 0, CharHeight * 0.5f+0.11f);
    const FCollisionShape Sphere = FCollisionShape::MakeSphere(CharRadius - 0.1f);
	FCollisionQueryParams Params;
	
	Params.AddIgnoredActor(OwningChar);

	
    // 느슨한 판정 → 점프 가능 여부
    bCanJump = GetWorld()->OverlapAnyTestByChannel(
         SphereCenter-FVector(0, 0, 0.05f), FQuat::Identity, GroundChannel, Sphere,Params);

    // 단단한 판정 → 완전 접지 여부
    bIsGround = GetWorld()->SweepSingleByChannel(
        Hit,
        ActorLoc,
       SphereCenter,
        FQuat::Identity,
        GroundChannel,
        
        Sphere,
        Params
    );

	// --- 4) 월드 방향 기준 입력 벡터 계산 (Unity: quaternion * input) ---
	FRotator ControlRot      = OwningChar->GetControlRotation();
	FVector Input3D_World    = OwningChar->BaseBodyCompo->GetComponentRotation().Quaternion() * InputDir;

	// MovementInput = Input3D_World;
	
	
    // --- 2) 현재 속도 가져오기 ---
    FVector CurrVel = OwningChar->BaseBodyCompo->GetComponentVelocity();

	// --- 3) 접지 중일 때만 감속 & 입력 투영 ---
	if (bIsGround)
	{
		// 3.1) 수평 속도 Lerp 감속 (Unity: Lerp(horizontalSpeed, zero, damp * dt))
		FVector HorVel(CurrVel.X, CurrVel.Y, 0.f);
		FVector NewHor = FMath::Lerp(
			HorVel,
			FVector::ZeroVector,
			Dampening * GetWorld()->DeltaTimeSeconds
		);

		CurrVel = FVector(NewHor.X, NewHor.Y, CurrVel.Z);
		OwningChar->BaseBodyCompo->SetPhysicsLinearVelocity(CurrVel, false);
		// // // 3.2) 입력 벡터를 지면 법선에 투영 (Unity: ProjectOnPlane)
		// FVector Input3D(Input3D_World.X, Input3D_World.Y, 0.f);
		FVector Projected = FVector::VectorPlaneProject(Input3D_World, Hit.Normal.GetSafeNormal());
		Input3D_World = Projected;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, ( FString::Printf(TEXT("$x %f y %f z %f"),Hit.Normal.X,Hit.Normal.Y,Hit.Normal.Z)));
	}

   
    // --- 5) Unity의 Vector3.Project(input, velocity) 재현 ---
    FVector ProjOnVel(0.f);
    if (CurrVel.SizeSquared() > SMALL_NUMBER)
    {
        ProjOnVel = CurrVel.ProjectOnTo(Input3D_World.GetSafeNormal());
    }

    // --- 6) Lerp 계수 계산 및 movDir 생성 ---
    float CombinedMag = (ProjOnVel + Input3D_World).Size();  
    float Factor      = FMath::Clamp( FMath::Lerp(1.f, 0.f, CombinedMag / MaxSpeed1),0,1);  
    FVector DeltaVel  = Input3D_World * Factor * Accel1;  
	OwningChar->BaseBodyCompo->AddImpulse(DeltaVel,NAME_None,true);
    // --- 7) 최종 속도에 더해주기 (RigidBody.velocity += movDir) ---
	//BaseBodyCompo->SetPhysicsLinearVelocity(DeltaVel, true);
	InputDir = FVector::ZeroVector;
}

