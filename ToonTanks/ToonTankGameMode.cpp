// Fill out your copyright notice in the Description page of Project Settings.
#include "ToonTankGameMode.h"
#include "ToonTankPlayerController.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "GameFramework/Actor.h"  // 必须

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	HandleGameStart();
	
}


//use  AActor to make sure either tower and tank can assign to formal parameter
void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor== Tank)
	{
		Tank->HandleDestruction();
		if (ToonTankPlayerController)
		{
			ToonTankPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower=Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;
		if (TargetTowers==0)
		{
			GameOver(true);
		}
	}
}

void AToonTankGameMode::HandleGameStart()
{
	TargetTowers=GetTargetTowerCount();
	//get Tank that in the world and we control
	Tank=Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	
	//get playercontroller
	ToonTankPlayerController=Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this,0));

	StartGame();

	if (ToonTankPlayerController)
	{
		//enable player`s input
		ToonTankPlayerController->SetPlayerEnabledState(false);
		
		//it is a handle to control the Timer,can be used to [GetWorldTimerManager]ClearTimer,IsTimerActive and GetTimerRemaining
		FTimerHandle PlayerEnableTimerHandle;
		
		//ture is a parameter which when the delegate is triggered,it will convey to function be bind
		//(in this code is : SetPlayerEnabledState)
		//FTimerDelegate 是 “函数 + 绑定参数” 的组合，适合在定时器触发时调用带参数的成员函数。
		//由于这里的SetPlayerEnabledState需要传参，所以要调用委托传入绑定参数，如果是一个无参函数，可以忽略这个绑定参数
		//甚至不需要委托，直接将这个函数的地址传到SetTimer之中
		FTimerDelegate PlayerEnableTimerDelegate=FTimerDelegate::CreateUObject(
			ToonTankPlayerController,
			&AToonTankPlayerController::SetPlayerEnabledState,
			true);
		//SetTimer:Creating a Timer
		//trigger the delegate after startdelay sconds
		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false);
	}
}

int32 AToonTankGameMode::GetTargetTowerCount()
	{
		//none specific type in template but a parent class
		TArray<AActor*> Towers;
		UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),Towers);
		MaxScore=Towers.Num();
		return Towers.Num();
	}

	


