// Fill out your copyright notice in the Description page of Project Settings.

#include "Nest.h"
#include "Firefly.h"
#include "First_DemoCharacter.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ANest::ANest()
{
    m_fAttractRange = 200.0f;

    m_fFireflyConvinceDelay = 0.0f;

    m_pRootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
    RootComponent = m_pRootSceneComponent;

    m_pStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Geometry"));
    m_pStaticMesh->SetupAttachment(RootComponent);
    m_pStaticMesh->bGenerateOverlapEvents = false;

    m_pFireflyAttractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttractSphere"));
    m_pFireflyAttractSphere->SetupAttachment(RootComponent);
    m_pFireflyAttractSphere->InitSphereRadius(m_fAttractRange);
    m_pFireflyAttractSphere->SetHiddenInGame(false);
    m_pFireflyAttractSphere->SetVisibility(true);
    m_pFireflyAttractSphere->ComponentTags.Add(TEXT("FireflyCollision"));
}

// Called when the game starts or when spawned
void ANest::BeginPlay()
{
	Super::BeginPlay();
}

void ANest::OnConstruction(const FTransform& Transform)
{
    m_pFireflyAttractSphere->InitSphereRadius(m_fAttractRange);
}

