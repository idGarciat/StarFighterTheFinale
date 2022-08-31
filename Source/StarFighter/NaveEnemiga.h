 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nave.h"
#include "NaveEnemiga.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API ANaveEnemiga : public ANave
{
	GENERATED_BODY()
private:
	FString SistemaDefensa;
	FString SistemaAtaque;
	FString SistemaDesplazamiento;
	FString SistemaCamuflaje;

public:
	void SetSistemaDefensa(FString _SistemaDefensa) { SistemaDefensa = _SistemaDefensa; }
	void SetSistemaAtaque(FString _SistemaAtaque) { SistemaAtaque = _SistemaAtaque; }
	void SetSistemaDesplazamiento(FString _SistemaDesplazamiento) { SistemaDesplazamiento = _SistemaDesplazamiento; }
	void SetSistemaCamuflaje(FString _SistemaCamuflaje) { SistemaCamuflaje = _SistemaCamuflaje; }

	void CaracteristicasNaveEnemiga();

};
