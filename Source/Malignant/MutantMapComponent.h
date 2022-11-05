// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MutantCharacter.h"
#include "BoneBladeMutantCharacter.h"
#include "FourArmMutantCharacter.h"
#include "MutantMapComponent.generated.h"


//Storage for all mutant class references 
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

	//TMap to hold mutant class references
	UPROPERTY()
		TMap<TEnumAsByte<EMutantState>, TSubclassOf<AMutantCharacter>> MutantClassMap;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Accessor for MutantClassMap
	UFUNCTION(BlueprintCallable)
		TMap<TEnumAsByte<EMutantState>, TSubclassOf<AMutantCharacter>> GetMap();

		
};
