// Copyright (c) 2023 Smoking Carrots. All rights reserved.


#include "BLActionWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/ListView.h"
#include "UI/Entries/BLActionEntryWidget.h"
#include "UI/Entries/BLActionEntryData.h"

void UBLActionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ClickedButton = nullptr;

	DescDisplay->SetText(FText::FromString(""));

	ActionsList->OnItemClicked().AddUObject(this, &UBLActionWidget::OnActionClicked);
}

void UBLActionWidget::ChangeName(UBLActionEntryData* ActionEntry)
{
	UBLActionEntryWidget* Button = Cast<UBLActionEntryWidget>(ActionsList->GetEntryWidgetFromItem(ActionEntry));
	if (Button)
	{
		Button->Name->SetText(ActionEntry->Name);
	}
}

void UBLActionWidget::ResetAction()
{
	if (ClickedButton)
	{
		ClickedButton->SetIsClicked(false);
		ClickedButton = nullptr;
	}

	DescDisplay->SetText(FText::FromString(""));
}

void UBLActionWidget::ShowDescription(int32 Index)
{
	if (Descriptions.IsValidIndex(Index))
	{
		DescDisplay->SetText(Descriptions[Index]);
	}
}

