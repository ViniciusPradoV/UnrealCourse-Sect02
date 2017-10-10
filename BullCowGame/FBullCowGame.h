#pragma once

#include <string>
#include <iostream>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};

enum class EResetStatus
{
	OK,
	No_Hidden_Word,
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor


	int32 GetMaxTries() const;											// Max tries based on length of the word
	int32 GetCurrentTry() const;										// Gets the current user guess
	int32 GetHiddenWordLength() const;									// Gets the hidden word length
	bool IsGameWon() const;												// Determines if the guess is the correct one
	EGuessStatus CheckGuessValidity(FString Guess);						// Determines if input guess is an isogram and has the word length asked or an invalid word thus not discounting the number of max tries

	void Reset();														// TODO make a more rich return value.
	FBullCowCount SubmitValidGuess(FString);






	// Maybe implement it later
	//void Surrender(FString SecretIsogram);							// Forfeits the current game and show the secret isogram
private:
	// see constructor for initialization
	int32 MyCurrentTry;
	int32  MyMaxTries;
	FString  MyHiddenWord;
	bool bIsGameWon;

	bool IsIsogram(FString Guess) const;
	bool IsLowerCase(FString Guess) const;
};