// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "MutagenBase.generated.h"

/**
 * 
 */
class UCompoundBase;
class AMutantCharacter;

UCLASS(Blueprintable)
class MALIGNANT_API UMutagenBase : public UItemBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<TSubclassOf<UCompoundBase>> RequiredIngredients;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AMutantCharacter> MutantClass;
};
