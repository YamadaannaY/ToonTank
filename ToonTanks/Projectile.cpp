// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick =false;

	ProjectileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent=ProjectileMesh;

	ProjectileMovement=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->InitialSpeed=1300.f;
	ProjectileMovement->MaxSpeed=1300.f;
	//Creat a trail particles
	TrailParticles=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SomkeTrail"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);
	if (LunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,LunchSound,GetActorLocation());
	}
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent*HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit)
{
	AActor* MyOwner=GetOwner();
	if (MyOwner==nullptr)
	{
		Destroy();
		return;
	};

	AController* MyOwnerInstigator=MyOwner->GetInstigatorController();

	UClass* DamageTypeClass=UDamageType::StaticClass();

	if (OtherActor && OtherActor!=this && OtherActor!=MyOwner)
	{
		//Oncomponenthithit happens and broadcast will call onhit,which apply damage and trigger delegate OnTakeAnyDamage,the
		//delegate call the DamageTaken 
		UGameplayStatics::ApplyDamage(OtherActor,Damage,MyOwnerInstigator,this,DamageTypeClass);
		//Spawn a particle if hit partciles being created;
		if (HitParticles)
		{
		UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles,GetActorLocation(),GetActorRotation());
		}
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation());
		}
		if (HitCameraShakeclass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeclass);
		}
		
	}
	Destroy();
}


