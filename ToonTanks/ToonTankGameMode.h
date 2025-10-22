// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDied(AActor* DeadActor);
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank;
	class AToonTankPlayerController* ToonTankPlayerController;

	//Delay the game player input with disabled
	float StartDelay=3.f;
	
	//handle the events when the game start
	void HandleGameStart();
	
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true));
	int32 TargetTowers=0;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true));
	int32 MaxScore;

public:
	int32 GetTargetTowerCount();
};

