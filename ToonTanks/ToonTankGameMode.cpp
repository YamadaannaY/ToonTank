#include "ToonTankGameMode.h"
#include "ToonTankPlayerController.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "GameFramework/Actor.h" 

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	HandleGameStart();
}


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
		bGameOver=false;
	}
	else if (ATower* DestroyedTower=Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;
		
		if (TargetTowers==0)
		{
			GameOver(true);
			bGameOver=true;
		}
	}
}

void AToonTankGameMode::HandleGameStart()
{
	TargetTowers=GetTargetTowerCount();
	
	Tank=Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	
	ToonTankPlayerController=Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this,0));

	StartGame();

	if (ToonTankPlayerController)
	{
		ToonTankPlayerController->SetPlayerEnabledState(false);
		
		FTimerHandle PlayerEnableTimerHandle;

		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
	[this]
	{
		ToonTankPlayerController->SetPlayerEnabledState(true);
	},
	StartDelay,
	false);

	}
}

int32 AToonTankGameMode::GetTargetTowerCount()
	{
		TArray<AActor*> Towers;
		UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),Towers);
		MaxScore=Towers.Num();
	
		return Towers.Num();
	}