// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Nest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNestDelegate);


UCLASS()
class FIRST_DEMO_API ANest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void OnConstruction(const FTransform& Transform) override;

public:
    UPROPERTY(BlueprintAssignable, Category = "Nest")
    FNestDelegate OnFireflyEntered;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Nest")
    class AFirefly* m_pHeldFirefly = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Nest")
    UStaticMeshComponent* m_pStaticMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Nest")
    class USphereComponent* m_pFireflyAttractSphere;

    USceneComponent* m_pRootSceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nest")
    float m_fAttractRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nest")
    float m_fFireflyConvinceDelay;	
};
