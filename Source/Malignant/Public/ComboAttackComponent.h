// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComboAttackComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MALIGNANT_API UComboAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComboAttackComponent();

	UFUNCTION(BlueprintCallable)
		virtual void LightAttack();
	UFUNCTION(BlueprintCallable)
		virtual void HeavyAttack();

	void StartAttack(FName Section, float Speed);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PlayAnimationMontage(FName Section, float Speed);


	UFUNCTION(BlueprintCallable)
		void ToggleComboFrame(bool IsWithinComboFrames);

	UFUNCTION(BlueprintCallable)
		void FinishAttack();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bComboIsValid();
	uint32 GetSectionAsInt(FName Section);

	UPROPERTY(BlueprintReadOnly)
		USkeletalMeshComponent* CharacterMeshComponent;

	UPROPERTY(BlueprintReadOnly)
		UAnimMontage* AttackMontage;


	FName AttackSection;

	UPROPERTY(EditAnywhere)
		float StartingAttackSpeed = 1;

	float AttackSpeed = 1;
	bool bIsAttacking = false;
	bool bWithinComboFrames = false;
	bool bPlayNextAttack = false;
	int32 ComboCounter = 1;

	void Reset();
	

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetSkeletalMesh(USkeletalMeshComponent* Component);
	void SetAttackMontage(UAnimMontage* Montage);

		
};
