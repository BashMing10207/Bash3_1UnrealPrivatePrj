// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/CustomAI/PTBashAI.h"

#include "Algo/RandomShuffle.h"

// Sets default values
UPTBashAI::UPTBashAI()
{
 
}

// Called when the game starts or when spawned
void UPTBashAI::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector UPTBashAI::BashPathFind()
{
	FVector MyLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation = MyTargetLocation;

	FVector BestDirection = FVector::ZeroVector;
	float MinDistance = FLT_MAX;
	
	// 8방향 정의
	TArray<FVector> Directions = {
		FVector::ForwardVector,
		FVector::BackwardVector,
		FVector::RightVector,
		FVector::LeftVector,
		(FVector::ForwardVector + FVector::RightVector).GetSafeNormal(),
		(FVector::ForwardVector + FVector::LeftVector).GetSafeNormal(),
		(FVector::BackwardVector + FVector::RightVector).GetSafeNormal(),
		(FVector::BackwardVector + FVector::LeftVector).GetSafeNormal()
	};

	for (const FVector& Dir : Directions)
	{
		FVector CheckPos = MyLocation + Dir * MoveDistance;

		// 충돌 검사
		FHitResult Hit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(GetOwner());

		bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, MyLocation+FVector::UpVector*15.f, CheckPos, ECC_Visibility, Params);

		if (!bHit && !IsRecentlyVisited(CheckPos))
		{
			float DistanceToTarget = FVector::Dist(CheckPos, TargetLocation);
			if (DistanceToTarget < MinDistance)
			{
				MinDistance = DistanceToTarget;
				BestDirection = Dir;
			}
		}
	}

	if (!BestDirection.IsNearlyZero())
	{
		FVector NewDir = BestDirection;
		//SetActorLocation(NewLocation);
		
		
		LastMoveDirection = BestDirection;
		VisitedPositions.Add(MyLocation);
		if (VisitedPositions.Num() > 32) // 루프 방지를 위한 제한된 기억
		{
			VisitedPositions.RemoveAt(0);
		}

		// 디버그
		DrawDebugLine(GetWorld(), MyLocation, MyLocation + BestDirection * 100.0f, FColor::Green, false, 0.2f, 0, 2.0f);
		return NewDir;
	}


	// 2) 모서리 갇힘 시 방문 기록 초기화

	{
		if (rand() % 5 >= 2)
		VisitedPositions.Empty();  // 기록 초기화 :contentReference[oaicite:10]{index=10}
		// 역방향만 후보로 재설정
		if (!LastMoveDirection.IsNearlyZero())
		{
			return -LastMoveDirection;
			
		}
	}
	
	return FVector::ZeroVector;
}



bool UPTBashAI::IsRecentlyVisited(const FVector& Pos)
{
	for (const FVector& Visited : VisitedPositions)
	{
		if (FVector::Dist(Visited, Pos) < CheckRadius)
		{
			return true;
		}
	}
	return false;
}

