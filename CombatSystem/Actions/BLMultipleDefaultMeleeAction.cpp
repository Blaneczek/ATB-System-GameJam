// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "BLMultipleDefaultMeleeAction.h"
#include "Characters/BLCombatCharacter.h"
#include "PaperZDAnimInstance.h"
#include "PaperZDAnimationComponent.h"
#include "Kismet/GameplayStatics.h"

void UBLMultipleDefaultMeleeAction::ActivateAction(ABLCombatCharacter* Owner)
{
	if (Owner)
	{
		Owner->MultipleDefaultMeleeAction();
		Owner->SetCurrentME(FMath::Clamp((Owner->GetCurrentME() - MECost), 0.f, Owner->GetMaxME()));
	}
}

void UBLMultipleDefaultMeleeAction::ExecuteAction(ABLCombatCharacter* Owner, ABLCombatCharacter* Target)
{
	if (!Owner || !Target || Target->GetCurrentHP() <= 0)
	{
		OnEndExecution.ExecuteIfBound();
		return;
	}

	if (ActionAnim)
	{
		FZDOnAnimationOverrideEndSignature EndAnimDel;
		EndAnimDel.BindWeakLambda(this, [this](bool bResult) { OnEndExecution.ExecuteIfBound(); });
		Owner->GetAnimationComponent()->GetAnimInstance()->PlayAnimationOverride(ActionAnim, "DefaultSlot", 1.f, 0.0f, EndAnimDel);
		ActionCalculations(Owner, Target, CombatManager);
	}
	else
	{
		ActionCalculations(Owner, Target, CombatManager);
		OnEndExecution.ExecuteIfBound();
	}
}
 