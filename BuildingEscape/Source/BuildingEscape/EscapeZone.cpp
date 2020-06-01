// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeZone.h"
#include "PlayerPawn.h"
#include "BuildingEscapeGameModeBase.h"
#include "Components/BoxComponent.h"
#include "components/DecalComponent.h"

// Sets default values
AEscapeZone::AEscapeZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// Enum indicating how each type should respond
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//We only want care about the pawn
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//We created a vector of 200 unit size in x,y,z
	OverlapComp->SetBoxExtent(FVector(200.f));

	//The extraction zone is visible in game running
	OverlapComp->SetHiddenInGame(false);

	RootComponent = OverlapComp;

	//We call our method to handle overlapevents
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AEscapeZone::HandleOverlap);
}

// Called when the game starts or when spawned
void AEscapeZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEscapeZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPawn* Pawn = Cast<APlayerPawn>(OtherActor);

	if (!Pawn)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Player Escaped"));

	ABuildingEscapeGameModeBase* GM =  Cast<ABuildingEscapeGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		bool bEscapeComplete = true;

		GM->OnEscapeComplete(Pawn, bEscapeComplete);
	}



}

// Called every frame
void AEscapeZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

