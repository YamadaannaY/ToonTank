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
	
	//创建可赋值的实例，并将其与根组件绑定
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
	//在设置好具体子类的情况下处理声效和音效

	if (DeathParticle){
	//在当前world的特定位置以特定朝向生成粒子特效
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
	//传入一个目标位置，获得二者之间的向量，将这个向量的欧拉角旋转度作为炮台的旋转度
	FVector ToTarget = LookAtTarget-TurretMesh->GetComponentLocation();
	
	//only effect the Yaw because we not expect the turret to turn up , down or roll
	FRotator LookAtRotation= FRotator(0.f,ToTarget.Rotation().Yaw,0.f);
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
