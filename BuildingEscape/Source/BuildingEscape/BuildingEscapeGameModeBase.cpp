// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscapeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PawnPlayerController.h"

void ABuildingEscapeGameModeBase::OnEscapeComplete(APawn* InstigatorPawn, bool bEscapeComplete)
{
	if (InstigatorPawn)
	{
		if (SpectatorViewpointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatorViewpointClass, ReturnedActors);
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];


				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetInstigatorController());
				if (PC)
				{
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("PlayerController cast failed"));
				}

				
				APawn* Pawn = PC->GetPawn();

				if (Pawn)
				{
					APawnPlayerController* PPC = Cast<APawnPlayerController>(Pawn->GetController());

					if (PPC)
					{
						PPC->OnEscapeCompleted(InstigatorPawn, bEscapeComplete);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("PawnPlayerController cast failed"));
					}
				}

				
			}
		}
	}



}