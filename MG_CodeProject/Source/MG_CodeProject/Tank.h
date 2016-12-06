// Copyright Marett Creative Labs

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class AProjectile;
class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class MG_CODEPROJECT_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();


protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;


private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// Ref for spawning projectiles
	UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0;

};
