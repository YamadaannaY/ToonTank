#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick =false;

	ProjectileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent=ProjectileMesh;

	ProjectileMovement=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovement->InitialSpeed=1300.f;
	ProjectileMovement->MaxSpeed=1300.f;
	
	TrailParticles=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SmokeTrail"));
	TrailParticles->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);
	if (LunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,LunchSound,GetActorLocation());
	}
}

void AProjectile::OnHit(UPrimitiveComponent*HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit)
{
	const AActor* MyOwner=GetOwner();
	if (MyOwner==nullptr)
	{
		Destroy();
		return;
	}

	AController* MyOwnerInstigator=MyOwner->GetInstigatorController();

	UClass* DamageTypeClass=UDamageType::StaticClass();

	if (OtherActor && OtherActor!=this && OtherActor!=MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor,Damage,MyOwnerInstigator,this,DamageTypeClass);

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