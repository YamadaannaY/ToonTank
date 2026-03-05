#include "HealthComponent.h"

#include "ToonTankGameMode.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent() :ToonTankGameMode(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Health=MaxHealth;

	//响应ApplyDamage应用
	GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::DamageTaken);

	ToonTankGameMode=Cast<AToonTankGameMode>(UGameplayStatics::GetGameMode(this));
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor,float Damage,const UDamageType* DamageType,class AController* Instigator,AActor* DamageCauser)
{
	if (Damage<=0.f) return;

	Health-=Damage;
	if(Health<=0.f)
	{
		ToonTankGameMode->ActorDied(DamagedActor);
	}
}