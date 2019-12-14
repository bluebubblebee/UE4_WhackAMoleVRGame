// Fill out your copyright notice in the Description page of Project Settings.


#include "HammerPickup.h"
#include "Components/BoxComponent.h"

AHammerPickup::AHammerPickup()
{
	HitCollider = CreateDefaultSubobject <UBoxComponent>(TEXT("HitCollider"));
	HitCollider->SetupAttachment(Base);
}
