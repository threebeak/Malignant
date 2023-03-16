// Fill out your copyright notice in the Description page of Project Settings.


#include "MixingTableComponent.h"
#include "MutantCharacter.h"
#include "MutagenBase.h"
#include "CompoundBase.h"

// Sets default values for this component's properties
UMixingTableComponent::UMixingTableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

TSubclassOf<AMutantCharacter> UMixingTableComponent::Mix(TSubclassOf<UMutagenBase> MutagenClass, TArray<TSubclassOf<UCompoundBase>> Ingredients, bool &isValid)
{
	TSubclassOf<AMutantCharacter> Result = AMutantCharacter::StaticClass();

	isValid = false;

	for (auto Element : MutagenClass.GetDefaultObject()->RequiredIngredients)
	{
		if (Ingredients.Find(Element) == INDEX_NONE)
		{
			return Result;
		}
	}
	Result = MutagenClass.GetDefaultObject()->MutantClass;

	isValid = true;
	return Result;

}


// Called when the game starts
void UMixingTableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMixingTableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

