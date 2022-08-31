// Fill out your copyright notice in the Description page of Project Settings.


#include "NewNaveNodriza.h"
#include "Kismet/GameplayStatics.h"
#include "Proyectil.h"
#include "NaveAereaJugador.h"
#include "NaveAcuatica.h"


ANewNaveNodriza::ANewNaveNodriza()
{
	//=======================================================================================================

	TArray<AActor*> Instances; //creamos un TArray para almacenar la cantidad de naves creadas

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANewNaveNodriza::StaticClass(), Instances);

	if (Instances.Num() > 1) //si la cantidad de naves creadas es mayor a 1, entonces se destruiran las siguientes creadas.
	{
		//If exist at least one of them, set the instance with the first found one
		Instance = Cast<ANewNaveNodriza>(Instances[0]);
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow,FString::Printf(TEXT("%s already exists"),*Instance->GetName()));
		//Then Destroy this Actor
		Destroy();
	}

	//=======================================================================================================
	MoveSpeedNewNaveNodriza = 50.0f; //para la velocidad
	GunOffset = FVector(90.f, 0.f, 0.f); //para la distancia de aparicion de la bala
	FireRate = 2.0f;
	bCanFire = true;

	MovingNX = 0.0f;
	MovingNY = 0.0f;
}

void ANewNaveNodriza::BeginPlay()
{
	Super::BeginPlay();


	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ANewNaveNodriza::FireNewNaveNodriza, 01.0f, true, 0.0f);//hara la funcion de disparo cada tiempo determinado.


}

void ANewNaveNodriza::Tick(float DeltaSeconds)
{
	srand(time(NULL));//toma el tiempo de la computadora y esto hace que no halla randoms iguales

	MovingNX = rand() % 18 - 10; //random eje X 
	MovingNY = rand() % 18 - 10; //random eje Y 

	const FVector MoveDirection = FVector(MovingNX, MovingNY, 0.0f);//formamos un vector direccion con los valores random de X y Y
	const FVector Movement = MoveDirection * MoveSpeedNewNaveNodriza * DeltaSeconds;

	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();

		FHitResult Hit(1.0f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
	}


}

void ANewNaveNodriza::FireNewNaveNodriza()
{


	bCanFire = true;
	float RandX = rand() % 500 - 50;
	float RandY = rand() % 500 - 50;
	const FVector FireDirectionNewNaveNodriza = FVector(RandX, RandY, 0.0f).GetClampedToMaxSize(1.0f); //vector que toma valores de NaveAcuatica


	FireShotNewNaveNodriza(FireDirectionNewNaveNodriza);
}

void ANewNaveNodriza::FireShotNewNaveNodriza(FVector FireDirectionNewNaveNodriza)
{
	if (bCanFire == true)
	{

		/*ANaveAereaJugador* Pavatar = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); //obtiene la ubicacion de mi Pawn o NaveJugador
		if (!Pavatar)
		{
			return;

		}
		FVector toPlayer = Pavatar->GetActorLocation() - GetActorLocation();*/


		const FRotator FireRotation = FRotator(0.0, rand() % 500 - 50, 0.0);//toma una rotacion aleatoria 
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			
			World->SpawnActor<AProyectil>(SpawnLocation, FireRotation); //creamos diferentes ubicaciones para 5 balas y estas sean disparadas simultanemaente
			World->SpawnActor<AProyectil>(SpawnLocation + FVector(50, -50, 0), FireRotation);
			World->SpawnActor<AProyectil>(SpawnLocation +FVector(-50, 50, 0), FireRotation);
			World->SpawnActor<AProyectil>(SpawnLocation + FVector(100, -100, 0), FireRotation);
			World->SpawnActor<AProyectil>(SpawnLocation + FVector(-100, 100, 0), FireRotation);

		}

		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANewNaveNodriza::ShotTimerExpired, FireRate);


		bCanFire = false;

	}
}

void ANewNaveNodriza::ShotTimerExpired()
{
	bCanFire = true;
}


