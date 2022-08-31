// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAerea.h"
//#include "Cola.h"
#include "InventoryComponent.h"
#include "ClockTower.h"
#include "Jugador.h"
#include "FreakyAllen.h"
#include "AumentoVelocidad.h"
#include "ConcreteJugador.h"
#include "NaveAereaAmiga.h"
#include "RedAmiga.h"
#include "NaveAereaJugador.generated.h"


/**
 *
 */

 //class AProyectil;

UCLASS()
class STARFIGHTER_API ANaveAereaJugador : public ANaveAerea
{
	GENERATED_BODY()

		/** The camera */
		UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Datos", meta = (AllowPrivateAccess = "true")) //Blueprint que podemos asignarle un "Dato" en este caso su vida
		FString NaveActorName;
	

	//Cola<class AProyectil*> ColaProyectiles;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	ANaveAereaJugador();

	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface

	void Fire();

	/* Fire a shot in the specified direction */
	void FireShot(FVector FireDirection);

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		FVector GunOffset;

	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float FireRate;

	//Inventario
	UPROPERTY()
		UInventoryComponent* ShipInventory;

	UFUNCTION()
		void TakeItem(AInventoryActor* InventoryItem);

	UFUNCTION()
		void DropItem();


	UFUNCTION()
		virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;



	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:

	float Vida; //vida usada para la nave jugador

	uint32 bCanFire : 1;


	FTimerHandle TimerHandle_ShotTimerExpired;

	float FireForwardValue; //valores aleatorios
	float FireRightValue;   //valores aleatorios


	TMap<FString, int32>NaveInfo; //almacenara los datos y valores de mi NaveJgador.

public:
	class AClockTower* ClockTower;
	class AFreakyAllen* FreakyAllen;
	class ANaveAereaAmiga* NaveAereaAmiga;
	class ARedAmiga* RedAmiga;

public:
	IJugador* Jugador;
	void AumentoVelocidadT();
	void GuardarVelocidad();
	void UsarVelocidad();
	void contar();
	FTimerHandle MovTimerHandle;
	FTimerHandle Mov1TimerHandle;
	int abc;
	bool otrobool;
	bool uno;
	bool dos;
	bool tres;
	bool cuatro;
	bool cinco;
	bool seis;
	bool siete;
	bool ocho;
	bool nueve;
	bool diez;
	AConcreteJugador* ConcreteJugador;
	AAumentoVelocidad* AumentoVelocidad;

	void Amigo();

	float LoctActX;
	float LoctActY;

	ANaveAereaAmiga* Instance;
};