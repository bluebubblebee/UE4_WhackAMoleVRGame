// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectToWhack.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "HammerPickup.h"

// Sets default values
AObjectToWhack::AObjectToWhack()
{

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	HitTrigger = CreateDefaultSubobject <UBoxComponent>(TEXT("HitTrigger"));
	HitTrigger->SetupAttachment(Root);
	HitTrigger->OnComponentBeginOverlap.AddDynamic(this, &AObjectToWhack::BeginOverlap);

	HitAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("HitAudio"));
	HitAudio->SetupAttachment(Root);

	PrimaryActorTick.bCanEverTick = true;
}


void AObjectToWhack::BeginPlay()
{
	Super::BeginPlay();

	CurrentState = EStatus::VE_None;

	NextState = EStatus::VE_None;	

	bEnableCollision = false;

	Mesh->SetVisibility(false);
}


void AObjectToWhack::Initialize(float StartPosition, float EndPosition)
{
	// Initialize Start, End Position
	StartZPosition = StartPosition;

	EndZPosition = EndPosition;	

	CurrentDeltaTime = 0.0f;

	CurrentVelocity = 0.0f;

	// Set first state as a start to move
	CurrentState = EStatus::VE_WaitToStart;

	NextState = EStatus::VE_GoUp;

	DelayToStartMove = FMath::FRandRange(0.5f, 4.0f);
}


void AObjectToWhack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Waiting to start
	if (CurrentState == EStatus::VE_WaitToStart)
	{
		CurrentDeltaTime += DeltaTime;

		if (CurrentDeltaTime >= DelayToStartMove)
		{
			CurrentDeltaTime = 0.0f;

			CurrentVelocity = 0.0f;

			CurrentState = NextState;

			bEnableCollision = false;

			Mesh->SetVisibility(true);
		}
	}

	// Up
	if (CurrentState == EStatus::VE_GoUp)
	{
		// Apply velocity with aceleration
		CurrentVelocity += AccerationRate * DeltaTime;

		FVector CurrentPosition = GetActorLocation();
		CurrentPosition.Z += CurrentVelocity;

		SetActorLocation(CurrentPosition);		

		if (CurrentPosition.Z >= EndZPosition)
		{
			bEnableCollision = true;

			CurrentPosition.Z = EndZPosition;

			CurrentVelocity = 0.0f;

			CurrentDeltaTime = 0.0f;

			CurrentState = EStatus::VE_Idle;

			NextState = EStatus::VE_GoDown;
			
		}

		
	}


	// Idle
	if (CurrentState == EStatus::VE_Idle)
	{
		CurrentDeltaTime += DeltaTime;
		if (CurrentDeltaTime >= TimeInIdle)
		{
			CurrentDeltaTime = 0.0f;
				
			CurrentState = NextState;

			bEnableCollision = false;
		}
	}	

	

	// Down
	if (CurrentState == EStatus::VE_GoDown)
	{
		CurrentVelocity += AccerationRate * DeltaTime;

		FVector CurrentPosition = GetActorLocation();

		CurrentPosition.Z -= CurrentVelocity;

		SetActorLocation(CurrentPosition);

		if (CurrentPosition.Z <= StartZPosition)
		{
			CurrentPosition.Z = StartZPosition;

			// Reset move
			CurrentState = EStatus::VE_WaitToStart;

			NextState = EStatus::VE_GoUp;

			CurrentDeltaTime = 0.0f;

			CurrentVelocity = 0.0f;

			DelayToStartMove = FMath::FRandRange(0.5f, 4.0f);

			Mesh->SetVisibility(false);
		}
	}

}



void AObjectToWhack::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (!bEnableCollision) return;

	if (OtherActor != nullptr)
	{
		AHammerPickup* Hammer = Cast<AHammerPickup>(OtherActor);

		if (Hammer != nullptr)
		{
			CurrentState = EStatus::VE_Reset;

			bEnableCollision = false;

			Mesh->SetVisibility(false);

			HitAudio->Play();

			// Call blueprint event
			OnHit();

			GetWorld()->GetTimerManager().SetTimer(WaitToReseTimerHandle, this, &AObjectToWhack::OnWaitToReset, WaitToReset, false);
		}
	}
}

void AObjectToWhack::OnWaitToReset()
{
	GetWorld()->GetTimerManager().ClearTimer(WaitToReseTimerHandle);

	FVector CurrentPosition = GetActorLocation();

	CurrentPosition.Z = StartZPosition;

	SetActorLocation(CurrentPosition);

	CurrentDeltaTime = 0.0f;

	CurrentVelocity = 0.0f;

	// Set first state as a start to move
	CurrentState = EStatus::VE_WaitToStart;

	NextState = EStatus::VE_GoUp;

	DelayToStartMove = FMath::FRandRange(0.5f, 4.0f);
}

