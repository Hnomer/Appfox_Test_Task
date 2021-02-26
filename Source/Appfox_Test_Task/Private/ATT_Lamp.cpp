// Fill out your copyright notice in the Description page of Project Settings.


#include "ATT_Lamp.h"
#include "Net/UnrealNetwork.h"

#define D(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

// Sets default values
AATT_Lamp::AATT_Lamp()
{
	PrimaryActorTick.bCanEverTick = false;

	LampMesh = CreateDefaultSubobject<UStaticMeshComponent>("LampMesh");

	PointLight = CreateDefaultSubobject<UPointLightComponent>("PointLight");

	SetRootComponent(LampMesh);

	PointLight->SetupAttachment(RootComponent);
}

void AATT_Lamp::BeginPlay()
{
	Super::BeginPlay();
	
	LampMesh->SetMaterial(0, UMaterialInstanceDynamic::Create(LampMesh->GetMaterial(0), this));

	//SetLampState(false);
}

void AATT_Lamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AATT_Lamp::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AATT_Lamp, bIsLampOn);
}

void AATT_Lamp::OnLampStateChanged()
{
	if (bIsLampOn)
	{
		if (!(GetNetMode() == ENetMode::NM_Client))
		{
			StartColorIteration();
		}
	}
	else
	{
		StopColorIteration();

		((UMaterialInstanceDynamic*)LampMesh->GetMaterial(0))->SetVectorParameterValue("LampColor", LampColor_Off);
		((UMaterialInstanceDynamic*)LampMesh->GetMaterial(0))->SetScalarParameterValue("EmissiveMultiplier", 0);

		PointLight->SetIntensity(0);
	}
}

void AATT_Lamp::SetLampState(bool State)
{
	if (!(GetNetMode() == ENetMode::NM_Client))
	{
		bIsLampOn = State;
		OnLampStateChanged();
	}
}

void AATT_Lamp::StartColorIteration()
{
	GetWorldTimerManager().SetTimer(TimerHandler, this, &AATT_Lamp::SwitchToNextColor, TimeBetweenColorSwitch, true, 0.0f);
}

void AATT_Lamp::StopColorIteration()
{
	if (&TimerHandler)
	{
		GetWorldTimerManager().ClearTimer(TimerHandler);
	}
}

void AATT_Lamp::SwitchToNextColor()
{
	if (!(GetNetMode() == ENetMode::NM_Client))
	{
		RPC_Client_ChangeLampColor(FColor::MakeRandomColor());
	}
}

bool AATT_Lamp::RPC_Client_ChangeLampColor_Validate(FColor NewColor)
{
	return true;
}

void AATT_Lamp::RPC_Client_ChangeLampColor_Implementation(FColor NewColor)
{
	SwitchLampColor(NewColor);
}


void AATT_Lamp::SwitchLampColor(FColor NewColor)
{
	if (LampMesh && PointLight)
	{
		((UMaterialInstanceDynamic*)LampMesh->GetMaterial(0))->SetVectorParameterValue("LampColor", NewColor);
		((UMaterialInstanceDynamic*)LampMesh->GetMaterial(0))->SetScalarParameterValue("EmissiveMultiplier", 1);


		PointLight->SetLightColor(NewColor, true);
		PointLight->SetIntensity(5000);
	}
}

