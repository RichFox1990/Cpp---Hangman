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

const int MAX_GUESSES = 12;

void randomWord(string&, string&);


int main() {
	cout << "my directory is " << ExePath() << "\n";
}

int main()
{

	char playAgain = 'y';

	string currentWord, displayedWord;

	int guesses;

	do
	{
		// reset guesses
		guesses = 0;

		// Pull a random word from the "words" array and also generate a encrypted version of the word and apply it to our variables
		randomWord(currentWord, displayedWord);

		cout << "|---------------WELCOME TO HANGMAN---------------|\n\nGuess letters to reveal their position within the film name.\n\nHowever, be careful. You have a limited number of guesses before you lose.\n\nTo win, correctly enter the film name before you run out of attempts.\n\n|-------------------LETS BEGIN-------------------|\n\n";





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