// Fill out your copyright notice in the Description page of Project Settings.


#include "Singleton.h"
#include "NewNaveNodriza.h"



//ANewNaveNodriza* ASingleton::Instancia = nullptr;


// Sets default values
ASingleton::ASingleton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASingleton::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Se creo nodriza"));

	for (int i = 0; i <= 4; i++)// creara la nave nodriza 5 veces,  y si el singleton funciona solo creara una sola naveNodriza.
	{
		float Randx = rand() % 200 - 10;
		float Randy = rand() % 200 - 10;
		ANewNaveNodriza* SpawnedNodriza = GetWorld()->SpawnActor<ANewNaveNodriza>(ANewNaveNodriza::StaticClass());
		//ANewNaveNodriza* SpawnedNodriza = GetWorld()->SpawnActor<ANewNaveNodriza>(FVector(Randx, Randy, 112.0f), FRotator::ZeroRotator);

		if (SpawnedNodriza) //muestra cuantas fueron creadas
		{
			//If the Spawn succeeds, set the Spawned inventory to the local one and log the success string
			Nodriza = SpawnedNodriza;
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s has been created"), *Nodriza->GetName()));
		}
	}
}

// Called every frame
void ASingleton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

