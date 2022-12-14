// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogueManager.generated.h"

UCLASS()
class DIALOGUESYSTEM_API ADialogueManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogueManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// Starts a conversation using a data asset of type DialogueDataAsset
	/// </summary>
	/// <param name="asset"></param>
	UFUNCTION(CallInEditor)
	void startConversation(class UDialogueDataAsset* asset);
	
	/// <summary>
	/// Updates the public text and color values according to the current line
	/// </summary>
	/// <param name="speakername">The value the SpeakerText variable has to be changed to</param>
	/// <param name="dialogue">The value the DialogueText variable has to be changed to</param>
	void updateText(FString speakername, FString dialogue);

	/// <summary>
	/// Returns if a conversation is currently happening
	/// </summary>
	/// <returns>True if a conversation is currently ongoing</returns>
	bool convoIsHappening() { return _convoIsHappening; }

private:
	/// <summary>
	/// Goes to the next line of dialogue
	/// </summary>
	UFUNCTION(CallInEditor)
	void nextLine();

	/// <summary>
	/// Ends the conversation
	/// </summary>
	void endConversation();

public:
	/// <summary>
	/// Text that should be displayed in the speaker box
	/// </summary>
	FString SpeakerText;

	/// <summary>
	/// Text that should be displayed in the dialogue box
	/// </summary>
	FString DialogueText;

	/// <summary>
	/// The color of the box
	/// </summary>
	FLinearColor TextBoxColor;

	/// <summary>
	/// The color of the text
	/// </summary>
	FLinearColor TextColor;

private:
	UPROPERTY(VisibleAnywhere)
	TArray<FString> _lines;

	class UDialogueDataAsset* _currentConvo;

	UPROPERTY(EditAnywhere)
	class UDialogueDataAsset* _debugConvo;

	int _lineNum;
	bool _convoIsHappening = false;

};
