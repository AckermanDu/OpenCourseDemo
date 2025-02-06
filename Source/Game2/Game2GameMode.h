// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Game2GameMode.generated.h"

class UMainMenuWidget;
class USuccessUI;
class UFailWidget;

UCLASS(minimalapi)
class AGame2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
    AGame2GameMode();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Game")
    void GameSuccess();

    UFUNCTION(BlueprintCallable, Category = "Game")
    void GameFail(AGame2Character* PlayerCharacter);

    void EnemyDestroyed();
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<USuccessUI> SuccessUIClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UFailWidget> FailUIClass;

private:
    int32 n;
};



