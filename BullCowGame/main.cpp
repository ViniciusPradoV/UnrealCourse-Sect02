/*This is the console executable that makes use of the BullCow class
This acts as the view in the MVC pattern, and is responsbile for all
user interaction or game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

// methods created
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

// classes
FBullCowGame BCGame;			// instantiate a new game

// entry point for the application
int main() 
{
	// introducing the game
	PrintIntro();	
	// plays the game
	do
	{
		PlayGame();
		BCGame.Reset();

	} while (AskToPlayAgain());
	

	return 0; // exit the application
}

void PlayGame()
{
	FString Guess = "";
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		// get valid the guess
		Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount FBullCowCount = BCGame.SubmitValidGuess(Guess);
		//print number of bulls and cows
		std::cout << "Bulls: " << FBullCowCount.Bulls << std::endl;
		std::cout << "Cows: " << FBullCowCount.Cows << std::endl;
		std::cout << std::endl;

	}
	PrintGameSummary();
}

void PrintIntro() 
{
	// introduce the game
	std::cout << "Welcome to Bulls and Cows, the word guessing game!\n\n" << std::endl;
	std::cout << "How it works?\n";
	std::cout << "This game challenges you to guess the secret isogram given a chosen ammount of guesses.\n";
	std::cout << "Each attempted guess is followed by a number of 'Bulls' and 'Cows'.\n\n";
	std::cout << "Each 'Bull' means that you've got a CORRECT letter on a CORRECT place for the last guess\n attempt in relation to the secret isogram.\n\n";
	std::cout << "Each 'Cow' means you've got a CORRECT letter on a WRONG place for the last guess attempt\n in relation to the secret isogram.\n\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";


	return;
}

FText GetValidGuess()
{
	// get a guess from the player 
	FText Guess = "";
	EGuessStatus GuessEvaluation = EGuessStatus::Not_Isogram;
	do
	{

		int32 MaxTries = BCGame.GetMaxTries();
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Max tries: " << MaxTries << "\n";
		std::cout << "Try " << CurrentTry << ".";
		std::cout << "Make a guess !\n";
		std::getline(std::cin, Guess);
		GuessEvaluation = BCGame.CheckGuessValidity(Guess);
			switch (GuessEvaluation)
			{
			case EGuessStatus::Wrong_Length:
				std::cout << "Your input is invalid! Word size does not match secret isogram size, please, try again!\n";
				break;

			case EGuessStatus::Not_Lowercase:
				std::cout << "Your input is invalid! The word has uppercase letters, try typing your guess with lowercase letters only\n";
				break;

			case EGuessStatus::Not_Isogram:
				std::cout << "Your input is invalid! The word is not an isogram! Try a word that doesn't have repeated letters\n";
				break;


			default:
				break;
			}
		} while (GuessEvaluation != EGuessStatus::OK);

		return Guess;
}

bool AskToPlayAgain()
{
	FText RetryAns = "";
	std::cout << "Do you want to play again (Y/N)? \n";
	// get the retry question answer
	std::getline(std::cin, RetryAns);
	// determine whether the answer is negative or positive
	if ((RetryAns[0] != 'Y') &&
		(RetryAns[0] != 'y') &&
		(RetryAns[0] != 'N') &&
		(RetryAns[0] != 'n'))
	{

		std::cout << "Your input is invalid! Try upper or lower case 'Y' or 'N' for your answer \n ";
		return AskToPlayAgain();
		
		
	}
	else 
	{
		return (RetryAns[0] == 'Y' ||
			RetryAns[0] == 'y');
	}
	
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You've won the game!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}