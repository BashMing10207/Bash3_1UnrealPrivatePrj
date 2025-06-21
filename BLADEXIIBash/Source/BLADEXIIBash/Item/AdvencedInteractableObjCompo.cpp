// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvencedInteractableObjCompo.h"

#include <string>

#include "CustomComponents/PTActionNoiseComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "CustomComponents/PTActionNoiseComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "ProfilingDebugging/CookStats.h"


// Sets default values for this component's properties
UAdvencedInteractableObjCompo::UAdvencedInteractableObjCompo()
{
	//COllsionSOund BInd
	
	
}

void UAdvencedInteractableObjCompo::BeginPlay()
{
	if (IsValid(this) && !!this)
	{
		MeshCompo = Cast<UMeshComponent>(GetOwner()->GetComponentByClass(UMeshComponent::StaticClass()));

		//SkeletalMeshCompo = Cast<UMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	
		if (bOnDestorySpawn)
		{
			GetOwner()->OnDestroyed.AddDynamic(this,&UAdvencedInteractableObjCompo::OnDestorySpawn);
		}
	
		Super::BeginPlay();

		if (!!MeshCompo)
			SetMeshEvent(MeshCompo);

	
		GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UAdvencedInteractableObjCompo::OnGetDamageEvent_Implementation);

		//GetOwner()->OnDestroyed.AddDynamic(this,&UAdvencedInteractableObjCompo::OnDestorySpawn);

	}
}

void UAdvencedInteractableObjCompo::SetEnabledFunction(bool bIsAttackable, bool bIsCollideDamaeable, bool bIsCollideSoundable,
	bool bIsDamageSoundable, bool bIsGetDamageable, bool bIsDestroySpawnable, bool bIsCollideEffectable)
{
	bOnCollisionAttack = bIsAttackable;
	bOnCollisionDamage = bIsCollideDamaeable;
	bOnCollisionSound = bIsCollideSoundable;
	bOnDamageSound = bIsDamageSoundable;
	bDamageable = bIsDestroySpawnable;
	bOnDestorySpawn = bIsDestroySpawnable;
	bOnCollideEffect = bIsCollideEffectable;
}

void UAdvencedInteractableObjCompo::OnCollisionEvent_Implementation(UPrimitiveComponent* HitComponent,
                                                                    AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (CoolTime != 0.f)
	{
		if (!bOnCollideEventCoolDown)
			return;

		bOnCollideEventCoolDown = false;
		GetWorld()->GetTimerManager().SetTimer(CollideCooldownTimerHandle,this,
			&UAdvencedInteractableObjCompo::EnableCollideEvent,CoolTime,false);
	}
	
	float Velocity = NormalImpulse.Size();


	if (MeshCompo != nullptr)
	{
		Velocity /= MeshCompo->GetMass();
	}
	
	if (bOnCollisionDamage)
	{
		OnCollisionGetDamage(Velocity);
	}

	if (bOnCollisionSound)
	{
		OnCollisionSound(Velocity);
	}

	if (bOnCollisionAttack)
	{
		OnCollisionAttack(Velocity,OtherActor, Hit);
	}
	
	if (bOnCollideEffect)
	{
		OnCollideEffect(Velocity,HitComponent,OtherActor,Hit);
	}
}

void UAdvencedInteractableObjCompo::OnGetDamageEvent_Implementation(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (bOnDamageSound)
	{
		OnDamageSound();
	}

	if (bDamageable)
	{
		Health -= Damage;
		if (Health <= 0)
		{
			GetOwner()->Destroy();
		}
	}
}

void UAdvencedInteractableObjCompo::OnCollisionGetDamage(float speed)
{
	float Velocity =speed;///MeshCompo->GetMass();//(MeshCompo->GetComponentVelocity()-tmpVelocity).ProjectOnToNormal(NormalImpulse.GetSafeNormal());
	if (MinSpeedToAttack < Velocity)
	{
		
		if (!!GetOwner())
		{
			AController* MyOwnerInstigator = GetOwner()->GetInstigatorController();
			UClass* DamageTypeClass = UDamageType::StaticClass();
			UGameplayStatics::ApplyDamage(GetOwner(),FMath::Lerp(MinSpeedToGetDamage,MaxSpeedToGetDamage,
				FMath::GetRangePct(MinSpeedToGetDamage, MaxSpeedToGetDamage,speed)),
				MyOwnerInstigator, GetOwner(), DamageTypeClass);
		}
	}
}

void UAdvencedInteractableObjCompo::OnCollisionSound(float speed)
{
	if ((speed > MinSpeedToSound) and ((!!CollisionSoundCue)and (!!CollisionSoundAttenuatiom)))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, std::to_string(speed).c_str());
		
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), CollisionSoundCue, GetOwner()->GetActorLocation(),
	FRotator::ZeroRotator,FMath::Lerp(MinCollideVolume,MaxCollideVolume,
		(speed-MinSpeedToSound)/(MaxSpeedToSound-MinSpeedToSound)),
			FMath::RandRange(0.8f,1.2f), 0.f,CollisionSoundAttenuatiom);
		UPTActionNoiseComponent::SpawnNoiseAtLocation(GetWorld(), GetOwner()->GetActorLocation(), CollideSoundRange, bCanCollideSoundIgnoreWall, false);
	
	}
	
}

void UAdvencedInteractableObjCompo::OnDamageSound()
{
	if ((!!DamageSoundAttenuatiom) & (!!DamageSoundCue))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DamageSoundCue, GetOwner()->GetActorLocation(),FRotator::ZeroRotator,
		DamagedSoundVolume,FMath::RandRange(0.8f,1.2f),0.0f,DamageSoundAttenuatiom);
		UPTActionNoiseComponent::SpawnNoiseAtLocation(GetWorld(), GetOwner()->GetActorLocation(), DamagedSoundRange, bCanDamageSoundIgnoreWall, false);
	}
	
}

void UAdvencedInteractableObjCompo::OnCollisionAttack(float speed, AActor* OtherActor, const FHitResult& Hit)
{
	float Velocity =speed;//MeshCompo->GetMass();//(MeshCompo->GetComponentVelocity()-tmpVelocity).ProjectOnToNormal(NormalImpulse.GetSafeNormal());
	if (MinSpeedToAttack < Velocity)
	{
		
		if (OtherActor)
		{
			// if (Hit.BoneName == "Head"
			// 	and
			// 	OtherActor->GetClass()->ImplementsInterface(UPTEnemyInfo::StaticClass()))
			// {
			// 	IPTEnemyInfo::Execute_GiveStun(OtherActor);
			// }
			AController* MyOwnerInstigator = GetOwner()->GetInstigatorController();
			UClass* DamageTypeClass = UDamageType::StaticClass();
			UGameplayStatics::ApplyDamage(OtherActor,FMath::Lerp(MinCollideAttackAmount,MaxCollideAttackAmount,
				(speed-MinSpeedToSound)/(MaxSpeedToSound-MinSpeedToSound)),
				MyOwnerInstigator, GetOwner(), DamageTypeClass);
		}
	}
}

void UAdvencedInteractableObjCompo::OnDestorySpawn(AActor* DestroyedActor)
{
	if ((!!DestorySoundCue) & (!!DestroySoundAttenuatiom))
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DestorySoundCue, GetOwner()->GetActorLocation(),FRotator::ZeroRotator,
		DamagedSoundVolume,FMath::RandRange(0.8f,1.2f),0.0f,DamageSoundAttenuatiom);
	if (!!DestroySpawnActor)
		GetWorld()->SpawnActor(DestroySpawnActor,&GetOwner()->GetTransform());
	if (!!DestroyEffect)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),DestroyEffect, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);

	UPTActionNoiseComponent::SpawnNoiseAtLocation(GetWorld(), GetOwner()->GetActorLocation(), DamagedSoundRange, bCanDamageSoundIgnoreWall, false);

}

void UAdvencedInteractableObjCompo::OnCollideEffect(float Speed, UPrimitiveComponent* HitComponent, AActor* OtherActor,
	const FHitResult& Hit)
{
	if (Speed > MinEffectSpeed)
		if (!!CollideEffect)
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),CollideEffect, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);
}

void UAdvencedInteractableObjCompo::SetMeshEvent(UMeshComponent* Mesh)
{
	Mesh->OnComponentHit.AddDynamic(this,&UAdvencedInteractableObjCompo::OnCollisionEvent_Implementation);
}


float UAdvencedInteractableObjCompo::CollisionPower(FVector NormalImpulse, float MinSpeed, float maxSpeed,
                                                   float MinDamage,float MaxDamage,float Mass)
{
	FVector Velocity =NormalImpulse/Mass;//MeshCompo->GetMass//(MeshCompo->GetComponentVelocity()-tmpVelocity).ProjectOnToNormal(NormalImpulse.GetSafeNormal());
	if (MinSpeed < Velocity.Size())
	{
		return FMath::Lerp(MinDamage,MaxDamage,Velocity.Size()/maxSpeed);
	}
	
	return 0.f;
}

void UAdvencedInteractableObjCompo::EnableCollideEvent()
{
	bOnCollideEventCoolDown = true;
}
