


#include "SpawnPoint.h"
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

	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());

	if (!SpawnedActor) {
		return;
	}

	// Since we have already applied a transformation in SpawnActorDefered we want to keep the current world position.
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* USpawnPoint::GetSpawnedActor() const
{
	return SpawnedActor;
}

