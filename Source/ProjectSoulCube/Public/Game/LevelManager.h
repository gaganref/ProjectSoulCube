// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"

DECLARE_DYNAMIC_DELEGATE(FPreGenerateGridData);
DECLARE_DYNAMIC_DELEGATE(FPostGenerateGridData);
DECLARE_DYNAMIC_DELEGATE(FPreGenerateLevel);
DECLARE_DYNAMIC_DELEGATE(FPostGenerateLevel);

UCLASS()
class PROJECTSOULCUBE_API ALevelManager : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = "Level Data", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UGridDataGenerator> GridDataRef;
	
	UPROPERTY(Category = "Level Data", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AGameAlter> AlterRef;

	UPROPERTY(Category = "Level Data", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class APlayerStart> PlayerStartRef;
	
	UPROPERTY(Category = "Level Data", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AGameLevelBounds> LevelBoundsRef;

	UPROPERTY(Category = "Level Data", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ALevelGenerator> LevelGeneratorRef;
	
	UPROPERTY(Category = "Level Data", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AObjectsGenerator> ObjectsGeneratorRef;

private:
	FPreGenerateGridData PreGenerateGridDataDelegate;
	
	FPostGenerateGridData PostGenerateGridDataDelegate;
	
	FPreGenerateLevel PreGenerateLevelDelegate;
	
	FPostGenerateLevel PostGenerateLevelDelegate;
	
public:
	// Sets default values for this actor's properties
	ALevelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	FORCEINLINE TObjectPtr<class UGridDataGenerator> GetGridData() const { return GridDataRef; }
	
	FORCEINLINE TObjectPtr<class AGameAlter> GetAlterRef() const { return AlterRef; }

	FORCEINLINE TObjectPtr<class APlayerStart> GetPlayerStartRef() const { return PlayerStartRef; }
	
	FORCEINLINE TObjectPtr<class AGameLevelBounds> GetLevelBoundsRef() const { return LevelBoundsRef; }
	
	FORCEINLINE TObjectPtr<class ALevelGenerator> GetLevelGeneratorRef() const { return LevelGeneratorRef; }
	
	FORCEINLINE  TObjectPtr<class AObjectsGenerator> GetObjectsGeneratorRef() const { return ObjectsGeneratorRef; }
};
