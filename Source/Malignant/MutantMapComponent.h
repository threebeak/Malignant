// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MutantCharacter.h"
#include "BoneBladeMutantCharacter.h"
#include "FourArmMutantCharacter.h"
#include "MutantMapComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MALIGNANT_API UMutantMapComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMutantMapComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		TMap<TEnumAsByte<EMutantState>, TSubclassOf<AMutantCharacter>> MutantClassMap;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		TMap<TEnumAsByte<EMutantState>, TSubclassOf<AMutantCharacter>> GetMap();

		
};
