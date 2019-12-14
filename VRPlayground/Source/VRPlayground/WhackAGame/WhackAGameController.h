// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WhackAGameController.generated.h"

UCLASS()
class VRPLAYGROUND_API AWhackAGameController : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WhackAGame")
	USceneComponent *Root;

	// 9 Spawn points for each avocado
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WhackAGame")
	USceneComponent *SpawnPoint0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WhackAGame")
	USceneComponent *SpawnPoint1;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WhackAGame")
	USceneComponent *SpawnPoint2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WhackAGame")
	USceneComponent *SpawnPoint3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WhackAGame")
	USceneComponent *SpawnPoint4;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WhackAGame")
	USceneComponent *SpawnPoint5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "WhackAGame")
	USceneComponent *SpawnPoint6;

	// TArray containing all spawn points
	TArray<USceneComponent*> SpawnPointList;


protected:

	// Object to spawn
	UPROPERTY(EditDefaultsOnly, Category = "WhackAGame")
	TSubclassOf<class AObjectToWhack> ObjectToWhackClass;
	
public:	

	AWhackAGameController();

protected:

	virtual void BeginPlay() override;
	
};
