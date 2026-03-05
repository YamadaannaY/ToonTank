#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UHealthComponent();

protected:
	
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float MaxHealth = 100.f;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	float Health=0.f;

	UPROPERTY()
	class AToonTankGameMode* ToonTankGameMode;

	//Hit回调触发的伤害应用，血量小于0触发GameMode中的ActorDied
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor,float Damage,const UDamageType* DamageType,AController* Instigator,AActor* DamageCauser);

	//Tick
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
