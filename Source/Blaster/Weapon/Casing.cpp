// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Casing.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ACasing::ACasing()
{
	PrimaryActorTick.bCanEverTick = true;

	CasingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Casing Mesh"));
	SetRootComponent(CasingMesh);
	CasingMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	CasingMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	CasingMesh->SetSimulatePhysics(true);
	CasingMesh->SetEnableGravity(true);
	CasingMesh->SetNotifyRigidBodyCollision(true);
}

void ACasing::BeginPlay()
{
	Super::BeginPlay();

	CasingMesh->OnComponentHit.AddDynamic(this, &ACasing::OnHit);
	
	float RandomImpulseValue = FMath::FRandRange(-1,1.f) * MaxRandomImpulse;
	float EjectionImpulse = ShellEjectionImpulse + RandomImpulseValue;
	
	FRotator RandomRotationOffset = MaxRandomEjectAngle * FRotator(
		FMath::FRandRange(-1.f,1.f),
		FMath::FRandRange(-1.f,1.f),
		FMath::FRandRange(-1.f,1.f)) ;
	FVector EjectionDirection = RandomRotationOffset.RotateVector(GetActorForwardVector());
	
	CasingMesh->AddImpulse(EjectionImpulse * EjectionDirection);
	
	SetLifeSpan(3.f);
}

void ACasing::OnHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (ShellSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
	}	

	// Deactivate collision to prevent further hit events.
	CasingMesh->SetNotifyRigidBodyCollision(false);
	
	UE_LOG(LogTemp, Warning, TEXT("Shell Hit"));
}

void ACasing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

