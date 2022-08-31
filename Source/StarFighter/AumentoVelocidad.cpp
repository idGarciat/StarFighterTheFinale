// Fill out your copyright notice in the Description page of Project Settings.


#include "AumentoVelocidad.h"

int AAumentoVelocidad::Velocidad()
{
	Super::Velocidad();
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, TEXT("la nave aumenta su velocidad"));
	return Super::Velocidad() + 100;


}

