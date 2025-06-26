// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/IBSInteractiveable.h"
#include "Interface/IKeyUseable.h"
#include "BSDoor.generated.h"

UCLASS()
class BLADEXIIBASH_API ABSDoor : public AActor,public IIBSInteractiveable,public IIKeyUseable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABSDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
