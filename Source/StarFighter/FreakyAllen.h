// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Subscriber.h"
#include "Morph.h"
#include "NaveAereaJugador.h"

#include "FreakyAllen.generated.h"

class AClockTower;

UCLASS()
class STARFIGHTER_API AFreakyAllen : public AActor, public ISubscriber, public IMorph
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFreakyAllen();

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FreakyMeshComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	uint32 bCanFire : 1;
	FTimerHandle TimerHandle_ShotTimerExpired; //tiempo que toma de la PC
	FTimerHandle MemberTimerHandle;//caracteristica que usaremos en el BeginPlay
	FTimerHandle MemberTimerHandle1;
public:

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		FVector GunOffset;//es como la distancia que aparecera la proyectil.
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float FireRate; //propiedad que hara cuanto tardara en desaparecer el proyectil.
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float MoveSpeedNewNaveNodriza; //sera la velocidad usada por la NaveAccuatica

	float MovingNX; //Movimiento que le daremos un valor aleatorio para el eje X
	float MovingNY; //Movimiento que le daremos un valor aleatorio para el eje Y
	void FireNewNaveNodriza(); //funcion que llamara a FireShotAcuatica
	void FireShotNewNaveNodriza(FVector FireDirectionEnemigo); //Funcion que tiene la finalidad de disparar un proyectil.


	void ShotTimerExpired();


private:
	//The Clock Tower of this Subscriber
	UPROPERTY()
		AClockTower* ClockTower;

public:
	//Called when this Subscriber is destroyed, it will unsubscribe this from the Clock Tower
	virtual void Destroyed() override;

public:

	//Called when the Plublisher changed its state, it will execute this Subscriber routine

	virtual void Update(class APublisher* Publisher) override;

	//Execute this Subscriber routine
	virtual void Morph();

	//Set the Clock Tower of this Subscriber
	void SetClockTower(AClockTower* myClockTower);

	class ANaveAereaJugador* NaveAereaJugador;

	FTimerHandle AFreakyTimerHandle1;
	bool hola;
};
