// Fill out your copyright notice in the Description page of Project Settings.


#include "FreakyAllen.h"
#include "Publisher.h"
#include "Kismet/GameplayStatics.h"
#include "ClockTower.h"
#include "Proyectil.h"
// Sets default values
AFreakyAllen::AFreakyAllen()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FreakyMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));

	FreakyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FreakyMesh"));
	RootComponent = FreakyMeshComponent;
	FreakyMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	FreakyMeshComponent->SetStaticMesh(FreakyMesh.Object);


	MoveSpeedNewNaveNodriza = 10.0f; //para la velocidad
	GunOffset = FVector(90.f, 0.f, 0.f); //para la distancia de aparicion de la bala.
	FireRate = 2.0f;
	bCanFire = true;
	hola = false;
	MovingNX = 0.0f;
	MovingNY = 0.0f;


}
// Called when the game starts or when spawned
void AFreakyAllen::BeginPlay()
{
	Super::BeginPlay();


}
// Called every frame
void AFreakyAllen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (hola == true)
	{

		bCanFire = false;
		//SetActorLocation(FVector(NaveAereaJugador->LoctActX + 1000.0f, NaveAereaJugador->LoctActY + 1000.0f,0));
		ANaveAereaJugador* avatarT = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (!avatarT)
		{
			return;

		}
		FVector toPlayerT = avatarT->GetActorLocation() - GetActorLocation();
		toPlayerT.Normalize();


		const FVector MoveDirection = toPlayerT;
		const FVector Movement = MoveDirection * MoveSpeedNewNaveNodriza;

		if (Movement.SizeSquared() > 0.0f)
		{
			const FRotator NewRotation = Movement.Rotation();

			FHitResult Hit(1.0f);
			RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		}

	}

}

void AFreakyAllen::Destroyed()
{

	Super::Destroyed();
	//Log Error if its Clock Tower is NULL
	if (!ClockTower)
	{
		UE_LOG(LogTemp, Error, TEXT("Destroyed():ClockTower is NULL, make sure it's initialized."));
		return;
	}
	//Unsubscribe from the Clock Tower if it's destroyed
	ClockTower->UnSubscribe(this);
}

void AFreakyAllen::Update(APublisher* Publisher)
{
	//Execute the routine
	Morph();
}
void AFreakyAllen::Morph()
{
	//Log Error if its Clock Tower is NULL
	if (!ClockTower)
	{
		UE_LOG(LogTemp, Error, TEXT("Morph(): ClockTower is NULL, make sure it's initialized.")); return;
	}
	//Get the current time of the Clock Tower
	FString Time = ClockTower->GetTime();
	if (!Time.Compare("Enemigo en movimiento"))
	{
		//Execute the Morning routine
		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, FString::Printf(TEXT("It is %s, so FreakyAllen se esta moviendo"), *Time));

		srand(time(NULL));//toma el tiempo de la computadora y esto hace que no halla randoms iguales

		//MovingNX = rand() % 18 - 10; //random eje X 

		//MovingNY = rand() % 18 - 10; //random eje Y 
		//const FVector MoveDirection = FVector(MovingNX, MovingNY, 0.0f);//formamos un vector direccion con los valores random de X y Y
		//const FVector Movement = MoveDirection * MoveSpeedNewNaveNodriza;

		//if (Movement.SizeSquared() > 0.0f)
		//{
		//	const FRotator NewRotation = Movement.Rotation();

		//	FHitResult Hit(1.0f);
		//	RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		//}
	}

	else if (!Time.Compare("Enemigo estatico"))
	{
		//Execute the Midday routine
		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, FString::Printf(TEXT("It is %s, so FreakyAllen's right eye starts to twitch"),*Time));

	}
	else if (!Time.Compare("Enemigo Atacando"))
	{
		//Execute the Evening routine
		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, FString::Printf(TEXT("It is %s, so FreakyAllen morphs into a blood sucking wogglesnort"),*Time));
		//UE_LOG(LogTemp, Error, TEXT("It is % s, so FreakyAllen morphs into a blood sucking wogglesnort"),*Time);
		FireNewNaveNodriza();

	}
	else if (!Time.Compare("Somos amigos"))
	{

		hola = true;
		GetWorldTimerManager().SetTimer(AFreakyTimerHandle1, this, &AFreakyAllen::FireNewNaveNodriza, 02.0f, true, 1.0f);
	}
}

void AFreakyAllen::SetClockTower(AClockTower* myClockTower)
{
	//Log Error if the passed Clock Tower is NULL
	if (!myClockTower)
	{
		UE_LOG(LogTemp, Error, TEXT("SetClockTower(): myClockTower is NULL, make sure it'sinitialized."));
		return;
	}
	//Set the Clock Tower and Subscribe to that
	ClockTower = myClockTower;
	ClockTower->Subscribe(this);
}

void AFreakyAllen::FireNewNaveNodriza()
{
	const FVector FireDirectionNewNaveNodriza = FVector(MovingNX, MovingNY, 0.0f).GetClampedToMaxSize(1.0f);

	FireShotNewNaveNodriza(FireDirectionNewNaveNodriza);
}

void AFreakyAllen::FireShotNewNaveNodriza(FVector FireDirectionNewNaveNodriza)
{
	if (bCanFire == true)
	{
		/*ANaveAereaJugador* Pavatar = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)); //obtiene la ubicacion de mi Pawn o NaveJugador
		if (!Pavatar)
		{
			return;

		}
		FVector toPlayer = Pavatar->GetActorLocation() - GetActorLocation();*/

		const FRotator FireRotation = FireDirectionNewNaveNodriza.Rotation();//toma una rotacion aleatoria 
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			World->SpawnActor<AProyectil>(SpawnLocation, FireRotation);
		}

		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AFreakyAllen::ShotTimerExpired, FireRate);
	}
}

void AFreakyAllen::ShotTimerExpired()
{
	bCanFire = true;
}


