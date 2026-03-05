#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class AToonTankGameMode;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

	//处理死亡时的VFX
	virtual void HandleDestruction();
	
	UPROPERTY()
	AToonTankGameMode* ToonTankGameMode;

protected:
	//旋转炮塔，Tick中调用
	void RotateTurret(FVector LookAtTarget);
	
	//生成Projectile，配置了初速度和加速度
	void Fire();

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true));
	class UCapsuleComponent* CapsuleComp;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true));
	UStaticMeshComponent* BaseMesh;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true));
	UStaticMeshComponent* TurretMesh;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true));
	USceneComponent* ProjectilesSpawnPoint;

	UPROPERTY(EditDefaultsOnly,Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly,Category="Combat")
	UParticleSystem* DeathParticle;

	UPROPERTY(EditDefaultsOnly,Category="Combat")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere,Category="Combat")
	TSubclassOf<UCameraShakeBase> DeathCameraShakeClass;

};
