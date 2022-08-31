// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ImplementacionNaveEnemigaBuilder.generated.h"

UCLASS()
class STARFIGHTER_API AImplementacionNaveEnemigaBuilder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AImplementacionNaveEnemigaBuilder();

private:
	UPROPERTY(VisibleAnywhere, Category = "Implementacion builder")
		class ANaveEnemigaCazaBuilder* NaveEnemigaCazaBuilder;
	UPROPERTY(VisibleAnywhere, Category = "Implementacion builder")
		class ADirectorNaveEnemigaBuilder* DirectorNaveEnemigaBuilder;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
