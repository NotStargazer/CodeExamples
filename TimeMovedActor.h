#pragma once

#include "Kismet/GameplayStatics.h"
#include "FG19n20GP2\FG19n20GP2Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeMovedActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimeTick, float, PlayerSpeed);

//Derive from this class to add time movement based on player.
UCLASS(Blueprintable, BlueprintType, Abstract)
class FG19N20GP2_API ATimeMovedActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	PlayerCharacter* Player;

public:
	UPROPERTY()
	bool bPlayerMoving = false;

	UPROPERTY(BlueprintAssignable, Category = "Time Actor", meta = (DisplayName = "Time Tick"))
	FTimeTick TickOnMove;

	ATimeMovedActor();

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	// Updates player moving as the player moves or stops
	UFUNCTION()
	void UpdateMove(bool Update);

	// Ticks every frame the player is moving
	UFUNCTION(BlueprintNativeEvent)
	void TimeTick(float DeltaTime, float PlayerSpeed);
	virtual void TimeTick_Implementation(float DeltaTime, float PlayerSpeed) {};

	//Ticks every frame the player is stopped
	UFUNCTION(BlueprintNativeEvent)
	void StopTick();
	virtual void StopTick_Implementation() {};

protected:

	//For designers to debug stuff easier
	UPROPERTY(EditAnywhere, Category = "Debug Mode", meta = (ToolTip = "Toggle on or off for debugging the time stop mechanic."))
	bool bDeactivateTimeStop = false;
};
