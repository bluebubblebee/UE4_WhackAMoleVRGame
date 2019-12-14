// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "MotionControllerComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APickup::APickup()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); 
	RootComponent = Root; 

	Base = CreateDefaultSubobject<UBoxComponent>(TEXT("Base"));
	Base->SetSimulatePhysics(true);
	Base->SetBoxExtent(FVector(1, 1, 1));
	Base->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Base->SetupAttachment(Root);

	InteractiveCollider = CreateDefaultSubobject < UBoxComponent>(TEXT("InteractiveCollider"));
	InteractiveCollider->SetupAttachment(Base);


	PickupSnapLocator = CreateDefaultSubobject<USceneComponent>(TEXT("PickupSnapLocator"));
	PickupSnapLocator->SetupAttachment(Base);

	bUsing = false;
	bEnablePickup = true;
	PrimaryActorTick.bCanEverTick = true;

	bUsePickupLocator = false;

	bSnapToInitialTransform = false;
	WaitTimeToSnapToInitial = 5.0f;
	CurrentTimeToSnapToInitial = 0.0f;
	bWaitToSnapToInitial = false;
}


void APickup::BeginPlay()
{
	Super::BeginPlay();

	bSimulatePhysics = Base->IsSimulatingPhysics();	

	InitialBaseTransform = Base->GetComponentTransform();
}


void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bWaitToSnapToInitial)
	{
		CurrentTimeToSnapToInitial += DeltaTime;

		if (CurrentTimeToSnapToInitial >= WaitTimeToSnapToInitial)
		{
			CurrentTimeToSnapToInitial = 0.0f;

			bWaitToSnapToInitial = false;

			Base->SetWorldTransform(InitialBaseTransform);

			bEnablePickup = true;
		}
	}
}

void APickup::Pickup_Implementation(UMotionControllerComponent* MotionController)
{
	if (!bEnablePickup) return;

	if (!bUsing)
	{
		bUsing = true;

		CurrentMotionController = MotionController;

		Base->SetSimulatePhysics(false);

		// Use the PickupLocator to set the location before attach
		if (bUsePickupLocator)
		{
			FVector SnapLocation = PickupSnapLocator->GetComponentTransform().GetLocation() - Base->GetComponentTransform().GetLocation();
			float SnapDistance = SnapLocation.Size();			
			
			FVector NewLocation = (MotionController->GetForwardVector() * SnapDistance) + MotionController->GetComponentTransform().GetLocation();
			
			Base->SetWorldLocation(NewLocation);
		}

		Base->AttachToComponent(MotionController, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
	}
}

void APickup::Drop_Implementation(UMotionControllerComponent* MotionController)
{
	if (!bEnablePickup) return;

	if ((MotionController == nullptr) || (CurrentMotionController == MotionController))
	{
		bUsing = false;

		Base->SetSimulatePhysics(bSimulatePhysics);

		CurrentMotionController = nullptr;

		Base->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);


		// Check if we should snap the pickup to its initial transform after drop
		if (bSnapToInitialTransform)
		{
			bWaitToSnapToInitial = true;
			CurrentTimeToSnapToInitial = 0.0f;

			bEnablePickup = false;
		}
	}

}

