// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PawnPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGESCAPE_API APawnPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
        UFUNCTION(BlueprintImplementableEvent)
        void OnEscapeCompleted(APawn* InstigatorPawn, bool bEscapeComplete);
};
