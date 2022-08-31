// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Metralleta.generated.h"

UCLASS()
class STARFIGHTER_API AMetralleta : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMetralleta();

	uint32 bCanFire : 1;
	FTimerHandle TimerHandle_ShotTimerExpired; //tiempo que toma de la PC
	FTimerHandle MemberTimerHandle; //caracteristica que usaremos en el BeginPlay
	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MetralletaMesh;


	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		FVector GunOffset;//es como la distancia que aparecera la proyectil.
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float FireRate; //propiedad que hara cuanto tardara en desaparecer el proyectil.
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float MoveSpeedMetralleta; //sera la velocidad usada por la NaveAccuatica

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void FireMetralleta(); //funcion que llamara a FireShotAcuatica
	void FireShotMetralleta(FVector FireDirectionEnemigo); //Funcion que tiene la finalidad de disparar un proyectil


	void ShotTimerExpired();
};
