// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	//处理销毁事件
	void HandeleDestruction();

protected:
	//向目标方向向量进行旋转
	void RotateTurret(FVector LookAtTarget);
	//攻击
	void Fire();

private:
	//碰撞组件
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true));
	class UCapsuleComponent* CapsuleComp;
	
	/**使用组件分离，使得炮台能够给予基体进行转向**/

	//基体组件
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true));
	UStaticMeshComponent* BaseMesh;
	
	//炮塔组件
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true));
	UStaticMeshComponent* TurretMesh;
	
	//子弹产生地点
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true));
	USceneComponent* ProjectilesSpawnPoint;

	//自由选择子弹类下的子类
	UPROPERTY(EditDefaultsOnly,Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	//死亡粒子特效
	UPROPERTY(EditDefaultsOnly,Category="Combat")
	class UParticleSystem* DeathParticle;

	//死亡音效
	UPROPERTY(EditDefaultsOnly,Category="Combat")
	class USoundBase* DeathSound;

	//死亡时相机震动，具体震动效果不同Pawn各自一个具体类
	UPROPERTY(EditAnywhere,Category="Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeclass;

};
