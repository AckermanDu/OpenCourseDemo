// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game2/Myself/MyCharacter.h"
#include "EnemyCharacter.generated.h"

class AGame2Projectile;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class GAME2_API AEnemyCharacter : public AMyCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyCharacter();

	virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
        FVector NormalImpulse, const FHitResult& Hit);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float maxHealth = 100.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float currentHealth;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> HealthWidgetClass;

    UFUNCTION()
    void UpdateHealthUI();

private:
    FTimerHandle FireTimerHandle;

    UPROPERTY(EditAnywhere, Category = "Combat")
    float FireRate = 2.0f; 

    UPROPERTY(EditAnywhere, Category = "Combat")
    FVector FireOffset = FVector(50.0f, 0.0f, 50.0f);

    void FireProjectile();

    UPROPERTY(EditAnywhere, Category = "Combat")
    TSubclassOf<class AGame2Projectile> ProjectileClass;

};
