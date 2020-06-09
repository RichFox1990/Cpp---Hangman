#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

string words[] =
{
	"Terminator",
	"Lord of the rings",
	"Captain America: The First Avenger",
	"Iron Man",
	"The Incredible Hulk",
	"Iron Man 2",
	"Thor",
	"The Avengers",
	"Iron Man 3",
	"Thor The Dark World",
	"Captain America: The Winter Soldier",
	"Guardians of the Galaxy",
	"Avengers: Age of Ultron",
	"Ant-Man",
	"Captain America: Civil War",
	"Spider-Man Homecoming",
	"Doctor Strange",
	"Thor: Ragnarok",
	"Black Panther",
	"Avengers: Infinity War",
	"Ant-Man and the Wasp",
	"Captain Marvel",
};

//CONST
const int MAX_GUESSES = 11;

//GLOBAL
int guesses;

//FUNCTIONS
void randomWord(string&, string&);
int handleGuess(const char, string&, const string&, string&);


int main()
{

	char playAgain = 'y';

	string currentWord, displayedWord;

	do
	{
		// reset guesses
		guesses = 0;

		// Pull a random word from the "words" array and also generate a encrypted version of the word and apply it to our variables
		randomWord(currentWord, displayedWord);

		cout << "|---------------WELCOME TO HANGMAN---------------|\n\nGuess letters to reveal their position within the film name.\n\nHowever, be careful. You have a limited number of guesses before you lose.\n\nTo win, correctly enter the film name before you run out of attempts.\n\nSpaces, ':' and '-' are shown automatically if the hidden word(s) contain them.\n\n|-------------------LETS BEGIN-------------------|\n\n\n";

		int gameStatus = 0;
		char guess;
		string allGuesses;
		char quit = 'n';

		while ( gameStatus == 0 )
		{
			// Display board for the current state of the word being guessed
			cout << "||";
			for (int i = 0; i < displayedWord.length()+2; i++)
				cout << '-';
			cout << "||\n|| ";
			for (int i = 0; i < displayedWord.length(); i++)
				cout << displayedWord[i];
			cout << " ||\n||";
			for (int i = 0; i < displayedWord.length()+2; i++)
				cout << '-';
			cout << "||\n\n";

			if (allGuesses.length() != NULL)
			{
				cout << "GUESSED LETTERS: ";
				cout << "{ ";
				for (const char c : allGuesses)
					cout << c << ", ";
				cout << "}\n\n";
			}


			cout << "Enter your letter guess:\n:- ";
			cin >> guess;
			cout << endl;

			gameStatus = handleGuess(guess, allGuesses, currentWord, displayedWord);

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
				cout << " Congratulations - You guessed correctly.\n\n||--YOU WIN--||\n\n";
				break;

			default:
				break;
			}

		}

		cout << "Do you want to play again? (y/n): ";
		cin >> playAgain;

	} while (playAgain == 'y');

	return 0;
}



void randomWord(string& secretWordVariable, string& displayedToUserVariable)
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
	secretWordVariable = words[rand() % numberOfWords];

	// copy it the the displayed word
	displayedToUserVariable = secretWordVariable;

	//encrypt the displayed word - while still displaying spaces and ':' and '-'
	for (int i = 0; i < secretWordVariable.length(); i++)
	{
		if (isspace(secretWordVariable[i]))
		{
			displayedToUserVariable[i] = ' ';
		}
		else if ((secretWordVariable[i] == '-') || (secretWordVariable[i] == ':'))
		{
			continue;
		}
		else
		{
			displayedToUserVariable[i] = '*';
		}
	}
}

int handleGuess(const char guess, string& previousGuesses, const string& secretWordVariable, string& displayedToUserVariable)
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

	for (const char c : previousGuesses)
	{
		if (c == guess)
		{
			cout << "**You have already guessed this letter**\n\n";
			return 0;
		}
	}

	previousGuesses += guess;

	for (int i = 0; i < secretWordVariable.length(); i++)
	{
		if (guess == tolower(secretWordVariable[i]))
		{
			correct = true;
			displayedToUserVariable[i] = secretWordVariable[i];
		}
	}

	if (!correct)
	{

		guesses += 1;
			if (guesses == MAX_GUESSES)
			{
				return -1; // lose
			}
			else
			{
				cout << "XX-- That guess was incorrect... --XX\n\n";
				return 0; // continue game
			}
	}

	// code will only execute further if the guess was correct - therefore no need for an else

	if (secretWordVariable == displayedToUserVariable)
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