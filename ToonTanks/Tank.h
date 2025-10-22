// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"


/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
	
	void HandleDestruction();

	

	APlayerController* GetTankPlayerController() const {return TankPlayerController;}

	bool bAlive=true;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	float Speed;
	
	UPROPERTY(EditAnywhere,Category="Components")
	float TurnRate;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true));
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true));
	class UCameraComponent* Camera;

	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController;
	

	UPROPERTY(VisibleAnywhere)
	float  MaxHealth=100.f;
	
};
