// Fill out your copyright notice in the Description page of Project Settings.


#include "WhackAGameController.h"
#include "ObjectToWhack.h"
#include "Components/SceneComponent.h"


AWhackAGameController::AWhackAGameController()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// Create all spawn points for the objects to whack
	SpawnPoint0 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint0"));
	SpawnPoint0->SetupAttachment(Root);

	SpawnPoint1 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint1"));
	SpawnPoint1->SetupAttachment(Root);

	SpawnPoint2 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint2"));
	SpawnPoint2->SetupAttachment(Root);

	SpawnPoint3 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint3"));
	SpawnPoint3->SetupAttachment(Root);

	SpawnPoint4 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint4"));
	SpawnPoint4->SetupAttachment(Root);

	SpawnPoint5 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint5"));
	SpawnPoint5->SetupAttachment(Root);

	SpawnPoint6 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint6"));
	SpawnPoint6->SetupAttachment(Root);

	PrimaryActorTick.bCanEverTick = true;
}


void AWhackAGameController::BeginPlay()
{
	Super::BeginPlay();

	// Add all spawn points to the list
	SpawnPointList.Add(SpawnPoint0);
	SpawnPointList.Add(SpawnPoint1);
	SpawnPointList.Add(SpawnPoint2);
	SpawnPointList.Add(SpawnPoint3);
	SpawnPointList.Add(SpawnPoint4);
	SpawnPointList.Add(SpawnPoint5);
	SpawnPointList.Add(SpawnPoint6);


	// Instance all objects and add it to the list
	if (ObjectToWhackClass != nullptr)
	{
		for (int i = 0; i < SpawnPointList.Num(); i++)
		{
			AObjectToWhack* NewObject = GetWorld()->SpawnActor<AObjectToWhack>(ObjectToWhackClass, SpawnPointList[i]->GetComponentTransform());
			if (NewObject != nullptr)
			{
				
				NewObject->AttachToComponent(SpawnPointList[i], FAttachmentTransformRules::SnapToTargetNotIncludingScale, NAME_None);

				FVector CurrentLocation = NewObject->GetActorLocation();

				float EndPosition = CurrentLocation.Z;

				float StartPosition = CurrentLocation.Z - 30.0f;

				CurrentLocation.Z = StartPosition;

				NewObject->SetActorLocation(CurrentLocation);

				NewObject->Initialize(StartPosition, EndPosition);
			}
		}

	}

}