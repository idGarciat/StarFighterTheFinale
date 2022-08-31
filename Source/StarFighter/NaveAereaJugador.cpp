// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAereaJugador.h"
#include "Proyectil.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Metralleta.h"

void ANaveAereaJugador::BeginPlay()
{


	Super::BeginPlay();
	UWorld* const World = GetWorld();

	ConcreteJugador = GetWorld()->SpawnActor<AConcreteJugador>(AConcreteJugador::StaticClass());
	AumentoVelocidad = GetWorld()->SpawnActor<AAumentoVelocidad>(AAumentoVelocidad::StaticClass());
	AumentoVelocidad->SetJugador(ConcreteJugador);
	GetWorldTimerManager().SetTimer(MovTimerHandle, this, &ANaveAereaJugador::contar, 01.0f, true, 1.0f);

	abc = 0;
	otrobool = false;
	uno=false;
	dos = false;
	tres = false;
	cuatro = false;
	cinco = false;
	seis = false;
	siete = false;
	ocho = false;
	nueve = false;
	diez = false;

	RedAmiga = GetWorld()->SpawnActor<ARedAmiga>(ARedAmiga::StaticClass());
	//NaveAereaAmiga = GetWorld()->SpawnActor<ANaveAereaAmiga>(ANaveAereaAmiga::StaticClass());
	//NaveAereaAmiga->DefinirRedAmiga(RedAmiga);

	ClockTower = GetWorld()->SpawnActor<AClockTower>(AClockTower::StaticClass());
	FreakyAllen = GetWorld()->SpawnActor<AFreakyAllen>(AFreakyAllen::StaticClass());
	FreakyAllen->SetClockTower(ClockTower);

}

ANaveAereaJugador::ANaveAereaJugador()
{
	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	ShipInventory = CreateDefaultSubobject<UInventoryComponent>("MyInventory");

	// Movement
	MoveSpeed = 1000.0f;

	Energy = 100.0f;

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f; 
	bCanFire = false;

	FireForwardValue = 1.0f;
	FireRightValue = 0.0f;

	//const FVector MoveDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);

	//const FRotator FireRotation = MoveDirection.Rotation();
	//// Spawn projectile at an offset from this pawn
	//const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

	//UWorld* const World = GetWorld();
	//if (World != nullptr)
	//{
	//	//FTransform SpawnLocation;
	//	// spawn the projectile
	//	
	//	ColaProyectiles.Push(World->SpawnActor<AProyectil>(SpawnLocation, FireRotation));
	//	ColaProyectiles.Push(World->SpawnActor<AProyectil>(SpawnLocation, FireRotation));
	//	ColaProyectiles.Push(World->SpawnActor<AProyectil>(SpawnLocation, FireRotation));
	//	ColaProyectiles.Push(World->SpawnActor<AProyectil>(SpawnLocation, FireRotation));
	//	ColaProyectiles.Push(World->SpawnActor<AProyectil>(SpawnLocation, FireRotation));

	//	//UE_LOG(LogTemp, Warning, TEXT("SpawnLocation(X, Y) = %s, %s FireRotation(X, Y) =  s, s"), SpawnLocation.X, SpawnLocation.Y);
	//	//UE_LOG(LogTemp, Warning, TEXT("World not nullptr"));
	//}





	NaveInfo.Add("Vida", 100); //iniciamos con un dato de vida en 100
	Vida = 10000;//mi valor de vida sera 100

	NaveInfo.Add("velocidad", 1000);
}

void ANaveAereaJugador::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	//PlayerInputComponent->BindAction(Fire)
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ANaveAereaJugador::Fire);
	PlayerInputComponent->BindAction(TEXT("DropItem"), EInputEvent::IE_Pressed, this, &ANaveAereaJugador::DropItem);
	PlayerInputComponent->BindAction(TEXT("Amigo"), EInputEvent::IE_Pressed, this, &ANaveAereaJugador::Amigo);


	PlayerInputComponent->BindAction(TEXT("AumentoV"), IE_Pressed, this, &ANaveAereaJugador::UsarVelocidad);

	//PlayerInputComponent->BindAction(FireBinding);
	//PlayerInputComponent->BindAxis(FireForwardBinding);
	//PlayerInputComponent->BindAxis(FireRightBinding);
}

void ANaveAereaJugador::Amigo()
{
	ClockTower->SetTimeOfDay("Somos amigos");
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Amiguita")));
}

void ANaveAereaJugador::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	if (ForwardValue != 0.0f || RightValue != 0.0f) {

		if (ForwardValue != FireForwardValue) {
			FireForwardValue = ForwardValue;
		}

		if (RightValue != FireRightValue) {
			FireRightValue = RightValue;
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("ForwardValue: %f RightValue: %f"), ForwardValue, RightValue);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}

	if (ForwardValue != 0.0f || RightValue != 0.0f)
	{

		ClockTower->SetTimeOfDay("Enemigo en movimiento");
		RedAmiga->DefinirEstado("Amigo en movimiento");

	}

	if (ForwardValue == 0.0f || RightValue == 0.0f)
	{

		ClockTower->SetTimeOfDay("Enemigo estatico");
		RedAmiga->DefinirEstado("Amigo estatico");

	}


	LoctActX = GetActorLocation().X;
	LoctActY = GetActorLocation().Y;

}

void ANaveAereaJugador::Fire() 
{
	//ClockTower->SetTimeOfDay("Enemigo Atacando");

	bCanFire = true;
	UE_LOG(LogTemp, Warning, TEXT("Se presiono la barra espaciadora"));
	// Create fire direction vector
	ClockTower->SetTimeOfDay("Enemigo Atacando");
	RedAmiga->DefinirEstado("Amigo Atacando");

	UE_LOG(LogTemp, Warning, TEXT("FireForwardValue: %f FireRightValue: %f"), FireForwardValue, FireRightValue);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	//const FVector FireDirection = GetActorLocation();//
	// Try and fire a shot
	FireShot(FireDirection);

}

void ANaveAereaJugador::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{

		// If we are pressing fire stick in a direction
		//if (FireDirection.SizeSquared() > 0.0f)
		//{
		const FRotator FireRotation = FireDirection.Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// spawn the projectile
			World->SpawnActor<AProyectil>(SpawnLocation, FireRotation);
			//UE_LOG(LogTemp, Warning, TEXT("SpawnLocation(X, Y) = %s, %s FireRotation(X, Y) =  s, s"), SpawnLocation.X, SpawnLocation.Y);
			//UE_LOG(LogTemp, Warning, TEXT("World not nullptr"));
		}



		//bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAereaJugador::ShotTimerExpired, FireRate);

		// try and play the sound if specified

	/*	if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}*/
		//}
	}
}

void ANaveAereaJugador::ShotTimerExpired()
{
	bCanFire = true;
}

void ANaveAereaJugador::DropItem()
{
	if (ShipInventory->CurrentInventory.Num() == 0)
	{
		return;
	}
	AInventoryActor* Item = ShipInventory->CurrentInventory.Last();
	ShipInventory->RemoveFromInventory(Item);
	//should probably use scaled bounding box
	FVector ItemOrigin;
	FVector ItemBounds;
	Item->GetActorBounds(false, ItemOrigin, ItemBounds);
	FTransform PutDownLocation = GetTransform() + FTransform(RootComponent->GetForwardVector() * ItemBounds.GetMax());
	Item->PutDown(PutDownLocation);
}

void ANaveAereaJugador::TakeItem(AInventoryActor* InventoryItem)
{
	InventoryItem->PickUp();
	ShipInventory->AddToInventory(InventoryItem);
}

void ANaveAereaJugador::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	AInventoryActor* InventoryItem = Cast<AInventoryActor>(Other);
	if (InventoryItem != nullptr)
	{
		TakeItem(InventoryItem);

		if (InventoryItem != nullptr)
		{
			int n = rand() % 6 + 1;

			switch (n)
			{
			case 1:
			{
				
				for (auto& Elem : NaveInfo) //usando los datos de la nave
				{
					GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));//mostramos en pantalla la cantidad de vida
				}

				FString nV = "Velocidad";
				for (auto& pair : NaveInfo)
				{
					if (pair.Key == nV)
					{
						if (pair.Value > 0)
						{
							pair.Value = pair.Value + 50;
							MoveSpeed = MoveSpeed + 50;

						}



					}
				}
			}
			break;
			case 2:
			{
				
				for (auto& Elem : NaveInfo) //usando los datos de la nave
				{
					GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));//mostramos en pantalla la cantidad de vida
				}

				FString nV = "Velocidad";
				for (auto& pair : NaveInfo)
				{
					if (pair.Key == nV)
					{
						if (pair.Value > 0)
						{
							pair.Value = pair.Value - 50;
							MoveSpeed = MoveSpeed - 50;
						}



					}
				}
			}
			break;
			case 3:
			{
				
				for (auto& Elem : NaveInfo) //usando los datos de la nave
				{
					GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));//mostramos en pantalla la cantidad de vida
				}

				FString nVD = "Vida";
				for (auto& pair : NaveInfo)
				{
					if (pair.Key == nVD)
					{
						if (pair.Value > 0)
						{
							pair.Value = pair.Value + 10;

							Vida = Vida + 10; //reducir la vida de 10 en 10 al recibir un impacto
						}



					}
				}
			}
			break;
			case 4:
			{
				
				for (auto& Elem : NaveInfo) //usando los datos de la nave
				{
					GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));//mostramos en pantalla la cantidad de vida
				}

				FString nNV = "Vida";
				for (auto& pair : NaveInfo)
				{
					if (pair.Key == nNV)
					{
						if (pair.Value > 0)
						{
							pair.Value = pair.Value - 10;

							Vida = Vida - 10; //reducir la vida de 10 en 10 al recibir un impacto

							if (Vida == 0) //si mi vida es igual a 0, entonces mi NaveJugador desaparece.
							{


								SetActorTickEnabled(false);
								SetActorHiddenInGame(true);
								SetActorEnableCollision(false);
							}
							break;
						}



					}
				}
			}
			break;
			case 5:
			{

				UWorld* const World = GetWorld();
				ANaveAereaJugador* avatarT = Cast<ANaveAereaJugador>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
				FVector toPlayerT = avatarT->GetActorLocation() - GetActorLocation();
				toPlayerT.Normalize();


				TArray<AActor*> Instances; //creamos un TArray para almacenar la cantidad de naves creadas

				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANaveAereaAmiga::StaticClass(), Instances);

				if (Instances.Num() > 1) //si la cantidad de naves creadas es mayor a 1, entonces se destruiran las siguientes creadas.
				{
				//If exist at least one of them, set the instance with the first found one
				Instance = Cast<ANaveAereaAmiga>(Instances[0]);
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("%s already exists"), *Instance->GetName()));
				//Then Destroy this Actor
				Destroy();
				}


				//World->SpawnActor<ANaveAereaAmiga>(FVector(LoctActX,LoctActY+100 , 200.0f), FRotator::ZeroRotator);
				NaveAereaAmiga = GetWorld()->SpawnActor<ANaveAereaAmiga>(FVector(LoctActX, LoctActY + 100, 200.0f), FRotator::ZeroRotator),(ANaveAereaAmiga::StaticClass());
				NaveAereaAmiga->DefinirRedAmiga(RedAmiga);
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Black, FString::Printf(TEXT("Tienes un amigo")));

				
			}
			break;
			default:
				break;
			}

	}

	
	}




	AProyectil* Choque = Cast<AProyectil>(Other);//cada vez que un Proyectil nos haga contacto, hara la siguiente funcion
	if (Choque != nullptr)
	{
		for (auto& Elem : NaveInfo) //usando los datos de la nave
		{
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));//mostramos en pantalla la cantidad de vida
		}

		FString n = "Vida";
		for (auto& pair : NaveInfo)
		{
			if (pair.Key == n)
			{
				if (pair.Value >= 0)
				{
					pair.Value = pair.Value - 10;

					Vida = Vida - 10; //reducir la vida de 10 en 10 al recibir un impacto

					if (Vida == 0) //si mi vida es igual a 0, entonces mi NaveJugador desaparece.
					{

						SetActorTickEnabled(false);
						SetActorHiddenInGame(true);
						SetActorEnableCollision(false);
					}
					break;
				}



			}
		}

	}
}

void ANaveAereaJugador::AumentoVelocidadT()
{
	Jugador = AumentoVelocidad;

	MoveSpeed = Jugador->Velocidad() + MoveSpeed;

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Velocidad aumento en %i."), Jugador->Velocidad()));

	
}

void ANaveAereaJugador::UsarVelocidad()
{
	
	if (uno == true) {
		AumentoVelocidadT();
		GetWorldTimerManager().SetTimer(Mov1TimerHandle, this, &ANaveAereaJugador::GuardarVelocidad, 01.0f, false, 5.0f);
		uno = false;
	}

	otrobool = true;

	dos = false;
	tres = false;
	cuatro = false;
	cinco = false;
	seis = false;
	siete = false;
	ocho = false;
	nueve = false;
	diez = false;
	abc = 0;

}

void ANaveAereaJugador::contar()
{
	abc = abc + 1;
	if (abc == 1) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("UNO")));
		uno = true;
	}
	else if (abc == 2) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("DOS")));
		dos = true;
	}
	else if (abc == 3) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("TRES")));
		tres = true;
	}
	else if (abc == 4) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("CUATRO")));
		cuatro= true;
	}
	else if (abc == 5) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("CINCO")));
		cinco = true;
	}
	else if (abc == 6) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("SEIS")));
		seis = true;
	}
	else if (abc == 7) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("SIETE")));
		siete = true;
	}
	else if (abc == 8) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("OCHO")));
		ocho = true;
	}
	else if (abc == 9) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("NUEVE")));
		nueve = true;
	}
	else if (abc == 10) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("DIEZ")));
		diez = true;
	}
	else if (abc > 10) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("MAS DE 10")));
		abc = 10;
	}


}

void ANaveAereaJugador::GuardarVelocidad()
{
	MoveSpeed = 1000.0f;
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Me llamaste papu")));
}