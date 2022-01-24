// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosingBarrel.h"

#include "DrawDebugHelpers.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosingBarrel::ASExplosingBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetSimulatePhysics(true);
	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");

	RadialForce->SetupAttachment(RootComponent);

	RadialForce->ImpulseStrength = 2000.0f;
	RadialForce->Radius = 400.0f;
	RadialForce->ForceStrength = 10.0f;
	RadialForce->bImpulseVelChange = true;
	RadialForce->SetVisibility(true);

	// Optional, ignores 'Mass' of other objects (if false, the impulse strength will be much higher to push most objects depending on Mass)
	RadialForce->bImpulseVelChange = true;

	// Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic
	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);

}

// Called when the game starts or when spawned
void ASExplosingBarrel::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &ASExplosingBarrel::OnActorHit);

}

// Called every frame
void ASExplosingBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASExplosingBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForce->FireImpulse();

}

