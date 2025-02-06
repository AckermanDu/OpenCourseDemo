// Copyright Epic Games, Inc. All Rights Reserved.

#include "Game2GameMode.h"
#include "Game2Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Game2/v2.0/Interface/MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Game2Character.h"
#include "Game2/v2.0/Interface/FailWidget.h"
#include "Game2/v2.0/Interface/SuccessUI.h"

AGame2GameMode::AGame2GameMode()
//	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// set default UMG class '/Game/_MyBluePrint/HUD/WPB_MainMenu.WPB_MainMenu'
	static ConstructorHelpers::FClassFinder<UUserWidget> MainMenuWidgetBPClass(TEXT("/Game/_MyBluePrint/HUD/WPB_MainMenu.WPB_MainMenu"));
	if (MainMenuWidgetBPClass.Class != nullptr)
	{
		MainMenuWidgetClass = MainMenuWidgetBPClass.Class;
	}

    n = 5;
}

void AGame2GameMode::BeginPlay()
{
    Super::BeginPlay();

    // create and display START UI
    if (MainMenuWidgetClass)
    {
        UMainMenuWidget* MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
        if (MainMenuWidget)
        {
            MainMenuWidget->AddToViewport();

            //forbid player input and display mouse
            APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
            if (PlayerController)
            {
                PlayerController->SetInputMode(FInputModeUIOnly());
                PlayerController->bShowMouseCursor = true;
            }
        }
    }
}

void AGame2GameMode::GameSuccess()
{
    if (SuccessUIClass)
    {
        USuccessUI* SuccessWidget = CreateWidget<USuccessUI>(GetWorld(),SuccessUIClass);
        if (SuccessWidget)
        {
            SuccessWidget->AddToViewport();
        }
    }
}

void AGame2GameMode::GameFail(AGame2Character* PlayerCharacter)
{
    if (FailUIClass)
    {
        UFailWidget* FailWidget = CreateWidget<UFailWidget>(GetWorld(), FailUIClass);
        if (FailWidget)
        {
            FailWidget->AddToViewport();
        }
    }
}

void AGame2GameMode::EnemyDestroyed()
{
    n--;

    if (n <= 0)
    {
        GameSuccess();
    }
}
