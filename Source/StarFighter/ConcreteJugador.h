// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Jugador.h"
#include "ConcreteJugador.generated.h"

UCLASS()
class STARFIGHTER_API AConcreteJugador : public AActor, public IJugador
{

	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConcreteJugador();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual int Velocidad()override { return 100; };
};
