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
	//Tank/Tower血量为0时触发，调用Des逻辑，触发State判断
	void ActorDied(AActor* DeadActor);
protected:
	virtual void BeginPlay() override;

	//创建Widget
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	//删除OverWidget并修改Text
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	UPROPERTY()
	class ATank* Tank;

	UPROPERTY()
	class AToonTankPlayerController* ToonTankPlayerController;

	float StartDelay=3.f;

	//配置基础变量，设置定时器来允许输入
	void HandleGameStart();
	
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true));
	int32 TargetTowers=0;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess=true));
	int32 MaxScore;

	bool bGameOver = false ; 

	//获取所有ActorClass
	int32 GetTargetTowerCount();
};

