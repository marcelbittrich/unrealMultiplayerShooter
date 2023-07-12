// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Casing.generated.h"

UCLASS()
class BLASTER_API ACasing : public AActor
{
	GENERATED_BODY()
	
public:	
	ACasing();

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CasingMesh;

	UPROPERTY(EditAnywhere)
	float ShellEjectionImpulse = 10.f;
	UPROPERTY(EditAnywhere)
	float MaxRandomImpulse = 2.f;
	UPROPERTY(EditAnywhere)
	float MaxRandomEjectAngle = 5.f;
	
	UPROPERTY(EditAnywhere)
	class USoundCue* ShellSound;

public:	
	virtual void Tick(float DeltaTime) override;

};
