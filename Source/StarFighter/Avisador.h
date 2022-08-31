// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Avisado.h"
#include "Avisador.generated.h"

UCLASS()
class STARFIGHTER_API AAvisador : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAvisador();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	TArray<AActor*> Suscriptores = TArray<AActor*>();

public:

	//Add the pased Subscriber to the list
	virtual void Suscribirse(AActor* Suscribirse);
	//Remove the passed Subscriber from the list
	virtual void DeSuscribirse(AActor* SuscribirseQuitar);
	//Notify all the Subscribers that something has changed
	virtual void AvisarSuscribtores();
};
