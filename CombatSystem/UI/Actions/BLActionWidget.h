// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BLCombatUtilities.h"
#include "BLActionWidget.generated.h"

class UTextBlock;
class UBLAction;
class UListView;
class UBLActionEntryWidget;
class UBLActionEntryData;

DECLARE_DELEGATE_OneParam(FOnAction, const FCombatActionData& /*ActionData*/);

/**
 * 
 */
UCLASS()
class BLADEOFLEGEND_API UBLActionWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnActionClicked(UObject* Item) {};

	void ChangeName(UBLActionEntryData* ActionEntry);

public:
	/** Adds actions to Widget */
	virtual void AddActions(const TArray<TSoftClassPtr<UBLAction>>& InActions) {};

	/** Adds Crystal actions to Widget */
	virtual void AddActions(const TMap<ECrystalColor, FCrystalSkills>& InCrystalActions) {};

	/** Resets action to default state (no description and normal button) */
	virtual void ResetAction();

public:
	FOnAction OnAction;

protected:
	/** ListView with every hero's actions in a particular Action type */
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UListView> ActionsList;

	/** Place to display action description */
	UPROPERTY(BlueprintReadOnly, Category = "BL|Combat", meta = (BindWidget))
	TObjectPtr<UTextBlock> DescDisplay;

	/** Stores descriptions for all actions in a particular Action type */
	UPROPERTY()
	TArray<FText> Descriptions;

	UPROPERTY()
	TArray<float> MECosts;

	/** Clicked item in ListView */
	UPROPERTY()
	TObjectPtr<UBLActionEntryWidget> ClickedButton;

};
