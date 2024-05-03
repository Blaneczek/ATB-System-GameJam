// Copyright (c) 2023 Smoking Carrots. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BLCombatUtilities.h"
#include "BLCombatSlot.generated.h"

class ABLCombatCharacter;
class UBoxComponent;
class UStaticMeshComponent;
class UBLAction;
class UWidgetComponent;
class UBLActionEntryData;

DECLARE_DELEGATE_OneParam(FOnSelectedSlot, ABLCombatSlot* /*Slot*/);
DECLARE_DELEGATE_TwoParams(FOnCharActionEnded, ABLCombatSlot* /*Slot*/, bool /*bIsEnemy*/);
DECLARE_DELEGATE_OneParam(FOnCharHealthUpdate, ABLCombatSlot* /*Slot*/);
DECLARE_DELEGATE_TwoParams(FOnCharDeath, ABLCombatSlot* /*Slot*/, bool /*bIsEnemy*/);
DECLARE_DELEGATE_TwoParams(FOnEnemyAction, ABLCombatSlot* /*Slot*/, FCombatActionData&& /*ActionData*/);
DECLARE_DELEGATE_OneParam(FOnEscapeCombat, bool /*bSuccessful*/);

UCLASS()
class BLADEOFLEGEND_API ABLCombatSlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABLCombatSlot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	ABLCombatCharacter* GetCharacter() const { return Character; };

	int32 GetIndex() const { return Index; };

	bool IsEnemy() const { return bIsEnemy; };

	bool IsActive() const { return bIsActive; };

	float GetCooldown() const;

	void SpawnHero(const FCombatCharData& BaseData, const FCombatActions& CombatActions, bool bSneakAttack);

	void SpawnEnemy(const FCombatCharData& BaseData, const TArray<TSoftClassPtr<UBLAction>>& Actions, bool bSneakAttack);

	void PauseCharCooldown();
	void UnPauseCharCooldown();

	void DoAction(const TArray<ABLCombatSlot*>& TargetsSlots, const FCombatActionData& ActionData, AActor* CombatManager, bool bSummon = false);

	/** Selected Target effect */
	void SelectTarget(bool NewSelect);

	/** Selected Hero effect */
	void SelectHero(bool NewSelect);

	/** Hover slot effect */
	void HoverMouse(bool NewHover);

	void DestroyCharacter();

private:
	UFUNCTION()
	void EndCharCooldown();
	UFUNCTION()
	void ActionEnded();

	void StartCharCooldown();

	UFUNCTION()
	void HandleCharDeath();
	UFUNCTION()
	void UpdateCharHealth();

	/** Mouse hovered effect */
	UFUNCTION()
	void OnBeginMouseOver(UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void OnEndMouseOver(UPrimitiveComponent* TouchedComponent);
	/**/

	void EscapeCombat(bool bSuccessful);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BL|Combat")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BL|Combat")
	TObjectPtr<UWidgetComponent> TargetPointer;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BL|Combat")
	TObjectPtr<USceneComponent> HelperScene;

	UPROPERTY()
	bool bCanDoAction;
	UPROPERTY()
	bool bClicked;

	FOnSelectedSlot OnSelectedSlot;
	FOnCharActionEnded OnCharActionEnded;
	FOnCharHealthUpdate OnCharHealthUpdate;
	FOnCharDeath OnCharDeath;
	FOnEnemyAction OnEnemyAction;
	FOnEscapeCombat OnEscapeCombat;
	
private:
	UPROPERTY()
	bool bIsActive;

	UPROPERTY()
	TObjectPtr<ABLCombatCharacter> Character;

	UPROPERTY(EditInstanceOnly, Category = "BL|Combat")
	int32 Index;

	UPROPERTY(EditInstanceOnly, Category = "BL|Combat")
	bool bIsEnemy;

	UPROPERTY(EditDefaultsOnly, Category = "BL|Combat")
	TSubclassOf<UUserWidget> TargetWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "BL|Combat")
	TSubclassOf<UUserWidget> HoverWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "BL|Combat")
	TSubclassOf<UUserWidget> HeroWidgetClass;

}; 
