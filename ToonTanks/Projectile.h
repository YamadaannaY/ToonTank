// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this actor's properties
	AProjectile();

private:
	UPROPERTY(EditDefaultsOnly,Category="Combat");
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere,Category="Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
	float Damage=20.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent*HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly,Category="Combat")
	class UParticleSystem* HitParticles;

	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* TrailParticles;
	
	UPROPERTY(EditDefaultsOnly,Category="Combat")
	USoundBase* LunchSound;

	UPROPERTY(EditDefaultsOnly,Category="Combat")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly,Category="Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeclass;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
