// Fill out your copyright notice in the Description page of Project Settings.

#include "Firefly.h"
#include "First_DemoCharacter.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Nest.h"

// Sets default values
AFirefly::AFirefly()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_fFollowConvinceTimer = -1.0f;
	m_fPlayerConvinceDelay = 3.0f;
    
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

	m_pCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	m_pCollisionSphere->InitSphereRadius(10.0f);
	m_pCollisionSphere->SetupAttachment(RootComponent);
    m_pCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AFirefly::OnBeginAttract);
    m_pCollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AFirefly::OnEndAttract);


	m_pPotentialFollowTarget = nullptr;
}

// Called when the game starts or when spawned
void AFirefly::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFirefly::OnBeginAttract(class UPrimitiveComponent* ThisComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if(!OtherComp || !OtherComp->ComponentHasTag(TEXT("FireflyCollision")))
    {
        return;
    }


    AActor* pHolderActor = nullptr;
    auto pAttachParent = RootComponent->GetAttachParent();
    if (pAttachParent)
    {
        pHolderActor = pAttachParent->GetOwner();
    }

    if(pHolderActor && pHolderActor->IsA(ANest::StaticClass()))
    {
        // If we're already attached to a nest, we don't care about anything.
        // We could maybe even just deactivate the collision mesh
        return;
    }


    if (OtherActor->IsA(ANest::StaticClass()))
    {
        ANest* pNest = static_cast<ANest*>(OtherActor);
        if(pNest->m_pHeldFirefly)
        {
            // The nest already holds a firefly so we dont go in the nest
            return;
        }

        m_pPotentialFollowTarget = OtherComp;
        m_fFollowConvinceTimer = pNest->m_fFireflyConvinceDelay;
        return;
    }

	if (OtherActor->IsA(AFirst_DemoCharacter::StaticClass()))
	{
        auto pCharacter = static_cast<AFirst_DemoCharacter*>(OtherActor);
        if (pCharacter->m_pHeldFirefly)
        {
            // The character already has a firefly, we dont follow him
            return;
        }
        m_pPotentialFollowTarget = OtherComp;
        m_fFollowConvinceTimer = m_fPlayerConvinceDelay;
	}
}

void AFirefly::OnEndAttract(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    m_pPotentialFollowTarget = nullptr;
	m_fFollowConvinceTimer = -1.0f;
}

// Called every frame
void AFirefly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!m_pPotentialFollowTarget)
	{	// Orbit
		float timeSeconds = GetWorld()->GetTimeSeconds();
		float fSin, fCos;
		FMath::SinCos(&fSin, &fCos, timeSeconds * PI * m_fOrbitFreq);

		float fHeight = FMath::Sin(timeSeconds * PI * m_fOrbitHeightFreq);

		FVector vNewLocation(fSin * m_fOrbitRadius, fCos * m_fOrbitRadius, fHeight * m_fOrbitHeight);
		m_pStaticMesh->SetRelativeLocation(vNewLocation);
	}

    if(m_fFollowConvinceTimer >= 0.0f)
	{
		m_fFollowConvinceTimer -= DeltaTime;
		if (m_fFollowConvinceTimer < 0.0f)
		{
            AActor* pPrevHolderActor = nullptr;
            auto pAttachParent = RootComponent->GetAttachParent();
            if (pAttachParent)
            {
                pPrevHolderActor = pAttachParent->GetOwner();
            }
            if(pPrevHolderActor && pPrevHolderActor->IsA(AFirst_DemoCharacter::StaticClass()))
            {
                auto pPrevCharacter = static_cast<AFirst_DemoCharacter*>(pPrevHolderActor);
                pPrevCharacter->m_pHeldFirefly = nullptr;
            }

			m_fFollowConvinceTimer = -1.0f;

            auto pNewHolderActor = m_pPotentialFollowTarget->GetOwner();
            if(pNewHolderActor->IsA(AFirst_DemoCharacter::StaticClass()))
            {
                auto pCharacter = static_cast<AFirst_DemoCharacter*>(pNewHolderActor);
                pCharacter->m_pHeldFirefly = this;
            }
            else if(pNewHolderActor->IsA(ANest::StaticClass()))
            {
                auto pNest = static_cast<ANest*>(pNewHolderActor);
                pNest->m_pHeldFirefly = this;
                pNest->OnFireflyEntered.Broadcast();
            }

            // @Note This calls OverlapEnd so the potentialFollowTarget might be nulled out after this line.
            AttachToComponent(m_pPotentialFollowTarget, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			m_pPotentialFollowTarget = nullptr;
		}
	}
}

