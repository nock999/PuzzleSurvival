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

	UFUNCTION()
	void OnBeginAttract(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnEndAttract(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void OnConstruction(const FTransform& Transform) override;

	bool m_bFollowingPlayer;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Firefly")
	UStaticMeshComponent* m_pStaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Firefly")
	class USphereComponent* m_pPlayerAttractSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Firefly")
	class USphereComponent* m_pCollisionSphere;

	USceneComponent* m_pRootSceneComponent;
	USceneComponent* m_pPotentialFollowTarget;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firefly")
	float m_fPlayerConvinceDelay;
};
