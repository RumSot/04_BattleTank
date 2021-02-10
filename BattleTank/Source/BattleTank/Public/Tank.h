// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


// Forward declarations
class UTankBarrel;	
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();	// Note: Unreal wont' allow void Fire(void)

private:
	// Sets default values for this pawn's properties
	ATank();

	// TODO: Remove after debugging
	virtual void BeginPlay() override;

	// Tank does not need to tick, hence no tick method. Turning this off to improves performance.

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;	// Alternative: https://docs.unrealengine.com/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/TSubclassOf/index.html

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	// Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;	// TODO: Remove

	float LastFireTime = 0;
};
