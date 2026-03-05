// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * @class ATank
 * @brief Represents the player-controlled tank in the game, inheriting functionalities from ABasePawn.
 *
 * This class is responsible for handling the movement, turning, and destruction of the tank. It also manages the input bindings for player controls and sets up the camera and spring arm components for a third-person view.
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
	
	virtual void HandleDestruction() override;
	
	FORCEINLINE APlayerController* GetTankPlayerController() const {return TankPlayerController;}

	bool bAlive=true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	float Speed;
	
	UPROPERTY(EditAnywhere,Category="Components")
	float TurnRate;
	
protected:
	
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true));
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components",meta=(AllowPrivateAccess=true));
	class UCameraComponent* Camera;

	UPROPERTY()
	APlayerController* TankPlayerController;
	
	UPROPERTY(VisibleAnywhere)
	float  MaxHealth=100.f;

	//移动
	void Move(float Value);

	//旋转
	void Turn(float Value);
};
