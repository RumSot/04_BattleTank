

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetSpawnedActor() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	// Configuration
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AActor> SpawnClass;		// Alternative: https://docs.unrealengine.com/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/TSubclassOf/index.html

	UPROPERTY()
	AActor* SpawnedActor = nullptr;
};
