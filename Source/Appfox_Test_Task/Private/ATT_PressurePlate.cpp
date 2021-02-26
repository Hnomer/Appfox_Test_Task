// Fill out your copyright notice in the Description page of Project Settings.


#include "ATT_PressurePlate.h"
#include "Net/UnrealNetwork.h"

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

AATT_PressurePlate::AATT_PressurePlate()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));

	PressurePlateMesh = CreateDefaultSubobject<UStaticMeshComponent>("PressurePlate");
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("CollisionBox");
	
	PressurePlateMesh->SetupAttachment(RootComponent);
	CollisionBox->SetupAttachment(RootComponent);

}

void AATT_PressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AATT_PressurePlate::OnCollisionBoxBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AATT_PressurePlate::OnCollisionBoxEndOverlap);
}

void AATT_PressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AATT_PressurePlate::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > &OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AATT_PressurePlate, bIsPressed);
}

void AATT_PressurePlate::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!(GetNetMode() == ENetMode::NM_Client))
	{
		if (!bIsPressed)
		{
			bIsPressed = true;

			SetLampsState(true);

			OnPressurePlateStateChanged();
		}
	}
}

void AATT_PressurePlate::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!(GetNetMode() == ENetMode::NM_Client))
	{
		TArray<AActor*> OverlappingActors;
		CollisionBox->GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

		if (OverlappingActors.Num() == 0)
		{
			bIsPressed = false;

			SetLampsState(false);

			OnPressurePlateStateChanged();
		}
	}
}

void AATT_PressurePlate::SetLampsState(bool State)
{
	for (AATT_Lamp* Lamp : LampsArray)
	{
		if (Lamp)
		{
			Lamp->SetLampState(State);
		}
	}
}

void AATT_PressurePlate::OnPressurePlateStateChanged()
{
	if (bIsPressed)
	{
		OnPlateSteppedOn();
	}
	else
	{
		OnPlateSteppedOff();
	}
}