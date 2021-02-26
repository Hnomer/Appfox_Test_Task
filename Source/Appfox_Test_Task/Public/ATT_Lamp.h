// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"

#include "ATT_Lamp.generated.h"


UCLASS()
class APPFOX_TEST_TASK_API AATT_Lamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATT_Lamp();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* LampMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPointLightComponent* PointLight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FColor LampColor_Off;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimeBetweenColorSwitch = 3;

	UFUNCTION(Reliable, NetMulticast, WithValidation)
	void RPC_Client_ChangeLampColor(FColor NewColor);

	UPROPERTY(ReplicatedUsing = OnLampStateChanged)
	bool bIsLampOn = false;

	UFUNCTION()
	void OnLampStateChanged();

	void SetLampState(bool State);

	void StartColorIteration();
	void StopColorIteration();

	void SwitchToNextColor();
	void SwitchLampColor(FColor NewColor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandler;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
