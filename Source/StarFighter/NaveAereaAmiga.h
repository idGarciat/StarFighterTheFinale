// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAerea.h"
#include "Avisado.h"
#include "Cambiar.h"
#include "NaveAereaJugador.h"
#include "NaveAereaAmiga.generated.h"
class ARedAmiga;
/**
 * 
 */
UCLASS()
class STARFIGHTER_API ANaveAereaAmiga : public ANaveAerea, public IAvisado, public ICambiar
{
	GENERATED_BODY()
public:
		ANaveAereaAmiga();

		virtual void BeginPlay() override;

		void Tick(float DeltaTime);

		ANaveAereaAmiga* Instance;

		uint32 bCanFire : 1;
		FTimerHandle TimerHandle_ShotTimerExpired;

		FTimerHandle MemberTimerHandle1;

		UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
			FVector GunOffset;
		UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
			float FireRate;
		UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
			float MoveSpeedAmiga;
		float MovingNX;
		float MovingNY;

		void FuegoAmigo(); 
		void DisparoAmigo(FVector FireDirectionEnemigo);
		void ShotTimerExpired();
		FTimerHandle AAmigoTimerHandle1;
private:
		UPROPERTY()
			ARedAmiga* RedAmiga;
public:
		virtual void Destroyed() override;

		virtual void Actualizar(class AAvisador* Avisador) override;

		virtual void Cambiar();

		void DefinirRedAmiga(ARedAmiga* MiRedAmiga);
		bool Moverse;
};
