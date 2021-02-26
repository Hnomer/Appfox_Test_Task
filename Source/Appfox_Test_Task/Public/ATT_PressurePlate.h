// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ATT_Lamp.h"
#include "GameFramework/Character.h"

#include "ATT_PressurePlate.generated.h"

UCLASS()
class APPFOX_TEST_TASK_API AATT_PressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AATT_PressurePlate();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UBoxComponent* CollisionBox;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent* PressurePlateMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<AATT_Lamp*> LampsArray;


	UFUNCTION()
	void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlateSteppedOn();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPlateSteppedOff();

	void SetLampsState(bool State);

private:

	//Is pressure plate pressed or not
	UPROPERTY(ReplicatedUsing = OnPressurePlateStateChanged)
	bool bIsPressed = false;

	UFUNCTION()
		void OnPressurePlateStateChanged();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
