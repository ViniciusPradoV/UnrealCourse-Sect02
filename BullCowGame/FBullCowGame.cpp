#include "FBullCowGame.h"

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
	FString GuessClone = Guess;							// Guess clone for character comparison

	if (Guess.length() != GetHiddenWordLength())
	{
		
		return EGuessStatus::Wrong_Length;
	}

	
	for (int32 GClChar = 0; GClChar < GetHiddenWordLength(); GClChar++)
	{
		for (int32 GChar = 0; GChar < GetHiddenWordLength(); GChar++)
		{
			if (GChar == GClChar)									// if positions are the same, ignore the comparison
			{
				continue;
			}

			else if (Guess[GChar] == GuessClone[GClChar])				// compare each guess letter with whole guess word, if letters repeat, guess is invalid
			{
				
				return EGuessStatus::Not_Isogram;
			}
		}
		
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

// Maybe implement it later


//void FBullCowGame::Surrender(FString SecretIsogram)
//{
//}
