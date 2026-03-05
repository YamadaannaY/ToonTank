
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
private:
	UPROPERTY(EditDefaultsOnly,Category="Combat");
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere,Category="Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
	float Damage=20.f;

	UPROPERTY(EditDefaultsOnly,Category="Combat")
	UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* TrailParticles;
	
	UPROPERTY(EditDefaultsOnly,Category="Combat")
	USoundBase* LunchSound;

	UPROPERTY(EditDefaultsOnly,Category="Combat")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly,Category="Combat")
	TSubclassOf<UCameraShakeBase> HitCameraShakeclass;

	//OnComponentHit回调，通过判断后触发ApplyDamage到HitActor
	UFUNCTION()
	void OnHit(UPrimitiveComponent*HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit);
	
protected:
	virtual void BeginPlay() override;
};
