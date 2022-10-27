// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MutantBase.h"

/**
 * 
 */
class MALIGNANT_API MutantMap
{
public:
	MutantMap();
	~MutantMap();

	UPROPERTY(BlueprintVisible)
		TMap<EMutantState, AMutantBase*> MMutants;
};
