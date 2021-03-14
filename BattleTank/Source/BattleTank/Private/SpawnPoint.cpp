


#include "SpawnPoint.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// ...

	auto TransformToComponentLocation = GetComponentTransform();
	auto NewActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, TransformToComponentLocation);

	if (!NewActor) {
		return;
	}
	auto TransformRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, false);	// Since we have already applied a transformation in SpawnActorDefered we want to keep the current world position.
	NewActor->AttachToComponent(this, TransformRules);

	UGameplayStatics::FinishSpawningActor(NewActor, TransformToComponentLocation);
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

