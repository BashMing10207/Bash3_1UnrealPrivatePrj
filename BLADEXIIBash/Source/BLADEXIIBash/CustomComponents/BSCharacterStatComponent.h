// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomData/BSCharacterStat.h"
#include "BSCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate , float /*CurrentHp*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate , const FBSCharacterStat& /*BaseStat*/ , const FBSCharacterStat& /*ModifierStat*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLADEXIIBASH_API UBSCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBSCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	
public:
	float ApplyDamage(float InDamage);

public:
	UFUNCTION(BlueprintCallable)
	FBSCharacterStat& GetBaseStat2() { return BaseStat; }
	UFUNCTION(BlueprintCallable)
	FBSCharacterStat& GetModifierStat2() { return ModifierStat; }
	
	FORCEINLINE float GetCurrentLevel() { return CurrentLevel; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	float GetCurrentStemina() { return CurrentStemina; }
	float GetCurrentHunger() {return CurrentHunger; }

	
	FORCEINLINE const FBSCharacterStat& GetBaseStat() { return BaseStat; }
	FORCEINLINE const FBSCharacterStat& GetModifierStat() { return ModifierStat; }
	FORCEINLINE FBSCharacterStat GetTotalStat() const  { return BaseStat + ModifierStat; }

public:
	void SetLevel(int32 NewLevel);
	void SetHp(float NewHp);
	void SetStemina(float NewStemina);
	void SetHunger(float NewHunger);

	FORCEINLINE void SetBaseStat(const FBSCharacterStat& InBaseStat)
	{
		BaseStat = InBaseStat;
		OnStatChanged.Broadcast(GetBaseStat(), GetModifierStat());
	}

	FORCEINLINE void SetModifierStat(const FBSCharacterStat& InModifierStat)
	{
		ModifierStat = InModifierStat;
		OnStatChanged.Broadcast(GetBaseStat() , GetModifierStat());
	}

	FORCEINLINE void AddBaseStat(const FBSCharacterStat& InAddBaseStat)
	{
		BaseStat = BaseStat + InAddBaseStat;
		OnStatChanged.Broadcast(GetBaseStat() , GetModifierStat());
	}

	FORCEINLINE void AddModifierStat(const FBSCharacterStat& InAddModifierStat)
	{
		ModifierStat = ModifierStat + InAddModifierStat;
		OnStatChanged.Broadcast(GetBaseStat() , GetModifierStat());
	}

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;
	FOnHpChangedDelegate OnSteminaChanged;
	FOnHpChangedDelegate OnHungerChanged;
	FOnStatChangedDelegate OnStatChanged;

protected:
	UPROPERTY(VisibleAnywhere , Category = Stat)
	float CurrentLevel;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentHp;
	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentStemina;
	UPROPERTY(VisibleAnywhere, Category = Stat)
	float CurrentHunger;
	UPROPERTY(VisibleAnywhere , Category = Stat)
	FBSCharacterStat BaseStat;

	UPROPERTY(VisibleAnywhere , Category = Stat)
	FBSCharacterStat ModifierStat;
};
