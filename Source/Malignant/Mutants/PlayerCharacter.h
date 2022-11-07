// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "../Interactables/Interactable.h"
#include "Engine/World.h"
#include "PlayerCharacter.generated.h"




UCLASS()
class MALIGNANT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	APlayerCharacter();


	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere)
		UCameraComponent* MainCamera;

	//Object currently being interacted with or viewed and interactable
		IInteractable* InteractingObject;

	//InteractingObject's assigned widget to be displayed Ex. "Press E to Interact"
	UPROPERTY()
		UUserWidget* DisplayWidget;

	//Default distance for line trace
	UPROPERTY(EditAnywhere, Category = Traces)
		float LookDistance = 200;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//Pointer to PlayerController to avoid casting
	UPROPERTY()
		APlayerController* PController;

	//Result from line trace
	FHitResult LookResult;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement Functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);
	void Jump();

	//Proxies for Enable/Disable Input
	void Lock();
	void Release(APlayerController* PCont);

	//Used to interact with IInteractables 
	virtual void Interact();

protected:

	//Handle LookResult and DisplayWidget
	void HandleTrace();
	void HandleDisplay(bool Visible);
};
