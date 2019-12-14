// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectToWhack.generated.h"

// Enumerate for move status
UENUM(BlueprintType)		
enum class EStatus : uint8
{
	VE_None 	UMETA(DisplayName = "None"),
	VE_Idle 	UMETA(DisplayName = "Idle"),
	VE_GoUp	    UMETA(DisplayName = "GoUp"),
	VE_GoDown	UMETA(DisplayName = "GoDown"),
	VE_WaitToStart	UMETA(DisplayName = "WaitToStart"),
	VE_Reset	UMETA(DisplayName = "Reset")
};



UCLASS()
class VRPLAYGROUND_API AObjectToWhack : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WhackAGame")
	USceneComponent *Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WhackAGame")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WhackAGame")
	class UBoxComponent* HitTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WhackAGame")
	class UAudioComponent* HitAudio;
	
public:	

	AObjectToWhack();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "WhackAGame")
	void OnHit();

public:	

	virtual void Tick(float DeltaTime) override;

public:

	void Initialize(float StartPosition, float EndPosition);

protected:	

	EStatus CurrentState = EStatus::VE_None;

	EStatus NextState;

	bool bEnableCollision;

	UPROPERTY(EditAnywhere, Category = "WhackAGame")
	float TimeInIdle;

protected:	

	float CurrentDeltaTime;

	float DelayToStartMove;

protected:

	float StartZPosition;

	float EndZPosition;

	float CurrentVelocity;


	UPROPERTY(EditAnywhere, Category = "WhackAGame")
	float AccerationRate = 1.0f;

protected:


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "WhackAGame: Reset")
	float WaitToReset = 3.0f;

	FTimerHandle WaitToReseTimerHandle;

	UFUNCTION()
	void OnWaitToReset();
};
