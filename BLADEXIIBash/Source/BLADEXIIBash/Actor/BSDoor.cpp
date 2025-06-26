// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BSDoor.h"

// Sets default values
ABSDoor::ABSDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABSDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABSDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

