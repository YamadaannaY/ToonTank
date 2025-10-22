// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//creat  instance of capsule component
	CapsuleComp=CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent=CapsuleComp;

	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectilesSpawnPoint=CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectilesSpawnPoint->SetupAttachment(TurretMesh);
}


void ABasePawn::HandeleDestruction()
{
	//handle visual / sound effects
	if (DeathParticle){
	UGameplayStatics::SpawnEmitterAtLocation(this,DeathParticle,GetActorLocation(),GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,DeathSound,GetActorLocation());
	}
	if (DeathCameraShakeclass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeclass);
	}
}


void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	//get a vector between target to turret location ,it is a world space direction
	FVector ToTarget = LookAtTarget-TurretMesh->GetComponentLocation();
	
	//only effect the Yaw because we not expect the turret to turn up , down or roll
	FRotator LookAtRotation= FRotator(0.f,ToTarget.Rotation().Yaw,0.f);
	
	//delivery the frotator var to mesh.
	TurretMesh->SetWorldRotation(LookAtRotation);
}	

void ABasePawn::Fire()
{
	AProjectile* Projectile=GetWorld()->SpawnActor<AProjectile>
	(ProjectileClass,
		ProjectilesSpawnPoint->GetComponentLocation(),
		ProjectilesSpawnPoint->GetComponentRotation());

	Projectile->SetOwner(this);
}
