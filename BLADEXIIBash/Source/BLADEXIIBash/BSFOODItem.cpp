// Fill out your copyright notice in the Description page of Project Settings.


#include "BSFOODItem.h"

ABSItemObjBase* ABSFOODItem::UseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller)
{
	return Super::UseItemObj_Implementation(UsingArm, Caller);
}

ABSItemObjBase* ABSFOODItem::ALTUseItemObj_Implementation(ABSArmComponent_C* UsingArm, AActor* Caller)
{
	return Super::ALTUseItemObj_Implementation(UsingArm, Caller);
}
