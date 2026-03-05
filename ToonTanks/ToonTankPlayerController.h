// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	//GameStart和End时候调用，禁止/允许玩家输入
	void SetPlayerEnabledState(bool bPlayerEnabled);
};
