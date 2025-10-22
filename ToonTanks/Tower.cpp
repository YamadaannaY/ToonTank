// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "kismet/GameplayStatics.h"



void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Tank)
	{
		// Find the  distance to the  tank
		float Distance=FVector::Dist(GetActorLocation(),Tank->GetActorLocation());
		//Check if the Tank is in range
		if (Distance<=FireRange)
		{	//If in range,rotate turret toward	Tank
			RotateTurret(Tank->GetActorLocation());
		}
	}
}

void ATower::HandleDestruction()
{
	Super::HandeleDestruction();

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
			Fire();		}
	}
}
