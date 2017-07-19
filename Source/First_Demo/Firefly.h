// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Firefly.generated.h"

UCLASS()
class FIRST_DEMO_API AFirefly : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFirefly();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Firefly")
	UStaticMeshComponent* m_pStaticMesh;
	class USphereComponent* m_pPlayerAttractSphere;

	USceneComponent* m_pRootSceneComponent;
	USceneComponent* m_pFollowTarget;

	float m_fPlayerConvinceTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firefly")
	float m_fOrbitRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firefly")
	float m_fOrbitHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firefly")
	float m_fOrbitHeightFreq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firefly")
	float m_fOrbitFreq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firefly")
	float m_fAttractRange;
};
