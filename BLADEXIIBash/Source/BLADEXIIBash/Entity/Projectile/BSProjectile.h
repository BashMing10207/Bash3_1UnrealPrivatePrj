// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSProjectile.generated.h"

UCLASS()
class BLADEXIIBASH_API ABSProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABSProjectile();
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	class USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	UFUNCTION(BlueprintCallable)
	class UProjectileMovementComponent* GetProjectileMovement()
	{
		return ProjectileMovement;
	}
};
