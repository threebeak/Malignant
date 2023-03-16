// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MixingTableComponent.generated.h"

class UMutagenBase;
class UCompoundBase;
class AMutantCharacter;

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


UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MALIGNANT_API UMixingTableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <FMutagens> AvailableMutagens;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <FCompounds> AvailableCompounds;

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
