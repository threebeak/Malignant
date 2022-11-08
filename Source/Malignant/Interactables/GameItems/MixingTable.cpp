// Fill out your copyright notice in the Description page of Project Settings.


#include "MixingTable.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "../../Components/MutantMapComponent.h"
#include "../../Mutants/PlayerCharacter.h"
#include "../../Mutants/MutantCharacter.h"



// Sets default values
AMixingTable::AMixingTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Mutants = CreateDefaultSubobject<UMutantMapComponent>(TEXT("Map"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	MixingTableInteractArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Mixing Table Interact Area"));
	TableCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TableCamera"));

	BottleMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle 1"));
	BottleMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle 2"));
	BottleMesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottle 3"));

	RootComponent = BoxCollision;
	BoxCollision->SetBoxExtent({ 64,32,32 });
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);

	TableCamera->SetupAttachment(RootComponent);
	BottleMesh1->SetupAttachment(RootComponent);
	BottleMesh2->SetupAttachment(RootComponent);
	BottleMesh3->SetupAttachment(RootComponent);
	MixingTableInteractArea->SetupAttachment(RootComponent);



	TableCamera->SetRelativeRotation({ -15, -90, 0 });
	TableCamera->SetRelativeLocation({ 0, 90, 73 });
	BottleMesh1->SetRelativeLocation({ -50, 0, 36 });
	BottleMesh2->SetRelativeLocation({ 0, 0, 36 });
	BottleMesh3->SetRelativeLocation({ 50, 0, 36 });

}

// Called when the game starts or when spawned
void AMixingTable::BeginPlay()
{
	Super::BeginPlay();

	MixingTableInteractArea->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MixingTableInteractArea->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	MixingTableInteractArea->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	MixingTableInteractArea->OnComponentBeginOverlap.AddDynamic(this, &AMixingTable::BeginOverlapMixingTable);
	MixingTableInteractArea->OnComponentEndOverlap.AddDynamic(this, &AMixingTable::EndOverlapMixingTable);

	
}

void AMixingTable::BeginOverlapMixingTable(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
		PlayerCharacter->SetOverlappingTable(true);
}

void AMixingTable::EndOverlapMixingTable(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
		PlayerCharacter->SetOverlappingTable(false);
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
		ActionsBound = true;
	}


	return true;
}

//Determine MutantCharacter class to spawn
bool AMixingTable::ChooseMutant(AActor* CallingActor)
{
	int32 BottleValue = Bottle1.Value + Bottle2.Value;

	//This will TEMPORARILY use the sum of bottle values because there are currently only 3 bottles
	//Each combination of values - 2 will result in 1 2 or 3 and can be used to determine mutant state.
	//This will have to change when more bottles and mutants are added

	EMutantState State = StaticCast<EMutantState>(BottleValue - 2);
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
			AMutantCharacter* NewCharacter = GetWorld()->SpawnActor<AMutantCharacter>(NewMutant, Player->GetActorLocation(), Player->GetActorRotation(), SpawnParams);
			if (NewCharacter)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s"), *NewCharacter->GetName().ToString()));
				Player = NewCharacter;
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

	//If we've already selected 2 bottles, the choice has been made and this function will not execute again
	if (Bottle2.Key)
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
	Exit();

	
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
	GetWorldTimerManager().SetTimer(CameraTimerHandle, this, &AMixingTable::Clear, 1.0f, false);
	
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
