// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	auto TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	LaunchBlast->AttachToComponent(RootComponent, TransformRules);
	LaunchBlast->bAutoActivate = true;

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	ImpactBlast->AttachToComponent(RootComponent, TransformRules);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, false);
	ExplosionForce->AttachToComponent(RootComponent, TransformRules);
	ExplosionForce->bAutoActivate = false;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);	// TODO: do we really want to keep this around?
	CollisionMesh->DestroyComponent();

	// TODO: randomise damage done.

	UGameplayStatics::ApplyRadialDamage(this,	// const UObject* WorldContextObject,
		ProjectileDamage,						// float BaseDamage, 
		GetActorLocation(),						// const FVector& Origin,
		ExplosionForce->Radius,					// float DamageRadius,								Note: if we change the radius in Projectile_BP this will automatically filter down
		UDamageType::StaticClass(),				// TSubclassOf<class UDamageType> DamageTypeClass,
		TArray<AActor *> ()						// const TArray<AActor*> &IgnoreActors,				Note: by passing an empty array we are saying damage all actors
	);


	FTimerHandle InOutTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(InOutTimerHandle, this, &AProjectile::DestroyProjectileOnTimerExpire, DestroyDelay);
}

void AProjectile::DestroyProjectileOnTimerExpire()
{
	Destroy();
}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

