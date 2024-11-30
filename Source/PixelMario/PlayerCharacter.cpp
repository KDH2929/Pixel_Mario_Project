

#include "PlayerCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"
#include "ThirdPersonCharacter.h"
#include "SpectatorCamera.h"


APlayerCharacter::APlayerCharacter()
{
    AnimState = 0;
}

int APlayerCharacter::GetAnimState()
{
    return AnimState;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
        //KeyNum1
        EnhancedInputComponent->BindAction(KeyNum1_Action, ETriggerEvent::Triggered, this, &APlayerCharacter::PlayDance1);

        //KeyNum2
        EnhancedInputComponent->BindAction(KeyNum2_Action, ETriggerEvent::Triggered, this, &APlayerCharacter::PlayDance2);

        //KeyNum3
        EnhancedInputComponent->BindAction(KeyNum3_Action, ETriggerEvent::Triggered, this, &APlayerCharacter::PlayDance3);

        //KeyNum4
        EnhancedInputComponent->BindAction(KeyNum4_Action, ETriggerEvent::Triggered, this, &APlayerCharacter::PlayDance4);

        //KeyNum5
        EnhancedInputComponent->BindAction(KeyNum5_Action, ETriggerEvent::Triggered, this, &APlayerCharacter::PlayDance5);

        // Mouse Scroll
        EnhancedInputComponent->BindAction(Scroll_Action, ETriggerEvent::Triggered, this, &APlayerCharacter::ChangeFOV);

        // Button R
        EnhancedInputComponent->BindAction(ChangeFreeCam_Action, ETriggerEvent::Triggered, this, &APlayerCharacter::ChangeFreeCam);

	}
}

void APlayerCharacter::PlayDance1()
{
    if (AnimState == 1)
    {
        AnimState = 0;
    }

    else
    {
        AnimState = 1;
    }
}


void APlayerCharacter::PlayDance2()
{
    if (AnimState == 2)
    {
        AnimState = 0;
    }

    else
    {
        AnimState = 2;
    }
}


void APlayerCharacter::PlayDance3()
{
    if (AnimState == 3)
    {
        AnimState = 0;
    }

    else
    {
        AnimState = 3;
    }
}


void APlayerCharacter::PlayDance4()
{
    if (AnimState == 4)
    {
        AnimState = 0;
    }

    else
    {
        AnimState = 4;
    }
}


void APlayerCharacter::PlayDance5()
{
    if (AnimState == 5)
    {
        AnimState = 0;
    }

    else
    {
        AnimState = 5;
    }
}

void APlayerCharacter::ChangeFOV(const FInputActionValue& Value)
{
    UCameraComponent* Camera = GetFollowCamera();

    float FOV = Camera->FieldOfView;

    float Val = Value.Get<float>();

    Camera->SetFieldOfView(FOV - (Val * 3));

}

void APlayerCharacter::ChangeFreeCam()
{
    FTransform SpawnTransform = GetFollowCamera()->GetComponentTransform();

    AActor* SpawnedCamera = GetWorld()->SpawnActor<ASpectatorCamera>(ASpectatorCamera::StaticClass(), SpawnTransform);

    AController* PlayerController = GetController();

    if (SpawnedCamera)
    {
        PlayerController->Possess(Cast<ASpectatorCamera>(SpawnedCamera));
    }

}
