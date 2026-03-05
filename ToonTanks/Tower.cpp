#include "Tower.h"
#include "Tank.h"
#include "ToonTankGameMode.h"
#include "kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Tank)
	{
		float Distance=FVector::Dist(GetActorLocation(),Tank->GetActorLocation());
		
		if (Distance<=FireRange && ToonTankGameMode->bGameOver == false)
		{
			RotateTurret(Tank->GetActorLocation());
		}
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}


void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition,FireRate,true);
}

void ATower::CheckFireCondition()
{
	if (Tank)
	{
		float Distance=FVector::Dist(GetActorLocation(),Tank->GetActorLocation());
		
		if (Distance<=FireRange && Tank->bAlive)
		{
			Fire();
		}
	}
}
