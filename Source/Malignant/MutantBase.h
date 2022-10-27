// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "MutantBase.generated.h"

UENUM(BlueprintType)
enum EMutantState { Human = 0, Tall, Normal, Short };

USTRUCT(BlueprintType)
struct FMutantStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		float Height = 0;
	UPROPERTY(EditAnywhere)
		float Radius = 0;
	UPROPERTY(EditAnywhere)
		float Health = 0;
	UPROPERTY(EditAnywhere)
		float Defense = 0;
	UPROPERTY(EditAnywhere)
		float MovementSpeed = 0;
	UPROPERTY(EditAnywhere)
		float AttackSpeed = 0;
};

UCLASS()
class MALIGNANT_API AMutantBase : public AActor
{
	GENERATED_BODY()

private:


	FMutantStats BaseStats;
	

public:	
	// Sets default values for this actor's properties
	AMutantBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Set stats for Mutant
	void SetBaseStats(float Height, float Radius, float Health, float Defense, float MoveSpeed, float AttackSpeed);

	UPROPERTY()
		UStaticMeshComponent* MutantMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void LightAttack();
	virtual void HeavyAttack();
	virtual void Ability();

	UFUNCTION(BlueprintCallable)
		UStaticMesh* GetMutantMesh();

	//Set stats for Mutant
	UFUNCTION(BlueprintCallable)
		FMutantStats GetBaseStats();

};
