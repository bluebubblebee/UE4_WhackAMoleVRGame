// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupInterface.h"

#include "Pickup.generated.h"

UCLASS()
class VRPLAYGROUND_API APickup : public AActor, public IPickupInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	USceneComponent *Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	class UBoxComponent* Base;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	class UBoxComponent* InteractiveCollider;

	// Snap helper locator to help with the orientation and position for the hand
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	USceneComponent* PickupSnapLocator;

	
public:	
	APickup();
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UBoxComponent* GetBase() { return Base; };

protected:
	virtual void BeginPlay() override;	

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickup Interface")
	void Pickup(class UMotionControllerComponent *MotionController);

	virtual void Pickup_Implementation(class UMotionControllerComponent *MotionController) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickup Interface")
	void Drop(class UMotionControllerComponent *MotionController);

	virtual void Drop_Implementation(class UMotionControllerComponent *MotionController) override;	


protected:

	// Wheter the pickup is enabled or not
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	bool bEnablePickup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
	bool bUsing;	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	class UMotionControllerComponent *CurrentMotionController;

	bool bSimulatePhysics;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	bool bUsePickupLocator;

protected:	

	// Whether the pickup snaps to initial transform after drop it or not
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	bool bSnapToInitialTransform;	

	bool bWaitToSnapToInitial;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float WaitTimeToSnapToInitial;

	float CurrentTimeToSnapToInitial;

	FTransform InitialBaseTransform;
};
