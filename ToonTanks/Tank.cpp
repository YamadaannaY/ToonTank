// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "HealthComponent.h"
#include "ToonTankGameMode.h"
#include "Tower.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

ATank::ATank()
{
	SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	Speed=600.f;
	TurnRate=45.f;
}
//bind function to axis mapping
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//make sure inherit all the parent`s function
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//bind move function to the moveforward axis mapping
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"),this,&ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&ATank::Fire);
}


void ATank::Move(float Value)
{
	//every time call the Move,reset the location to current location
	FVector DeltaLocation(0.f);
	
	//x=value*deltatime*speed
	DeltaLocation.X=Value*Speed*UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation,true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation(0.f);
	DeltaRotation.Yaw=Value*TurnRate*UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation,true);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController=Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResult);
		RotateTurret(HitResult.ImpactPoint);
		
	}
}

void ATank::HandleDestruction()
{
	Super::HandeleDestruction();

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	//we know the state of tank and told the state to tower to make sure they wolud not along shoot
	bAlive=false;
	
}


