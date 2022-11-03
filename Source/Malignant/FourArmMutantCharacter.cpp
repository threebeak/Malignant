// Fill out your copyright notice in the Description page of Project Settings.


#include "FourArmMutantCharacter.h"


AFourArmMutantCharacter::AFourArmMutantCharacter()
{
	Label = "FourArmMutant";
	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

void AFourArmMutantCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AFourArmMutantCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->GrabbedComponent->SetWorldLocation(LookResult.TraceEnd);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s"), *PhysicsHandle->GrabbedComponent->GetPhysicsLinearVelocity().ToString()));
	}
}

void AFourArmMutantCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFourArmMutantCharacter::Interact()
{
	if (PhysicsHandle->GrabbedComponent)
	{
		ThrowObject();
		return;
	}

	Super::Interact();

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("FourArmInteracting")));
	UPrimitiveComponent* HitComponent = LookResult.GetComponent();
	if (HitComponent)
	{
		GrabObject(HitComponent);
	}

}

bool AFourArmMutantCharacter::GrabObject(UPrimitiveComponent* HitComponent)
{
	if (HitComponent->IsSimulatingPhysics())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("ComponentValid")));
		HitComponent->SetSimulatePhysics(false);
		PhysicsHandle->GrabComponentAtLocationWithRotation(HitComponent, NAME_None, HitComponent->GetComponentLocation(), FRotator{ 0.0f, 0.0f, 0.0f });
		return true;
	}
	return false;
}

void AFourArmMutantCharacter::ThrowObject()
{
	UPrimitiveComponent* ThrowComponent = PhysicsHandle->GrabbedComponent;
	//ThrowComponent->ComponentVelocity = { 0.0f,0.0f,0.0f };
	PhysicsHandle->ReleaseComponent();
	ThrowComponent->SetSimulatePhysics(true);
	ThrowComponent->AddImpulse(MainCamera->GetForwardVector() * ThrowStrength, NAME_None, true);
	
	
}
