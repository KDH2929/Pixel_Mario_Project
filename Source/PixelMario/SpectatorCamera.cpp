// Fill out your copyright notice in the Description page of Project Settings.


#include "SpectatorCamera.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


ASpectatorCamera::ASpectatorCamera()
{
	static ConstructorHelpers::FObjectFinder<UInputAction> ChangeCamAction(TEXT("InputAction'/Game/ThirdPerson/Input/Actions/IA_SpectatorCam.IA_SpectatorCam'"));
	if (ChangeCamAction.Succeeded())
	{
		IA_ChangeCam = ChangeCamAction.Object;
	}
}


void ASpectatorCamera::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_ChangeCam, ETriggerEvent::Triggered, this, &ASpectatorCamera::ChangeCam);
	}
}

void ASpectatorCamera::ChangeCam()
{
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), FoundActors);

	if (!FoundActors.IsEmpty())
	{
		AController* PlayerController = GetController();

		PlayerController->Possess(Cast<APlayerCharacter>(FoundActors[0]));
		GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ASpectatorCamera::DestroyActor, 1.0f, false);
	}
}

void ASpectatorCamera::DestroyActor()
{
	Destroy();
}
