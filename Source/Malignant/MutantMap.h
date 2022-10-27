// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MutantBase.h"
#include "MutantMap.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MALIGNANT_API UMutantMap : public UObject
{
	GENERATED_BODY()

public:

	UMutantMap();

	UPROPERTY(BlueprintReadOnly)
		TMap<TEnumAsByte<EMutantState>, AMutantBase*> MMutants;

	UPROPERTY()
		AMutantBase* Mutant1;
	UPROPERTY()
		AMutantBase* Mutant2;
	UPROPERTY()
		AMutantBase* Mutant3;
};
