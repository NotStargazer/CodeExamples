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

//-- PlayerCharacter.cpp --//
void PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentSpeed = GetCharacterMovement()->Velocity.Size();
	CheckIfCharacterIsMoving();

	Cooldown -= DeltaTime * GetPlayerSpeedRatio();
}

/// <summary>
/// Gets a percentage between 0 to 1 based on the players stop speed to the players maximum speed.
/// </summary>
/// <returns>: Float ranging from 0 to 1</returns>
float PlayerCharacter::GetPlayerSpeedPercentage() const
{
	float MaxSpeed = GetMovementComponent()->GetMaxSpeed();
	float CurrentCharacterSpeed = GetMovementComponent()->Velocity.Size();

	return (FMath::Clamp<float>(CurrentCharacterSpeed / MaxSpeed, 0, 1)) * SlowdownEffectMod;
}
