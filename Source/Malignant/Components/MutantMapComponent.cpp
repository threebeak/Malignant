// Fill out your copyright notice in the Description page of Project Settings.


#include "MutantMapComponent.h"

// Sets default values for this component's properties
UMutantMapComponent::UMutantMapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bAutoActivate = true;

	//Add class references to the map
	MutantClassMap.Add(EMS_Base, AMutantCharacter::StaticClass());
	MutantClassMap.Add(EMS_Bone, ABoneBladeMutantCharacter::StaticClass());
	MutantClassMap.Add(EMS_FourArm, AFourArmMutantCharacter::StaticClass());

}


// Called when the game starts
void UMutantMapComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMutantMapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//Accessor for MutantClassMap
TMap<TEnumAsByte<EMutantState>, TSubclassOf<AMutantCharacter>> UMutantMapComponent::GetMap()
{
	return MutantClassMap;
}
