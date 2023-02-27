// Fill out your copyright notice in the Description page of Project Settings.


#include "MixingTable.h"
#include "MutantCharacter.h"
#include "MalignantGameState.h"
#include "Blueprint/UserWidget.h"


// Sets default values
AMixingTable::AMixingTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Mutants = CreateDefaultSubobject<UMutantMapComponent>(TEXT("Map"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	TableCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TableCamera"));

	BottleMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle 1"));
	BottleMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle 2"));
	BottleMesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle 3"));
	BottleMesh4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle 4"));

	ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh1(TEXT("StaticMesh'/Game/Meshes/Flasks/Flasks__1__Flask2.Flasks__1__Flask2'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh2(TEXT("StaticMesh'/Game/Meshes/Flasks/Flasks__1__Flask1.Flasks__1__Flask1'"));

	BottleMesh1->SetStaticMesh(Mesh1.Object);
	BottleMesh3->SetStaticMesh(Mesh1.Object);
	BottleMesh2->SetStaticMesh(Mesh2.Object);
	BottleMesh4->SetStaticMesh(Mesh2.Object);

	RootComponent = BoxCollision;
	BoxCollision->SetBoxExtent({ 64,32,32 });
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);

	TableCamera->SetupAttachment(RootComponent);
	BottleMesh1->SetupAttachment(RootComponent);
	BottleMesh2->SetupAttachment(RootComponent);
	BottleMesh3->SetupAttachment(RootComponent);
	BottleMesh4->SetupAttachment(RootComponent);

	TableCamera->SetRelativeRotation({ -15, -90, 0 });
	TableCamera->SetRelativeLocation({ 0, 90, 73 });
	BottleMesh1->SetRelativeLocation({ -50, 0, 20 });
	BottleMesh2->SetRelativeLocation({ -17, 0, 20 });
	BottleMesh3->SetRelativeLocation({ 17, 0, 20 });
	BottleMesh4->SetRelativeLocation({ 50, 0, 20 });

}

// Called when the game starts or when spawned
void AMixingTable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMixingTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Check valid player and action bindings. 
bool AMixingTable::Interact(AActor* CallingActor)
{
	Player = Cast<APlayerCharacter>(CallingActor);
	if (Player == nullptr)
		return false;

	//Lock player and allow input
	if (SetActionBindings(Player))
	{
		Player->Lock();
		Controller->SetViewTargetWithBlend(this, 2.0f);
	}
	return true;
}

//Setup Input from PlayerController
bool AMixingTable::SetActionBindings(APlayerCharacter* Character)
{
	Controller = Cast<APlayerController>(Character->GetController());
	if (Controller == nullptr)
		return false;

	EnableInput(Controller);

	if (!ActionsBound)
	{
		InputComponent->BindAction("Interact", IE_Pressed, this, &AMixingTable::Exit);
		InputComponent->BindAction<FBottleSelect>("Bottle_1", IE_Pressed, this, &AMixingTable::BottleSelect, 1);
		InputComponent->BindAction<FBottleSelect>("Bottle_2", IE_Pressed, this, &AMixingTable::BottleSelect, 2);
		InputComponent->BindAction<FBottleSelect>("Bottle_3", IE_Pressed, this, &AMixingTable::BottleSelect, 3);
		InputComponent->BindAction<FBottleSelect>("Bottle_4", IE_Pressed, this, &AMixingTable::BottleSelect, 4);
		ActionsBound = true;
	}


	return true;
}

//Determine MutantCharacter class to spawn
bool AMixingTable::ChooseMutant(AActor* CallingActor)
{
	int32 BottleValue = Bottle1.Value + Bottle2.Value;
	if (BottleValue < 5)
	{
		BottleValue -= 2;
	}
	else
	{
		if (BottleValue > 5)
		{
			BottleValue -= 1;
			
		}
		else
		{
			int32 i = abs(Bottle2.Value - Bottle1.Value);
				switch (i)
				{
				case 1:
					BottleValue = 4;
					break;
				case 3:
					BottleValue = 3;
					break;
				}
		}
	}

	EMutantState State = StaticCast<EMutantState>(BottleValue);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CHOOSE MUTANT %i"), (BottleValue - 2)));
if (Mutants)
	{

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("MAP")));

		//Find mutant class in map
		TSubclassOf<AMutantCharacter> NewMutant = *Mutants->GetMap().Find(State);

		if (NewMutant && Player)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("CALLED")));

			//Try to spawn new mutant character
			AMalignantGameState* CurrentGameState = Cast<AMalignantGameState>(GetWorld()->GetGameState());
			if (CurrentGameState)
			{
				CurrentGameState->SpawnPlayer(State);
				return true;
			}
		}
		return false;
	}
	return false;
}


//Store bottle choices and bottle value 
void AMixingTable::BottleSelect(const int32 BottleValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("%i"), BottleValue));

	//If we've already selected 2 bottles or selected a repeat bottle,this function will not execute again
	if (Bottle2.Key || Bottle1.Value == BottleValue)
		return;

	/***Temporary to show which bottles have been selected****/
	switch (BottleValue)
	{
	case 1:
		BottleMesh1->SetVisibility(false);
		break;
	case 2:
		BottleMesh2->SetVisibility(false);
		break;
	case 3:
		BottleMesh3->SetVisibility(false);
		break;
	case 4:
		BottleMesh4->SetVisibility(false);
		break;
	}
	/***************************************************/

	//Track which bottles have been selected
	if (!Bottle1.Key)
	{
		Bottle1.Key = true;
		Bottle1.Value = BottleValue;
		return;
	}
	Bottle2.Key = true;
	Bottle2.Value = BottleValue;

	//Try to determine mutant
	ChooseMutant(Player);
//	Exit();

	
}

TSubclassOf<UUserWidget> AMixingTable::GetWidgetType()
{
	return WidgetType;
}


//Temporarily cease input and switch cameras
void AMixingTable::Exit()
{
	DisableInput(Controller);
	Controller->SetViewTargetWithBlend(Player, 1.0f);

	//Wait for camera change then Clear()
	GetWorldTimerManager().SetTimer(CameraHandle, this, &AMixingTable::Clear, 1.0f, false);
	
}

//Clear pointers and reassign controller. If bottle 2 was not selected, reset bottle 1 choice.
void AMixingTable::Clear()
{
	if (!Bottle2.Key)
	{
		Bottle1.Key = false;
		Bottle1.Value = 0;
	}
	Controller->Possess(Player);
	Player->Release(Controller);

	Player = nullptr;
	Controller = nullptr;
}
