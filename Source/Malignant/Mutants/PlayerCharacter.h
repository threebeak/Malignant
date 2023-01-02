// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "../Interactables/Interactable.h"
#include "../MalignantEnums.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class UStaticMeshComponent;


UCLASS()
class MALIGNANT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()


	/* methods */
public:

	// Sets default values for this pawn's properties
	APlayerCharacter();

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

	//Attack method
	virtual void Attack();

	//toggles trace for mixing table flag, called from MixingTable within an overlap event callback
	void SetOverlappingTable(bool bIsOverlapping);


	/* members */
public:

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Traces)
	int TestOverlapping;


	/* methods */
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Handle LookResult and DisplayWidget
	void HandleTrace();
	void HandleDisplay(bool Visible);


	UFUNCTION(BlueprintImplementableEvent)
		void DetermineMovementStateBP();


	/* members */
protected:
	

	//Pointer to PlayerController to avoid casting
	UPROPERTY()
		APlayerController* PController;

	//Result from line trace
	FHitResult LookResult;


	/* methods */
private:

	void DetermineMovementState();



	/* members */
private:

	//Flag for enabled/disabling trace for mixing table
	bool bOverlappingTable;

	//Player movement state
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player States", meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<ECharacterMovementState> PlayerMovementState;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wall Run", meta = (AllowPrivateAccess = "true"))
	FVector WallRunDirection;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wall Run", meta = (AllowPrivateAccess = "true"))
	bool bWallRunning;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wall Run", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EWallRunSide> WallRunSide;
	


};
