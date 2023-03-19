// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MalignantGameInstanceBase.generated.h"

class UMutagenBase;
class UCompoundBase;
/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct FMutagens
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UMutagenBase> Mutagen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Amount;
};

USTRUCT(BlueprintType, Blueprintable)
struct FCompounds
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UCompoundBase> Compound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Amount;
};
UCLASS()
class MALIGNANT_API UMalignantGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <FMutagens> AvailableMutagens;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray <FCompounds> AvailableCompounds;

	UFUNCTION(BlueprintCallable)
		bool DecrementMutagen(TSubclassOf<UMutagenBase> MutagenClass);

	UFUNCTION(BlueprintCallable)
		bool DecrementCompound(TSubclassOf<UCompoundBase> MutagenClass);
	
};
