// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManager.h"
#include "DialogueDataAsset.h"
#include "DialogueUIWidget.h"

// Sets default values
ADialogueManager::ADialogueManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADialogueManager::BeginPlay()
{
	Super::BeginPlay();
	startConversation(_debugConvo); //delete later
}

// Called every frame
void ADialogueManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADialogueManager::startConversation(UDialogueDataAsset* asset)
{
	//Set conversationIsHappening to true
	_convoIsHappening = true;

	//Set the line number to 0
	_lineNum = 0;

	//Clear the lines array
	_lines.Empty();

	//set the current convo to this asset
	_currentConvo = asset;

	//Loop through the current convo lines array
	for (int i = 0; i < _currentConvo->lines.Num(); i++)
	{
		//Add the current line's speaker text to the dialougemanager's lines
		_lines.Add(_currentConvo->lines[i].SpeakerText);
	}

	//update the text
	updateText(_currentConvo->lines[0].SpeakerName, _lines[0]);
}

void ADialogueManager::updateText(FString speakername, FString dialogue)
{
	TextBoxColor = _currentConvo->lines[_lineNum].TextBoxColor.ReinterpretAsLinear();
	TextColor = _currentConvo->lines[_lineNum].TextColor.ReinterpretAsLinear();
	SpeakerText = speakername;
	DialogueText = dialogue;
}

void ADialogueManager::nextLine()
{
	//If a conversation is not happening
	if (!_convoIsHappening)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("NO MORE TEXT TO DISPLAY"));
		return;
	}

	_lineNum++;

	if (_lineNum < _currentConvo->lines.Num())
	{
		//Update text
		updateText(_currentConvo->lines[_lineNum].SpeakerName, _lines[_lineNum]);
	}
	else
	{
		endConversation();
	}
}

void ADialogueManager::endConversation()
{
	if (_currentConvo->branchingConvo)
	{
		startConversation(_currentConvo->branchingConvo);
	}
	else
	{
		_convoIsHappening = false;
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Conversation has ended"));
	}
	
}

