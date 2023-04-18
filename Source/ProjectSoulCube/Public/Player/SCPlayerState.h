// // Fill out your copyright notice in the Description page of Project Settings.
//
// #pragma once
//
// #include "CoreMinimal.h"
// #include "AbilitySystemInterface.h"
// #include "GameFramework/PlayerState.h"
// #include "SCPlayerState.generated.h"
//
// struct FOnAttributeChangeData;
//
// UCLASS()
// class PROJECTSOULCUBE_API ASCPlayerState : public APlayerState, public IAbilitySystemInterface
// {
// 	GENERATED_BODY()
//
// public:
// 	
// 	// Sets default values for this actor's properties
// 	ASCPlayerState();
//
// protected:
// 	
// 	// Called when the game starts or when spawned
// 	virtual void BeginPlay() override;
//
// public:
// 	
// 	// Called every frame
// 	virtual void Tick(float DeltaTime) override;
//
// protected:
//
// 	UPROPERTY()
// 	TObjectPtr<class USCAbilitySystemComponent> AbilitySystemComponent;
//
// 	UPROPERTY()
// 	TObjectPtr<class USCHealthAttributeSet> HealthAttributeSet;
// 	
// 	FDelegateHandle HealthChangedDelegateHandle;
// 	FDelegateHandle MaxHealthChangedDelegateHandle;
// 	FDelegateHandle HealthRegenRateChangedDelegateHandle;
// 	
// public:
//
// 	// Implement IAbilitySystemInterface
//     class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
// 	
//     class USCHealthAttributeSet* GetHealthAttributeSet() const;
//
// protected:
//
// 	// Attribute changed callbacks
// 	virtual void HealthChanged(const FOnAttributeChangeData& Data);
// 	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
// 	virtual void HealthRegenRateChanged(const FOnAttributeChangeData& Data);
//
// public:
//
// 	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState")
// 	bool IsAlive() const;
// 	
// 	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState|Attributes")
// 	float GetHealth() const;
//
// 	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState|Attributes")
// 	float GetMaxHealth() const;
//
// 	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDPlayerState|Attributes")
// 	float GetHealthRegenRate() const;
// };
