#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();

}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return  MyHiddenWord.length();
}

// checks if the guess and the secret isogram match
bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}

// checks wheter length of the guess matches the secret isogram and if the word inputed is an isogram
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{

	if (Guess.length() != GetHiddenWordLength())
	{
		
		return EGuessStatus::Wrong_Length;
	}

	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}

	else if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}

			
	return EGuessStatus::OK;
}


// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount FBullCowCount;
	int32 WordLength = MyHiddenWord.length();	// assumming same length as guess
	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{


			// if they match them
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				// if in the same place 
				if (GChar == MHWChar)
				{
					//	increment bulls if they're in the same place
					FBullCowCount.Bulls++;
				}
				
				// else
				else
				{
					// increment cow if not
					FBullCowCount.Cows++;
				}
				
			}
				
		}


	}

	if (FBullCowCount.Bulls == WordLength)
	{
		bIsGameWon = true;
	}
	else
	{
		bIsGameWon = false;
	}
	return FBullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	TMap<char, bool> LetterSeen;		 // setup our map
	for (auto Letter : Guess)			// for each letter in guess
	{
		Letter = tolower(Letter);		// converts upper case to lower case
		// compare guess against map
		if (LetterSeen[Letter]){		// if true, then we've already had the letter on the map, so it's repeated on the guess and it's not an isogram
			return false;	
		}
		else{				// if not, add the letter to our map
			LetterSeen[Letter] = true;	// add the letter
		}
	}
		
	return true;
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (islower(Letter))
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

// Maybe implement it later


//void FBullCowGame::Surrender(FString SecretIsogram)
//{
//}
