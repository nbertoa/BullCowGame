// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void OnInput(const FString& aInput) override;

private:
	void PrintWelcomeMessage() const;
	void AskForGuess() const;
	void ProcessUserInput(const FString& aInput);
	void InitGame();
	void EndGame();
	bool IsIsogram(const FString& aWord) const;
	void InitIsograms();
	const FString& GetRandomIsogram() const;

	// If their matching digits (between the user word and the hidden word)
	// are in their right positions, they are "bulls", if in different
	// positions, they are "cows".
	void GetBullsAndCows(const FString& aUserWord,
						 uint32& aBullCount,
						 uint32& aCowCount) const;

	TArray<FString> mIsograms;
	const FString* mHiddenWord = nullptr;
	uint32 mLifeCount = 0;
	bool mIsGameOver = false;
};
