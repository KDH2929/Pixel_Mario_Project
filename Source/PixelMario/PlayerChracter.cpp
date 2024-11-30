

#include "PlayerChracter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Controller.h"


APlayerChracter::APlayerChracter()
{
    AnimState = 0;
}

int APlayerChracter::GetAnimState()
{
    return AnimState;
}

void APlayerChracter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
        //KeyNum1
        EnhancedInputComponent->BindAction(KeyNum1_Action, ETriggerEvent::Triggered, this, &APlayerChracter::PlayDance1);

        //KeyNum2
        EnhancedInputComponent->BindAction(KeyNum2_Action, ETriggerEvent::Triggered, this, &APlayerChracter::PlayDance2);

        //KeyNum3
        EnhancedInputComponent->BindAction(KeyNum3_Action, ETriggerEvent::Triggered, this, &APlayerChracter::PlayDance3);

        //KeyNum4
        EnhancedInputComponent->BindAction(KeyNum4_Action, ETriggerEvent::Triggered, this, &APlayerChracter::PlayDance4);

        //KeyNum5
        EnhancedInputComponent->BindAction(KeyNum5_Action, ETriggerEvent::Triggered, this, &APlayerChracter::PlayDance5);

	}
}

void APlayerChracter::PlayDance1()
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


void APlayerChracter::PlayDance2()
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


void APlayerChracter::PlayDance3()
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


void APlayerChracter::PlayDance4()
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


void APlayerChracter::PlayDance5()
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
