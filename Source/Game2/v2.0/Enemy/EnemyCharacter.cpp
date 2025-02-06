// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Game2/Game2Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
#include "Game2/Game2GameMode.h"



AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;


    //Set Collision refeclt , only respon to Game2Projectile
    UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
    CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore); // default ignore all
    CapsuleComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
    currentHealth = maxHealth;
    CapsuleComp->OnComponentHit.AddDynamic(this, &AEnemyCharacter::OnHit);

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetRelativeLocation(FVector(0, 0, 200.0f));
    HealthWidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f));
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AEnemyCharacter::FireProjectile, FireRate, true);

    if (HealthWidgetClass)
    {
        HealthWidgetComponent->SetWidgetClass(HealthWidgetClass);
        HealthWidgetComponent->InitWidget();
        UpdateHealthUI();
    }
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AEnemyCharacter::FireProjectile()
{
    if (ProjectileClass)
    {
        FVector SpawnLocation = GetActorLocation() + FireOffset;
        FRotator SpawnRotation = GetActorRotation();

        GetWorld()->SpawnActor<AGame2Projectile>(ProjectileClass, SpawnLocation, SpawnRotation);
    }
}

void AEnemyCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor->IsA(AGame2Projectile::StaticClass()))
    {
        currentHealth -= 30.0f;
        UpdateHealthUI();
        //FString testMessage = FString::Printf(TEXT("currentHealth = %f"), currentHealth);
        //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, testMessage);

        if (currentHealth <= 0.0f)
        {
            if (AGame2GameMode* GameMode = Cast<AGame2GameMode>(GetWorld()->GetAuthGameMode()))
            {
                GameMode->EnemyDestroyed();
            }

            GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
            Destroy();
        }
    }

}

void AEnemyCharacter::UpdateHealthUI()
{
    UUserWidget* HealthWidget = HealthWidgetComponent->GetUserWidgetObject();
    if (HealthWidget)
    {
        UProgressBar* HealthBar = Cast<UProgressBar>(HealthWidget->GetWidgetFromName(TEXT("HealthBar")));
        if (HealthBar)
        {
            HealthBar->SetPercent(currentHealth / maxHealth);
        }
    }
}