// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BLCombatUtilities.h"
#include "BLCombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class BLADEOFLEGEND_API UBLCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBLCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void StartCombat();

	/** Sets the flag if it was a sneak attack (the player attacked first in Overworld). */
	UFUNCTION(BlueprintCallable)
	void SneakAttack();

	UFUNCTION(BlueprintCallable)
	void AddExpAndMoney(int32 Exp, int32 Money);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCombatData CombatData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPostCombatData PostCombatData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bBossFight = false;
};
