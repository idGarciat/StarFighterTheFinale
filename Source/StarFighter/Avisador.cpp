// Fill out your copyright notice in the Description page of Project Settings.


#include "Avisador.h"

// Sets default values
AAvisador::AAvisador()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAvisador::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvisador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAvisador::Suscribirse(AActor* Suscribirse)
{
	Suscriptores.Add(Suscribirse);
}

void AAvisador::DeSuscribirse(AActor* SuscribirseQuitar)
{
	Suscriptores.Remove(SuscribirseQuitar);
}

void AAvisador::AvisarSuscribtores()
{
	for (AActor* Actor : Suscriptores)
	{
		//Cast each of them to a concrete Subscriber
		IAvisado* Sub = Cast<IAvisado>(Actor);
		if (Sub)
		{
			Sub->Actualizar(this);
		}
	}
}

