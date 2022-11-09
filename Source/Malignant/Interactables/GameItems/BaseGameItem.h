// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interactable.h"
#include "BaseGameItem.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class MALIGNANT_API ABaseGameItem : public AActor, public IInteractable
{
	GENERATED_BODY()

	// methods 
public:

	// Sets default values for this actor's properties
	ABaseGameItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual bool Interact(AActor* CallingActor) override;
	virtual TSubclassOf<UUserWidget> GetWidgetType() override;

	UFUNCTION()
		void BeginOverlapMixingTable(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlapMixingTable(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	//members
public:



	//methods
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//members
protected:

	//Widget to display when this object is viewed
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUserWidget> WidgetType;

	//Area in which a player entering will trigger tracing for table
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* ItemInteractArea;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ItemStaticMesh;

	//methods
private:


	//members
private:
	



};
