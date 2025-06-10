// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/PTActionNoiseComponent.h"
#include "Interface/PTISoundListenable.h"
#include "Engine/OverlapResult.h"
#include "DrawDebugHelpers.h"

void UPTActionNoiseComponent::SpawnNoiseAtLocation(const UObject* WorldContextObject,FVector NoiseSpawnPoint, float NoiseRange, bool IgnoreWall, bool bISDrawDebug)
{
	TArray<FOverlapResult> OverlapResults;

	UWorld* ThisWorld = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	ThisWorld->OverlapMultiByChannel(OverlapResults, NoiseSpawnPoint,FQuat::Identity, ECC_EngineTraceChannel2, FCollisionShape::MakeSphere(NoiseRange));

	for (auto& OverlapResult : OverlapResults)
	{
		if (AActor* OverlapActor = OverlapResult.GetActor())
		{
			if (OverlapActor->GetClass()->ImplementsInterface(UPTISoundListenable::StaticClass()))
			{
				if (IgnoreWall)
				{
					IPTISoundListenable::Execute_ListenSound(OverlapActor, NoiseSpawnPoint);
				}
				else
				{
					FHitResult HitResult;
					bool bHit = ThisWorld->LineTraceSingleByChannel(
						HitResult,
						NoiseSpawnPoint,
						OverlapActor->GetActorLocation(),
						ECC_EngineTraceChannel2
					);

					if (!bHit || HitResult.GetActor() == OverlapActor)
					{
						IPTISoundListenable::Execute_ListenSound(OverlapActor, NoiseSpawnPoint);
					}
				}
			}
		}
	}


	if (bISDrawDebug)
	{
		DrawDebugSphere(ThisWorld, NoiseSpawnPoint, NoiseRange, 24, FColor::Red, false, 5.f);
	}
}