// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Avisador.h"
#include "RedAmiga.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API ARedAmiga : public AAvisador
{
	GENERATED_BODY()
public:
	ARedAmiga();
	FString Estado;
	void EstadoCambiado();
	void DefinirEstado(FString MiEstado);
	FORCEINLINE FString ObtenerEstado() { return Estado; }
};
