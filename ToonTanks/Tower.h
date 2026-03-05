#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	class ATank* Tank;
	
	UPROPERTY(EditDefaultsOnly,Category="Components")
	float FireRange=300.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate=2.f;

	//循环定时器，判断Dist和玩家的bAlive的bool状态，决定是否开火
	void CheckFireCondition();
};
