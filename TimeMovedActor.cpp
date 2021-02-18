#include "TimeMovedActor.h"


ATimeMovedActor::ATimeMovedActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATimeMovedActor::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	AFG19n20GP2Character* PlayerCharacter = Cast<AFG19n20GP2Character>(PC->GetPawn());
	Player = PlayerCharacter;

	if (IsValid(PlayerCharacter))
	{
		Player->MoveActorsDelegate.AddDynamic(this, &ATimeMovedActor::UpdateMove);
		bPlayerMoving = Player->GetIsMoving();
	}
}

void ATimeMovedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPlayerMoving || bDeactivateTimeStop)
	{
		TimeTick(DeltaTime, Player->GetPlayerSpeedRatio());
	}
	else
	{
		StopTick();
	}

}

void ATimeMovedActor::UpdateMove(bool Update)
{
	bPlayerMoving = Update;
}

