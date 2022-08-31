// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAereaAmiga.h"
#include "Kismet/GameplayStatics.h"
#include "Avisador.h"
#include "Kismet/GameplayStatics.h"
#include "RedAmiga.h"
#include "Proyectil.h"

ANaveAereaAmiga::ANaveAereaAmiga()
{
	PrimaryActorTick.bCanEverTick = true;

	//TArray<AActor*> Instances; //creamos un TArray para almacenar la cantidad de naves creadas

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANaveAereaAmiga::StaticClass(), Instances);

	//if (Instances.Num() > 1) //si la cantidad de naves creadas es mayor a 1, entonces se destruiran las siguientes creadas.
	//{
	//	//If exist at least one of them, set the instance with the first found one
	//	Instance = Cast<ANaveAereaAmiga>(Instances[0]);
	//	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s already exists"), *Instance->GetName()));
	//	//Then Destroy this Actor
	//	Destroy();
	//}

	MoveSpeedAmiga = 15.0f; //para la velocidad
	GunOffset = FVector(90.f, 0.f, 0.f); //para la distancia de aparicion de la bala.
	FireRate = 2.0f;
	bCanFire = true;
	Moverse = false;

}

void ANaveAereaAmiga::BeginPlay()
{
	Super::BeginPlay();
}

void ANaveAereaAmiga::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Moverse==true)
	{
	ANaveAereaJugador* avatarT = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (!avatarT)
		{
			return;

		}
		FVector toPlayerT = avatarT->GetActorLocation() - GetActorLocation() + FVector(0,100,0);
		toPlayerT.Normalize();


		const FVector MoveDirection = toPlayerT;
		const FVector Movement = MoveDirection * MoveSpeedAmiga;

		if (Movement.SizeSquared() > 0.0f)
		{
			const FRotator NewRotation = Movement.Rotation();

			FHitResult Hit(1.0f);
			RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		}

	}

}

void ANaveAereaAmiga::FuegoAmigo()
{
	const FVector FireDirectionNaveAereaAmiga = FVector(MovingNX, MovingNY, 0.0f).GetClampedToMaxSize(1.0f);

	DisparoAmigo(FireDirectionNaveAereaAmiga);
}

void ANaveAereaAmiga::DisparoAmigo(FVector DireccionFuegoAmigo)
{
	if (bCanFire == true)
	{
		const FRotator FuegoRotation = DireccionFuegoAmigo.Rotation();
		const FVector SpawnLocation = GetActorLocation() + FuegoRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			World->SpawnActor<AProyectil>(SpawnLocation, FuegoRotation);
		}

		//World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAereaAmiga::ShotTimerExpired, FireRate);
	}
}

void ANaveAereaAmiga::ShotTimerExpired()
{
	bCanFire = true;
}

void ANaveAereaAmiga::Destroyed()
{
	Super::Destroyed();
	//Log Error if its Clock Tower is NULL
	if (!RedAmiga)
	{
		UE_LOG(LogTemp, Error, TEXT("Destroyed():No hay red alv"));
		return;
	}
	//Unsubscribe from the Clock Tower if it's destroyed
	RedAmiga->DeSuscribirse(this);
}

void ANaveAereaAmiga::Actualizar(AAvisador* Avisador)
{
	Cambiar();
}

void ANaveAereaAmiga::Cambiar()
{
	FString Estado = RedAmiga->ObtenerEstado();
	if (!Estado.Compare("Amigo en movimiento"))
	{

		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, FString::Printf(TEXT("It is %s, so FreakyAllen se esta moviendo"), *Estado));
		if (Moverse==false)
		{
		ANaveAereaJugador* avatarT = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (!avatarT)
		{
			return;

		}
		FVector toPlayerT = avatarT->GetActorLocation() - GetActorLocation() + FVector (0,100,0);
		toPlayerT.Normalize();


		const FVector MoveDirection = toPlayerT;
		const FVector Movement = MoveDirection * MoveSpeedAmiga;

		if (Movement.SizeSquared() > 0.0f)
		{
			const FRotator NewRotation = Movement.Rotation();

			FHitResult Hit(1.0f);
			RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		}
		}
	}

	else if (!Estado.Compare("Amigo estatico"))
	{
		//Execute the Midday routine
		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, FString::Printf(TEXT("El estado es %s, ta quieto"),*Estado));

	}
	else if (!Estado.Compare("Amigo Atacando"))
	{
		//Execute the Evening routine
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, FString::Printf(TEXT("El estado es %s, ta atacando"),*Estado));
		//UE_LOG(LogTemp, Error, TEXT("It is % s, so FreakyAllen morphs into a blood sucking wogglesnort"),*Time);
		FuegoAmigo();

	}
}

void ANaveAereaAmiga::DefinirRedAmiga(ARedAmiga* MiRedAmiga)
{
	//Set the Clock Tower and Subscribe to that
	RedAmiga = MiRedAmiga;
	RedAmiga->Suscribirse(this);
}
