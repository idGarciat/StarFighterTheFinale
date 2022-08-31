// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Jugador.h"
#include "Deccorator.generated.h"

UCLASS()
class STARFIGHTER_API ADeccorator : public AActor, public IJugador
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeccorator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	IJugador* Jugador;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual int Velocidad() override;

	void SetJugador(IJugador* _Jugador) { Jugador = _Jugador; }
	IJugador* GetJugador() { return Jugador; }
};
