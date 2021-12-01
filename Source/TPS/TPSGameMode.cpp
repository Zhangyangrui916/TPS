#include "TPSGameMode.h"
#include "TPSCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
ATPSGameMode::ATPSGameMode():Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/ThirdPersonCPP/Blueprints/TPSCharacter_BP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>MainMenuClass(TEXT("WidgetBlueprint'/Game/UI/MainMenu.MainMenu_C'"));
	StartingWidgetClass = MainMenuClass.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget>InGameUIClass(TEXT("WidgetBlueprint'/Game/UI/InGameUI.InGameUI_C'"));
	InGameWidgetClass = InGameUIClass.Class;
}


void ATPSGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if (CurrentWidget != nullptr)
    {
        CurrentWidget->RemoveFromViewport();
    }

    if (NewWidgetClass == nullptr)
    {
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, 0);
        PlayerController->bShowMouseCursor = false;
        PlayerController->SetInputMode(FInputModeGameOnly());
        NewWidgetClass = InGameWidgetClass;
    }

    CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
    CurrentWidget->AddToViewport();
}


void ATPSGameMode::StartPlay()
{
    Super::StartPlay();
    ChangeMenuWidget(StartingWidgetClass);

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, 0);

    PlayerController->bShowMouseCursor = true;

    FInputModeUIOnly inputMode = FInputModeUIOnly().SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock).SetWidgetToFocus(CurrentWidget->TakeWidget());
    PlayerController->SetInputMode(inputMode);
}


