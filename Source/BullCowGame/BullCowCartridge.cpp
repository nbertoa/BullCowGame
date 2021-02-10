// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() {
    Super::BeginPlay();

    InitIsograms();
    InitGame();
}

void UBullCowCartridge::OnInput(const FString& aInput) {
    if (mIsGameOver) {
        ClearScreen();
        InitGame();
    }
    else {
        ProcessUserInput(aInput);
    }
}

void UBullCowCartridge::PrintWelcomeMessage() const {
    PrintLine(TEXT("Welcome to Bull Cow Game!"));
    PrintLine(TEXT("You have %i lives."), 
              mLifeCount);
}

void UBullCowCartridge::AskForGuess() const {
    check(mHiddenWord != nullptr);

    PrintLine(TEXT("Guess the %i letters word"), 
              mHiddenWord->Len());
    PrintLine(TEXT("Press Enter to continue..."));
}

void UBullCowCartridge::ProcessUserInput(const FString& aInput) {
    check(mIsGameOver == false);
    check(mLifeCount > 0);
    check(mHiddenWord != nullptr);

    if (IsIsogram(aInput) == false) {
        PrintLine("The word must be an isogram. Try again...");
        return;
    }

    if (*mHiddenWord == aInput) {
        PrintLine(TEXT("You won!"));
        EndGame();
        return;
    }

    const int32 hiddenWordLength = mHiddenWord->Len();
    if (hiddenWordLength != aInput.Len()) {
        PrintLine(TEXT("The hidden word has a length of %i"), 
                  hiddenWordLength);
        PrintLine(TEXT("Try again..."));
        return;
    }

    uint32 bullCount = 0;
    uint32 cowCount = 0;
    GetBullsAndCows(aInput,
                    bullCount,
                    cowCount);

    --mLifeCount;
    if (mLifeCount > 0) {
        PrintLine(TEXT("Wrong answer!"));
        PrintLine(TEXT("There are %i bulls and %i cows."),
                  bullCount,
                  cowCount);
        PrintLine(TEXT("You have %i lives left. Try again..."), 
                  mLifeCount);
    }
    else {
        PrintLine(TEXT("You lose!"));
        PrintLine(TEXT("The hidden word was %s."), 
                  **mHiddenWord);
        EndGame();
    }

}

void UBullCowCartridge::InitGame() { 
    mHiddenWord = &GetRandomIsogram();
    mLifeCount = static_cast<uint32>(mHiddenWord->Len());
    mIsGameOver = false;

    PrintWelcomeMessage();
    AskForGuess();
}

void UBullCowCartridge::EndGame() {
    mIsGameOver = true;
    PrintLine(TEXT("Press Enter to continue..."));
}

bool UBullCowCartridge::IsIsogram(const FString& aWord) const {
    if (aWord.IsEmpty()) {
        return false;
    }

    for (int32 i = 0; i < aWord.Len() - 1; ++i) {
        for (int32_t j = i + 1; j < aWord.Len(); ++j) {
            if (aWord[i] == aWord[j]) {
                return false;
            }
        }
    }

    return true;
}

void UBullCowCartridge::InitIsograms() {
    check(mIsograms.Num() == 0);

    mIsograms.Emplace(TEXT("pausing"));
    mIsograms.Emplace(TEXT("snail"));
    mIsograms.Emplace(TEXT("mog"));
    mIsograms.Emplace(TEXT("fiasco"));
    mIsograms.Emplace(TEXT("flux"));
    mIsograms.Emplace(TEXT("bathing"));
    mIsograms.Emplace(TEXT("glands"));
    mIsograms.Emplace(TEXT("guest"));
    mIsograms.Emplace(TEXT("bird"));
    mIsograms.Emplace(TEXT("bust"));
    mIsograms.Emplace(TEXT("stunk"));
    mIsograms.Emplace(TEXT("troupe"));
    mIsograms.Emplace(TEXT("blount"));
    mIsograms.Emplace(TEXT("unrest"));
    mIsograms.Emplace(TEXT("herms"));
    mIsograms.Emplace(TEXT("mews"));
    mIsograms.Emplace(TEXT("tamp"));
    mIsograms.Emplace(TEXT("vale"));
    mIsograms.Emplace(TEXT("tyres"));
    mIsograms.Emplace(TEXT("mingle"));
}

const FString& UBullCowCartridge::GetRandomIsogram() const {
    const int32 isogramCount = mIsograms.Num();
    check(isogramCount > 0);

    const int32 index = FMath::RandRange(0, 
                                         isogramCount - 1);
    return mIsograms[index];
}

void UBullCowCartridge::GetBullsAndCows(const FString& aUserWord,
                                        uint32& aBullCount,
                                        uint32& aCowCount) const {
    check(mHiddenWord != nullptr);

    aBullCount = 0;
    aCowCount = 0;

    // If their matching digits (between the user word and the hidden word)
    // are in their right positions, they are "bulls", if in different
    // positions, they are "cows".

    for (int32 i = 0; i < aUserWord.Len(); ++i) {
        // If their matching digits (between the user word and the hidden word)
        // are in their right positions, they are "bulls".
        if (aUserWord[i] == (*mHiddenWord)[i]) {
            ++aBullCount;
            continue;
        }

        // If in different positions, they are "cows".
        for (int32 j = 0; j < mHiddenWord->Len(); ++j) {
            if (aUserWord[i] == (*mHiddenWord)[j]) {
                ++aCowCount;
                break;
            }
        }
    }
}