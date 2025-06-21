// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomComponents/BSCharacterStatComponent.h"
//#include "Singleton/BSGameSingleton.h"

// Sets default values for this component's properties
UBSCharacterStatComponent::UBSCharacterStatComponent()
{
	CurrentLevel = 1;
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UBSCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UBSCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(CurrentLevel);
	SetHp(BaseStat.MaxHp);
}

float UBSCharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PreHp = CurrentHp;
	InDamage -= BaseStat.Defence - ModifierStat.Defence;
	const float ActualDamage = FMath::Clamp<float>(InDamage , 0.0f , InDamage);

	SetHp(PreHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return ActualDamage;
}

void UBSCharacterStatComponent::SetLevel(int32 NewLevel)
{
	// CurrentLevel = FMath::Clamp(NewLevel , 1 , UBSGameSingleton::Get().GetCharacterMaxLevel());
	// SetBaseStat(UBSGameSingleton::Get().GetCharacterStat(CurrentLevel));
}

void UBSCharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp(NewHp , 0.0f , GetTotalStat().MaxHp);
	OnHpChanged.Broadcast(CurrentHp);
}

void UBSCharacterStatComponent::SetStemina(float NewStemina)
{
	CurrentStemina = FMath::Clamp(NewStemina , 0.0f , GetTotalStat().Stemina);

	OnSteminaChanged.Broadcast(NewStemina);
}

void UBSCharacterStatComponent::SetHunger(float NewHunger)
{
	CurrentHunger = FMath::Clamp(NewHunger , 0.0f , GetTotalStat().Hungry);

	OnHungerChanged.Broadcast(NewHunger);
}
