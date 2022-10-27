// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "MutantBase.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MALIGNANT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	FHitResult LookResult;

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
		UCameraComponent* MainCamera;


	//Data for Line Traces
	UPROPERTY(EditAnywhere, Category = Traces)
		float LookDistance = 500;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		AMutantBase* PlayerMutant;

	void Transform();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void Jump();
	void SetMutant(AMutantBase* NewMutant);

private:

	//Will probably need to have a return value later
	void HandleTrace();
};
