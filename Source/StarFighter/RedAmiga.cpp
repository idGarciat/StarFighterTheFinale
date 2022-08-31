// Fill out your copyright notice in the Description page of Project Settings.


#include "RedAmiga.h"

ARedAmiga::ARedAmiga()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARedAmiga::EstadoCambiado()
{
	AvisarSuscribtores();
}

void ARedAmiga::DefinirEstado(FString MiEstado)
{
	Estado = MiEstado;
	EstadoCambiado();
}
