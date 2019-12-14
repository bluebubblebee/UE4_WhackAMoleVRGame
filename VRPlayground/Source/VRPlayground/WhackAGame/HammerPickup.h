// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "HammerPickup.generated.h"

/**
 * 
 */
UCLASS()
class VRPLAYGROUND_API AHammerPickup : public APickup
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	class UBoxComponent* HitCollider;

public:

	AHammerPickup();
	
};
