// Fill out your copyright notice in the Description page of Project Settings.

#include "Firefly.h"


// Sets default values
AFirefly::AFirefly()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_fPlayerConvinceTimer = 0.0f;

	m_fOrbitRadius = 60.0f;
	m_fOrbitHeight = 20.0f;
	m_fOrbitHeightFreq = 1.0f;
	m_fOrbitFreq = 1.0f;
	m_fAttractRange = 300.0f;

	m_pRootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = m_pRootSceneComponent;

	m_pStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Geometry"));
	m_pStaticMesh->SetupAttachment(RootComponent);

	m_pPlayerAttractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttractSphere"));
	m_pPlayerAttractSphere->InitSphereRadius(m_fAttractRange);
	m_pPlayerAttractSphere->

	m_pFollowTarget = nullptr;
}

// Called when the game starts or when spawned
void AFirefly::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirefly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float timeSeconds = GetWorld()->GetTimeSeconds();
	float fSin, fCos;
	FMath::SinCos(&fSin, &fCos, timeSeconds * PI * m_fOrbitFreq);
	
	float fHeight = FMath::Sin(timeSeconds * PI * m_fOrbitHeightFreq);

	FVector vNewLocation(fSin * m_fOrbitRadius, fCos * m_fOrbitRadius, fHeight * m_fOrbitHeight);
	m_pStaticMesh->SetRelativeLocation(vNewLocation);
}

