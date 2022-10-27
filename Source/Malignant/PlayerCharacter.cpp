// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));


	StaticMesh->SetupAttachment(RootComponent);
	MainCamera->SetupAttachment(RootComponent);

	GetCharacterMovement()->SetUpdatedComponent(RootComponent);
	bUseControllerRotationYaw = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Set distances for look trace to interact with objects


}

void APlayerCharacter::Transform()
{
	if (PlayerMutant)
	{
		GetCapsuleComponent()->SetCapsuleHalfHeight(PlayerMutant->GetBaseStats().Height / 2);
		GetCapsuleComponent()->SetCapsuleRadius(PlayerMutant->GetBaseStats().Radius);
		StaticMesh->SetStaticMesh(PlayerMutant->GetMutantMesh());
		GetCharacterMovement()->MaxWalkSpeed = PlayerMutant->GetBaseStats().MovementSpeed;
	}
}



// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Look trace
	FVector Start = MainCamera->GetComponentLocation();
	FVector End = (MainCamera->GetForwardVector() * LookDistance) + Start;
	GetWorld()->LineTraceSingleByChannel(LookResult, Start, End, ECC_Visibility);
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.2f, 0, 5.0f);
	if (LookResult.bBlockingHit)
	{
		HandleTrace();
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	InputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	InputComponent->BindAxis("LookRight", this, &APlayerCharacter::LookRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);

}


void APlayerCharacter::MoveForward(float AxisValue)
{
	if (GetCharacterMovement())
		GetCharacterMovement()->AddInputVector(GetActorForwardVector() * AxisValue);

}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if (GetCharacterMovement())
		GetCharacterMovement()->AddInputVector(GetActorRightVector() * AxisValue);
}

void APlayerCharacter::LookUp(float AxisValue)
{
	FRotator CurrentRotation = MainCamera->GetRelativeRotation();
	CurrentRotation.Pitch = FMath::ClampAngle((CurrentRotation.Pitch + AxisValue), -89.0f, 89.0f);
	MainCamera->SetRelativeRotation(CurrentRotation);
}

void APlayerCharacter::LookRight(float AxisValue)
{
	FRotator CurrentRotation = GetControlRotation();
	CurrentRotation.Yaw += AxisValue;
	GetController()->SetControlRotation(CurrentRotation);
}

//Proxy for ACharacter::Jump
void APlayerCharacter::Jump()
{
	if (GetCharacterMovement())
	{
		ACharacter::Jump();
	}
}

void APlayerCharacter::SetMutant(AMutantBase* NewMutant)
{
	if(NewMutant)
		PlayerMutant = NewMutant;

	Transform();
}

void APlayerCharacter::HandleTrace()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%s"), *LookResult.GetActor()->GetName()));
}
