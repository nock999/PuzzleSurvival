// Fill out your copyright notice in the Description page of Project Settings.

#include "Firefly.h"
#include "First_DemoCharacter.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
AFirefly::AFirefly()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_fPlayerConvinceTimer = -1.0f;
	m_fPlayerConvinceDelay = 3.0f;

	m_bFollowingPlayer = false;

	m_fOrbitRadius = 60.0f;
	m_fOrbitHeight = 20.0f;
	m_fOrbitHeightFreq = 1.0f;
	m_fOrbitFreq = 1.0f;
	m_fAttractRange = 300.0f;

	m_pRootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = m_pRootSceneComponent;

	m_pStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Geometry"));
	m_pStaticMesh->SetupAttachment(RootComponent);
	m_pStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_pStaticMesh->bGenerateOverlapEvents = false;

	m_pPlayerAttractSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttractSphere"));
	m_pPlayerAttractSphere->InitSphereRadius(m_fAttractRange);
	m_pPlayerAttractSphere->SetupAttachment(RootComponent);

	m_pPlayerAttractSphere->OnComponentBeginOverlap.AddDynamic(this, &AFirefly::OnBeginAttract);
	m_pPlayerAttractSphere->OnComponentEndOverlap.AddDynamic(this, &AFirefly::OnEndAttract);
	m_pPlayerAttractSphere->SetVisibility(true);

	m_pCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	m_pCollisionSphere->InitSphereRadius(10.0f);
	m_pCollisionSphere->SetupAttachment(RootComponent);
	m_pCollisionSphere->ComponentTags.Add(TEXT("FireflyCollision"));


	m_pPotentialFollowTarget = nullptr;
}

// Called when the game starts or when spawned
void AFirefly::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFirefly::OnBeginAttract(class UPrimitiveComponent* ThisComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	m_pPotentialFollowTarget = OtherComp;

	if (OtherActor->IsA(AFirst_DemoCharacter::StaticClass()))
	{
		m_fPlayerConvinceTimer = 0.0f;
	}
}

void AFirefly::OnEndAttract(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	m_fPlayerConvinceTimer = -1.0f;
}

void AFirefly::OnConstruction(const FTransform & Transform)
{
	m_pPlayerAttractSphere->InitSphereRadius(m_fAttractRange);
}

// Called every frame
void AFirefly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_fPlayerConvinceTimer < 0.0f)
	{	// Orbit
		float timeSeconds = GetWorld()->GetTimeSeconds();
		float fSin, fCos;
		FMath::SinCos(&fSin, &fCos, timeSeconds * PI * m_fOrbitFreq);

		float fHeight = FMath::Sin(timeSeconds * PI * m_fOrbitHeightFreq);

		FVector vNewLocation(fSin * m_fOrbitRadius, fCos * m_fOrbitRadius, fHeight * m_fOrbitHeight);
		m_pStaticMesh->SetRelativeLocation(vNewLocation);
	}
	else
	{
		m_fPlayerConvinceTimer += DeltaTime;
		if (m_fPlayerConvinceTimer >= m_fPlayerConvinceDelay)
		{
			m_fPlayerConvinceTimer = -1.0f;
			m_bFollowingPlayer = true;
			AttachToComponent(m_pPotentialFollowTarget, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			m_pPotentialFollowTarget = nullptr;
		}
	}
}

