// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 绑定按钮点击事件
    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartButtonClicked);
    }
}

void UMainMenuWidget::OnStartButtonClicked()
{
    // 隐藏界面
    RemoveFromParent();

    // 启用玩家输入
    APlayerController* PlayerController = GetOwningPlayer();
    if (PlayerController)
    {
        PlayerController->SetInputMode(FInputModeGameOnly());
        PlayerController->bShowMouseCursor = false;
    }

    // 如果需要加载关卡，可以调用以下代码
    // UGameplayStatics::OpenLevel(this, FName("YourLevelName"));
}
