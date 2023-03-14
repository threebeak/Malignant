// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "MixingTable.generated.h"


class UUserWidget;

//To pass values to BottleSelect function
DECLARE_DELEGATE_OneParam(FBottleSelect, const int32)

UCLASS()
class MALIGNANT_API AMixingTable : public AActor, public IInteractable
{
	GENERATED_BODY()



	/* methods */
public:

	// Sets default values for this actor's properties
	AMixingTable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Primary function called when this object is interacted with. Overridden from IInteractable
	virtual bool Interact(AActor* CallingActor) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Initialize();

	void Initialize_Implementation();

	/* members */

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> WidgetClass;

public:

	UPROPERTY(EditAnywhere)
		UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere)
		UCameraComponent* TableCamera;

	/* methods */
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/* members */
protected:


	//Values for the interacting player and corresponding controller to recieve input
	UPROPERTY()
		APlayerCharacter* Player;
	UPROPERTY()
		APlayerController* Controller;


	/* methods */
private:


	/* members */
private:



	
};
