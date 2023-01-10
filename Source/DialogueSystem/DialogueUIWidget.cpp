// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueUIWidget.h"
#include "DialogueManager.h"
#include "Kismet/GameplayStatics.h"
#include <Components/Image.h>
#include "OptionButtonWidget.h"

void UDialogueUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!_dialogueManager)
	{
		//Finds the dialogue manager actor in the scene 
		//THERE SHOULD ONLY BE ONE DIALOGUE MANAGER
		AActor* ManagerActor = UGameplayStatics::GetActorOfClass(GetWorld(), ADialogueManager::StaticClass());

		//Casts the actor as a dialogue manager
		_dialogueManager = Cast<ADialogueManager>(ManagerActor);

	}

	displayUI(_displayingUI);
}

void UDialogueUIWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (_dialogueManager->convoIsHappening())
	{
		if (!_displayingUI)
			displayUI(true);

		updateText();
	}
	else if (_dialogueManager->optionNum() > -1)
	{
		addOptions(_dialogueManager->optionNum());
	}
	else
	{
		if (_displayingUI)
			displayUI(false);
	}
}

void UDialogueUIWidget::updateText()
{
	SpeakerBoxText = _dialogueManager->SpeakerText;
	DialogueBoxText = _dialogueManager->DialogueText;
	BoxColor = _dialogueManager->TextBoxColor;
	TextColor = _dialogueManager->TextColor;
}

void UDialogueUIWidget::displayUI(bool value)
{
	if (value)
	{
		//Set the UI to be visible
		BoxColor.A = 1.0f;

		_displayingUI = true;
	}
	else
	{
		//Clear the text
		SpeakerBoxText = "";
		DialogueBoxText = "";

		//Set the UI to be invisible
		BoxColor.A = 0.0f;

		_displayingUI = false;
	}
}

void UDialogueUIWidget::addOptions(int optionNum)
{
	for (int i = 0; i < optionNum; i++)
	{
		UOptionButtonWidget* newOption;
		_optionButtons.Add(newOption);
	}
}
