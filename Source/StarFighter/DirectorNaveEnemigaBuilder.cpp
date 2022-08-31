// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectorNaveEnemigaBuilder.h"

// Sets default values
ADirectorNaveEnemigaBuilder::ADirectorNaveEnemigaBuilder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADirectorNaveEnemigaBuilder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADirectorNaveEnemigaBuilder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADirectorNaveEnemigaBuilder::ConstruirNaveEnemiga()
{
	if (!NaveEnemigaBuilder)
	{
		UE_LOG(LogTemp, Warning, TEXT("ConstruirNaveEnemiga(): NaveEnemigaBuilder es NULL, asegurese de inicializar correctamente esta clase"));
	}

	
	NaveEnemigaBuilder->BuildSistemaDefensa();
	NaveEnemigaBuilder->BuildSistemaAtaque();
	NaveEnemigaBuilder->BuildSistemaDesplazamiento();
	NaveEnemigaBuilder->BuildSistemaCamuflaje();
	
}

void ADirectorNaveEnemigaBuilder::SetNaveEnemigaBuilder(AActor* Builder)
{

	NaveEnemigaBuilder = Cast<INaveEnemigaBuilder>(Builder);
	if (!NaveEnemigaBuilder)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("invalido ")));

		UE_LOG(LogTemp, Warning, TEXT("ConstruirNaveEnemiga(): NaveEnemigaBuilder es NULL, asegurese de inicializar correctamente esta clase"));
	}



}

ANaveEnemiga* ADirectorNaveEnemigaBuilder::GetNaveEnemiga()
{
	if (NaveEnemigaBuilder)
	{
		return NaveEnemigaBuilder->GetNaveEnemiga();
		
	}

	UE_LOG(LogTemp, Warning, TEXT("GetNaveEnemiga(): retorna NULL"));
	return nullptr;
}

