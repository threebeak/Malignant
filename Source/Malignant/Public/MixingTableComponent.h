// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MixingTableComponent.generated.h"

class UMutagenBase;
class UCompoundBase;
class AMutantCharacter;
struct FMutagens;
struct FCompounds;


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MALIGNANT_API UMixingTableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	//True if a potion has already been created
	UPROPERTY(BlueprintReadWrite)
		bool bPotionIsMade;

	//True if the potion has been made and not drank
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bPotionIsAvailable;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetAvailableMutagens(TArray<FMutagens>& AvailableMutagens);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetAvailableCompounds(TArray<FCompounds>& AvailableCompounds);

	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<AMutantCharacter> MutantClass;

	// Sets default values for this component's properties
	UMixingTableComponent();

	UFUNCTION(BlueprintCallable)
	TSubclassOf<AMutantCharacter> Mix(TSubclassOf<UMutagenBase> MutagenClass, TArray<TSubclassOf<UCompoundBase>> Ingredients, bool &isValid);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
