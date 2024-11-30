// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ThirdPersonCharacter.h"
#include "PlayerChracter.generated.h"


UCLASS()
class PIXELMARIO_API APlayerChracter : public AThirdPersonCharacter
{
	GENERATED_BODY()

public:
	APlayerChracter();

	UFUNCTION(BlueprintCallable)
	int GetAnimState();


protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void PlayDance1();
	void PlayDance2();
	void PlayDance3();
	void PlayDance4();
	void PlayDance5();


private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* KeyNum1_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* KeyNum2_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* KeyNum3_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* KeyNum4_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* KeyNum5_Action;

	int AnimState;

};
