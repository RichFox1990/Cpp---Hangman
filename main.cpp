#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include "windows.h"
//#include <unistd.h> (for Unux)

using namespace std;

string words[] =
{
	"Terminator",
	"Lord of the rings",
	"Iron Man",
	"Forrest Gump",
	"The Incredible Hulk",
	"The Purge",
	"Red Dragon",
	"Thor",
	"The Avengers",
	"Hannibal",
	"Training Day",
	"The Green Mile",
	"Iron Man",
	"Pitch Perfect",
	"The Matrix",
	"Captain America",
	"Guardians of the Galaxy",
	"Jaws",
	"The Imitation Game",
	"Inception",
	"Avengers: Age of Ultron",
	"Mouse Trap",
	"Matilda",
	"Ant-Man",
	"A Beautiful Mind",
	"Captain America: Civil War",
	"Predator",
	"Kindergarten Cop",
	"Spider-Man Homecoming",
	"Doctor Strange",
	"Rain Man",
	"TopGun",
	"Black Panther",
	"Avengers: Infinity War",
	"Shutter Island",
	"Bill and Teds Bogus Journey",
	"Ant-Man and the Wasp",
	"Captain Marvel",
};

//CONST
const int MAX_GUESSES = 11;

//GLOBAL
int wrongGuessTotal;

string chosenWord;
string chosenLowerCase;
string wordState;

string guessedLetters;
vector<string> guessedWords{};


//FUNCTIONS
string randomWord();
string createLowerCaseAnswer(const string& word);
int handleGuess(const string&);
void displayWordState();
void displayGuessedItems();


int main()
{
	char playAgain = 'y';
	bool firstPlay = true;
	do
	{
		// reset guesses
		wrongGuessTotal = 0;

		// Pull a random word from the "words" array and also generate a encrypted version of the word and apply it to our variables
		chosenWord = randomWord();

		if (firstPlay)
		{
			cout << "|---------------WELCOME TO HANGMAN---------------|\n\n";
			Sleep(1500);
			cout << "Guess letters to reveal their position within the film name.\n\n";
			Sleep(1500);
			cout << "However, be careful. You have a limited number of guesses before you lose.\n\n";
			Sleep(1500);
			cout << "To win, correctly enter the film name before you run out of attempts.\n\nSpaces, ':' and '-' are shown automatically if the hidden word(s) contain them.\n\n";
			Sleep(2500);
			cout << "| ------------------ - LETS BEGIN------------------ - | \n\n\n";
			firstPlay = false;
		}

		guessedLetters.clear();
		guessedWords.clear();

		int gameStatus = 0;
		string guess;
		char quit = 'n';

		while ( gameStatus == 0 )
		{
			// Display board for the current state of the word being guessed
			displayWordState();
			
			Sleep(500);

			// Display already guessed words and letters (if any)
			displayGuessedItems();

			Sleep(400);

			cout << "Enter your letter guess:\n:- ";
			getline(cin, guess);
			cout << endl;

			gameStatus = handleGuess(guess);

			switch (gameStatus)
			{
			case 0:
				// continue guessing
				break;

			case -1:
				// Player ran of guesses
				cout << "You have ran out of guesses.\n\n||--YOU LOSE--||\n\n";
				break;

			case 1:
				// Player guessed the word
				displayWordState();
				cout << " Congratulations - You guessed correctly.\n\n||--YOU WIN--||\n\n";
				break;

			default:
				break;
			}

		}

		Sleep(500);
		cout << "Do you want to play again? (y/n): ";
		cin >> playAgain;
		cout << "\n\n";
		cin.ignore();

	} while (playAgain == 'y');

	return 0;
}



string randomWord()
/* 
Takes 2 string variables passed by reference
1- variable used to store the word the user has to guess
2- variable thats used to display on screen to the user (encrypted version of variable 1) i.e. "***** **** **" 
*/
{
	// work put how many words in the list to choose from
	int numberOfWords = sizeof(words) / sizeof(words[11]);

	// Pick a random word from the "words" array
	srand((unsigned int)time(NULL));
	string word = words[rand() % numberOfWords];

	// copy it the the word variable that the user sees
	wordState = word;

	//encrypt the displayed word - while still displaying spaces and ':' and '-'
	for (int i = 0; i < wordState.length(); i++)
	{
		if (isspace(word[i]))
		{
			wordState[i] = ' ';
		}
		else if ((word[i] == '-') || (word[i] == ':'))
		{
			continue;
		}
		else
		{
			wordState[i] = '_';
		}
	}

	chosenLowerCase = createLowerCaseAnswer(word);

	return word;
}

int handleGuess(const string& guess)
/* Takes the users char "guess" variable and compares it to the word they are trying to guess and edits the guess into
the displayedToUserVariable if the guess was correct. If not it adds 1 to the guess counter.
returns int;-
-1 = lose (out of guesses)
0 = continue playing
1 = Win
*/
{
	// TODO handle non alphabet char as an error
	// bool to handle if the letter guess was correct
	bool correct = false;

	// string variable to store a lowercase guess if the player guesses a word.
	string guessLower;

	// Create a lower case version of the guess to compare against the lower case answer
	for (char c : guess)
		guessLower += tolower(c);

	// if the guess starts with a space then deny the input
	if (guess[0] == ' ') // space
	{
		cout << "You started your guess with a space. Try again\n\n";
		return 0;
	}

	
	// if the guess is more than a single letter = Assume its a word guess and compare against the current secretWord
	if (guess.length() != 1)
	{
		guessedWords.push_back(guess);
		cout << "checking word....\n";
		Sleep(750);
		cout << "...\n\n";
		Sleep(500);
		if (guess.length() == chosenWord.length())
		{
			if (guessLower == chosenLowerCase)
			{
				int i = 0;

				// show the whole word
				for (char c : chosenWord)
				{
					wordState[i] = c;
					i++;
				}
				return 1; // return win
			}
			else
				correct = false;

		}
		else
			correct = false;
		
	}
	else if (guess.length() == 1)
	{
		for (char c : guessedLetters)
		{
			c = tolower(c);
			if (c == guessLower[0])
			{
				cout << "**You have already guessed this letter**\n\n";
				return 0;
			}

			// add letter to the list of guesses
		}

		guessedLetters += toupper(guess[0]);

		for (int i = 0; i < chosenWord.length(); i++)
		{
			if (guessLower[0] == tolower(chosenWord[i]))
			{
				correct = true;
				wordState[i] = chosenWord[i];
			}
		}
	}


	if (!correct)
	{
		wrongGuessTotal += 1;

			if (wrongGuessTotal == MAX_GUESSES)
			{
				return -1; // lose
			}
			else
			{
				cout << "XX-- That guess was incorrect... --XX\n\n";
				return 0; // continue game
			}
	}
	else // is correct
	{
		if (chosenWord == wordState)
		{
			//win
			return 1;
		}

		else
		{
			cout << "<<-- You guessed correctly-->>\n'" << guess << "' was revealed within the word(s).\n\n";
			return 0;
		}
	}
}

string createLowerCaseAnswer(const string& word)
// Create a lowercase version of the answer for comparisson to player guesses
{
	string lower;
	int i = 0;

	for (char c : word)
	{
		lower += tolower(c);
		i++;
	}

	return lower;
}

void displayWordState()
// Display board for the current state of the word being guessed
{
	cout << "||";
	for (int i = 0; i < chosenWord.length() + 2; i++)
		cout << '-';
	cout << "||\n|| ";
	for (int i = 0; i < chosenWord.length(); i++)
		cout << wordState[i];
	cout << " ||\n||";
	for (int i = 0; i < chosenWord.length() + 2; i++)
		cout << '-';
	cout << "||\n\n";
}

void displayGuessedItems()
// Display already guessed words and letters (if any)
{
	if (guessedLetters.length() != NULL)
	{
		cout << "GUESSED LETTERS: ";
		cout << "{ ";
		for (const char c : guessedLetters)
			cout << c << ", ";
		cout << "}\n";

	}
	if (guessedWords.size() != NULL)
	{
		cout << "GUESSED WORDS: ";
		cout << "{ ";
		for (int i = 0; i < guessedWords.size(); i++)
			cout << guessedWords[i] << ", ";
		cout << "}\n\n";
	}
}