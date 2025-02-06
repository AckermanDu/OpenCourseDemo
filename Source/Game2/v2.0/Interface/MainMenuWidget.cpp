// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // �󶨰�ť����¼�
    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartButtonClicked);
    }
}

void UMainMenuWidget::OnStartButtonClicked()
{
    // ���ؽ���
    RemoveFromParent();

    // �����������
    APlayerController* PlayerController = GetOwningPlayer();
    if (PlayerController)
    {
        PlayerController->SetInputMode(FInputModeGameOnly());
        PlayerController->bShowMouseCursor = false;
    }

    // �����Ҫ���عؿ������Ե������´���
    // UGameplayStatics::OpenLevel(this, FName("YourLevelName"));
}
