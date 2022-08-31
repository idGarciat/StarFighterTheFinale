// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Deccorator.h"
#include "AumentoVelocidad.generated.h"

/**
 * 
 */
UCLASS()
class STARFIGHTER_API AAumentoVelocidad : public ADeccorator
{
	GENERATED_BODY()
public:
		virtual int Velocidad() override;

};
