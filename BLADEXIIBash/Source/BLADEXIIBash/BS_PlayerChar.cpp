// Fill out your copyright notice in the Description page of Project Settings.


#include "BS_PlayerChar.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "MaterialHLSLTree.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "BSArmComponent.h"

ABS_PlayerChar::ABS_PlayerChar()
{
	SpringArmCompo = CreateDefaultSubobject<USpringArmComponent>("SpringArmCOmpo");
	SpringArmCompo->SetupAttachment(RootComponent);
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmCompo);

	
	
	
	TempArmTarget1 = CreateDefaultSubobject<UStaticMeshComponent>("TempArmTarget1");
	TempArmTarget1->SetupAttachment(CameraComp);
	TempArmTarget2 = CreateDefaultSubobject<UStaticMeshComponent>("TempArmTarget2");
	TempArmTarget2->SetupAttachment(CameraComp);
}

void ABS_PlayerChar::BeginPlay()
{
	Super::BeginPlay();

	ArmComponents[0]->SetUpBodyJoint(BaseBodyCompo);
	ArmComponents[1]->SetUpBodyJoint(BaseBodyCompo);
}

void ABS_PlayerChar::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (APlayerController* PC = Cast<APlayerController>(NewController))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Sub = 
				LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				Sub->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void ABS_PlayerChar::Sprint(bool isrunning)
{
	Super::Sprint(isrunning);
}

void ABS_PlayerChar::Jump()
{
	Super::Jump();
}

void ABS_PlayerChar::Crouch(bool isCrouch)
{
	Super::Crouch(isCrouch);
}

void ABS_PlayerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// MoveAction (Vector2D)
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABS_PlayerChar::Move);

		// LookAction (Vector2D)
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABS_PlayerChar::Look);

		// JumpAction (Started/Completed)
		EIC->BindAction(JumpAction, ETriggerEvent::Started,   this, &ABS_PlayerChar::JumpPressed);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ABS_PlayerChar::JumpReleased);
	}
}

void ABS_PlayerChar::Move(const FInputActionValue& Value)
{
    // Unity: RPlayerMana.Instance.playerInput.movement
    MovementInput = FVector(Value.Get<FVector2D>().X, Value.Get<FVector2D>().Y,0);
}
void ABS_PlayerChar::Look(const FInputActionValue& Value)
{
	FVector2D Axis = Value.Get<FVector2D>();
	AddControllerYawInput  (Axis.X);
	AddControllerPitchInput(Axis.Y);
}
void ABS_PlayerChar::JumpPressed(const FInputActionValue& /*Value*/)
{
    if (bCanJump)
    {
        // Unity: rigidbody.AddForce(transform.up * _jumpPower, ForceMode.Impulse)
        BaseBodyCompo->AddImpulse(FVector::UpVector * JumpImpulse, NAME_None, true);
    }
}

void ABS_PlayerChar::JumpReleased(const FInputActionValue& /*Value*/)
{
    // 필요시 점프 홀드 로직 추가
}

void ABS_PlayerChar::Movement(float DeltaTIme)
{
     Super::Movement(DeltaTIme);


    // --- 1) Ground 체크 (OverlapSphere + SweepSphere) ---
    FHitResult Hit;
    const FVector ActorLoc     = GetActorLocation();
    const FVector SphereCenter = ActorLoc - FVector(0, 0, PlayerHeight * 0.5f+0.11f);
    const FCollisionShape Sphere = FCollisionShape::MakeSphere(PlayerRadius - 0.1f);
	FCollisionQueryParams Params;
	
	Params.AddIgnoredActor(this);

	
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
	FRotator ControlRot      = GetControlRotation();
	FVector Input3D_World    = BaseBodyCompo->GetComponentRotation().Quaternion() * MovementInput;

	// MovementInput = Input3D_World;
	
	
    // --- 2) 현재 속도 가져오기 ---
    FVector CurrVel = BaseBodyCompo->GetComponentVelocity();

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
		BaseBodyCompo->SetPhysicsLinearVelocity(CurrVel, false);
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
    float Factor      = FMath::Clamp( FMath::Lerp(1.f, 0.f, CombinedMag / MaxSpeed),0,1);  
    FVector DeltaVel  = Input3D_World * Factor * Acceleration;  
	BaseBodyCompo->AddImpulse(DeltaVel,NAME_None,true);
    // --- 7) 최종 속도에 더해주기 (RigidBody.velocity += movDir) ---
	//BaseBodyCompo->SetPhysicsLinearVelocity(DeltaVel, true);
	MovementInput = FVector::ZeroVector;
}

void ABS_PlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Movement(DeltaTime);

	// for (int i = 0; i < ArmComponents.Num(); i++)
	// {
	//if (ArmComponents.Num() > 0)
	{
		ArmComponents[0]->SetHandPosTarget(BaseBodyCompo->GetComponentTransform(),TempArmTarget1->GetComponentTransform());
		ArmComponents[1]->SetHandPosTarget(BaseBodyCompo->GetComponentTransform(),TempArmTarget2->GetComponentTransform());
	}
	//}

}
