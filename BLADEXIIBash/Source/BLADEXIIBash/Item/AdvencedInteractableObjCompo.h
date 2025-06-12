#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdvencedInteractableObjCompo.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLADEXIIBASH_API UAdvencedInteractableObjCompo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAdvencedInteractableObjCompo();
	
	UFUNCTION(BlueprintCallable)
	virtual void SetMeshEvent(UMeshComponent* Mesh);

	UFUNCTION(BlueprintCallable)
	void SetEnabledFunction(bool bIsAttackable=false, bool bIsCollideDamaeable=false, bool bIsCollideSoundable=false, bool bIsDamageSoundable=false,
		bool bIsGetDamageable=false,bool bIsDestroySpawnable=false, bool bIsCollideEffectable=false);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_GetDamageable")
	float Health = 4.f;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	virtual void OnCollisionEvent_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION(BlueprintCallable)
	virtual void OnGetDamageEvent_Implementation(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION(BlueprintCallable)
	virtual void OnCollisionGetDamage(float speed);
	UFUNCTION(BlueprintCallable)
	virtual void OnCollisionSound(float speed);
	UFUNCTION(BlueprintCallable)
	virtual void OnDamageSound();
	UFUNCTION(BlueprintCallable)
	virtual void OnCollisionAttack(float speed, AActor* OtherActor,const FHitResult& Hit);
	UFUNCTION(BlueprintCallable)
	virtual void OnDestorySpawn(AActor* DestroyedActor);
	UFUNCTION(BlueprintCallable)
	virtual void OnCollideEffect(float Speed,UPrimitiveComponent* HitComponent, AActor* OtherActor, const FHitResult& Hit);

	float CollisionPower(FVector NormalImpulse, float MinSpeed, float maxSpeed,
	float MinDamage,float MaxDamage,float Mass);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_")
	TObjectPtr<UMeshComponent> MeshCompo;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_GetDamageable")
	bool bDamageable = true;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionGetDamage")
	bool bOnCollisionDamage = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionGetDamage")
	float MinSpeedToGetDamage = 420.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionGetDamage")
	float MaxSpeedToGetDamage = 1570.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionGetDamage")
	float MinCollideGetDamage = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionGetDamage")
	float MaxCollideGetDamage = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionSound")
	bool bOnCollisionSound = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionSound")
	float MinSpeedToSound = 400.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionSound")
	float MaxSpeedToSound = 1550.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionSound")
	float MinCollideVolume = 0.35f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionSound")
	float MaxCollideVolume = 1.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionSound")
	float CollideSoundRange = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionSound")
	TObjectPtr<class USoundCue> CollisionSoundCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionSound")
	TObjectPtr<class USoundAttenuation> CollisionSoundAttenuatiom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionSound")
	bool bCanCollideSoundIgnoreWall = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnDamageSound")
	bool bOnDamageSound = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnDamageSound")
	float DamagedSoundVolume = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnDamageSound")
	float DamagedSoundRange = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnDamageSound")
	TObjectPtr<class USoundCue> DamageSoundCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnDamageSound")
	TObjectPtr<class USoundAttenuation> DamageSoundAttenuatiom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnDamageSound")
	bool bCanDamageSoundIgnoreWall = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionAttack")
	bool bOnCollisionAttack = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionAttack")
	float MinSpeedToAttack = 450.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionAttack")
	float MaxSpeedToAttack = 1550.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionAttack")
	float MinCollideAttackAmount = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollisionAttack")
	float MaxCollideAttackAmount = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnDestroySpawns")
	bool bOnDestorySpawn = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnDestroySpawns")
	float DestroySoundVolume = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnDestroySpawns")
	TObjectPtr<class USoundCue> DestorySoundCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnDestroySpawns")
	TObjectPtr<class USoundAttenuation> DestroySoundAttenuatiom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnDestroySpawns")
	TSubclassOf<AActor> DestroySpawnActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnDestroySpawns")
	TObjectPtr<class UNiagaraSystem> DestroyEffect;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollideEffect")
	bool bOnCollideEffect = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollideEffect")
	float MinEffectSpeed = 550.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollideEffect")
	TObjectPtr<class UNiagaraSystem> CollideEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "_OnCollideEvent")
	bool bOnCollideEventCoolDown = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "_OnCollideEvent")
	float CoolTime = 0.025f;

	FTimerHandle CollideCooldownTimerHandle;

protected:
	void EnableCollideEvent();
};
