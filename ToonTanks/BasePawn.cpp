#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CapsuleComp=CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent=CapsuleComp;

	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectilesSpawnPoint=CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectilesSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	ToonTankGameMode = Cast<AToonTankGameMode>(UGameplayStatics::GetGameMode(this));
}


void ABasePawn::HandleDestruction()
{
	if (DeathParticle){
	UGameplayStatics::SpawnEmitterAtLocation(this,DeathParticle,GetActorLocation(),GetActorRotation());
	}
	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,DeathSound,GetActorLocation());
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}


void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	const FVector ToTarget = LookAtTarget-TurretMesh->GetComponentLocation();
	
	const FRotator LookAtRotation= FRotator(0.f,ToTarget.Rotation().Yaw,0.f);
	
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
