// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nave.h"
#include "NewNaveNodriza.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API ANewNaveNodriza : public ANave
{
	GENERATED_BODY()
private:
	//=====================================================================================
	ANewNaveNodriza();
public:


	UPROPERTY()
	ANewNaveNodriza* Instance;
	//===================================================================================================================================================================
	

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





public:

	virtual void BeginPlay() override;

	void Tick(float DeltaSeconds); //funcion que se actualizara cada frame

	void FireNewNaveNodriza(); //funcion que llamara a FireShotAcuatica
	void FireShotNewNaveNodriza(FVector FireDirectionEnemigo); //Funcion que tiene la finalidad de disparar un proyectil


	void ShotTimerExpired();
};