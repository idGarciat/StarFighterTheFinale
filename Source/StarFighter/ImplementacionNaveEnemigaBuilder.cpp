// Fill out your copyright notice in the Description page of Project Settings.


#include "ImplementacionNaveEnemigaBuilder.h"
#include "DirectorNaveEnemigaBuilder.h"
#include "NaveEnemigaCazaBuilder.h"
// Sets default values
AImplementacionNaveEnemigaBuilder::AImplementacionNaveEnemigaBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AImplementacionNaveEnemigaBuilder::BeginPlay()
{
	Super::BeginPlay();
	
	NaveEnemigaCazaBuilder= GetWorld()->SpawnActor<ANaveEnemigaCazaBuilder>(ANaveEnemigaCazaBuilder::StaticClass());

	DirectorNaveEnemigaBuilder= GetWorld()->SpawnActor<ADirectorNaveEnemigaBuilder>(ADirectorNaveEnemigaBuilder::StaticClass());




	DirectorNaveEnemigaBuilder->SetNaveEnemigaBuilder(NaveEnemigaCazaBuilder);
	DirectorNaveEnemigaBuilder->ConstruirNaveEnemiga();

	ANaveEnemiga* NaveEnemiga = DirectorNaveEnemigaBuilder->GetNaveEnemiga();
	NaveEnemiga->CaracteristicasNaveEnemiga();
}

// Called every frame
void AImplementacionNaveEnemigaBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

