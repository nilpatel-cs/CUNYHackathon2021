// Collaborative Effort of Lloyd Empedrado, Nathan Murdach, Nil Patel, Shoya Dixon
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

// reset game state
void newGame();
// game logic
void game();
// print hangman
void hangman(int i);
// print on win and lose
void gameover(int i);
// give user a hint if they get nothing
void hint();
//give user a hint towards end
void mercyHint();
// check for numerical entry
bool isNumeric(string s);

// save wrong guesses to print for player
string pastGuesses;
// to check if win by guessing characters
int correct;
// array to hold words
string words[270];
// hold randomly picked word
string word;
// underscores
string blank;
// highscore
int score = 0;

int main()
{
    // text file to word array
    using namespace std;
    ifstream file;
    file.open("words.txt");
    for (int i = 0; i < 270; i++)
    {
        file >> words[i];
    }

    // prompt user to enter something to start
    string entry;
    cout << "Enter anything when ready to start: " << endl;
    cin >> entry;
    newGame();
}

// restarts the game
void newGame()
{
    // randomly pick word from array
    srand(time(0));
    word = words[rand() % 270];
    // create a string of "_ " = to the length of the random word
    blank = "";
    for (int i = 0; i < word.size(); i++)
        blank += "_ ";
    // start game state
    game();
    return;
}

// game state
void game()
{
    // initialize correct to zero, pastGuesses to an empty string and life to 0.
    correct = 0;
    pastGuesses = "";
    string guess;
    int life = 0;

    // keep looping until all chances taken
    while (life < 6)
    {
        // print hangman
        hangman(life);
        // get user input
        cout << "Your guess is: ";
        cin >> guess;
        // capitalize user input - Ping was here
        for (int i = 0; i < guess.length(); i++) guess[i] = tolower(guess[i]);
        // check to make sure no numbers
        if (isNumeric(guess))
        {
            cout << "Don't enter numbers" << endl;
        }
        // if more than one character input
        else if (guess.size() > 1)
        {
            // reject if wrong size
            if (guess.size() != word.size())
            {
                cout << "Wrong length, try again." << endl;
            }
            // if right size check match
            else if (guess != word)
            {
                cout << "That's the wrong word!" << endl;
                score -= 10;
                life++;
            }
            // player guessed correctly
            else
            {
                score += 20 * (word.size() - correct);
                blank = word;
                hangman(life);
                gameover(1);
            }
        }
        // check if character already guessed
        else if (pastGuesses.find(guess) != -1)
        {
            cout << "You already guessed this incorrect character" << endl;
        }
        // check if character in word
        else if (word.find(guess) == -1)
        {
            cout << "You guessed the wrong character!" << endl;
            score -= 5;
            life++;
            pastGuesses += guess[0];
        }
        // check to see if already shown  
        else if (blank.find(guess) != -1)
        {
            cout << "You already guessed this correctly" << endl;
        }
        // if user guesses the right letter and it wasn't already guess 
        else
        {
            cout << "You guessed a correct character" << endl;
            char c = guess[0];
            blank[word.find(c) * 2] = c;
            correct += 1;
            score += 10;
            // look to see if character appears multiple times and reveal all occurences
            for (int i = word.find(guess) + 1; i < word.size(); i++)
            {
                if (word[i] == c)
                {
                    blank[i * 2] = c;
                    correct += 1;
                    score += 10;
                }
            }
            // if correct guesses is the same as the word length player guessed whole word
            if (correct == word.size())
            {
                blank = word;
                hangman(life);
                gameover(1);
            }
        }
    }

    // ran out of lives 
    blank = word;
    hangman(life);
    gameover(0);
}

// print hangman based on chances used
void hangman(int i)
{
    switch (i)
    {
    case 0:
        cout << "Word: " << blank << endl;
        cout << " ___________" << endl;
        cout << "|  _________|\tScore: " << score << endl;
        cout << "| |      |" << endl;
        cout << "| |      |" << endl;
        cout << "| |" << endl;
        cout << "| |" << endl;
        cout << "| |" << endl;
        cout << "| |" << endl;
        break;
    case 1:
        cout << "Word: " << blank << " Wrong guesses: " << pastGuesses << endl;
        cout << " ___________" << endl;
        cout << "|  _________|\tScore: " << score << endl;
        cout << "| |      |" << endl;
        cout << "| |      |" << endl;
        cout << "| |      O" << endl;
        cout << "| |    " << endl;
        cout << "| |    " << endl;
        cout << "| |" << endl;
        break;
    case 2:
        if (correct == 0 && word.size() > 4)
        {
            cout << "Here is a hint" << endl;
            hint();
        }
        cout << "Word: " << blank << "  Wrong guesses: " << pastGuesses << endl;
        cout << " ___________" << endl;
        cout << "|  _________|\tScore: " << score << endl;
        cout << "| |      |" << endl;
        cout << "| |      |" << endl;
        cout << "| |      O" << endl;
        cout << "| |      | " << endl;
        cout << "| |     " << endl;
        cout << "| |" << endl;
        break;
    case 3:
        if (correct == 0)
        {
            cout << "Here is a hint" << endl;
            hint();
        }
        cout << "Word: " << blank << "  Wrong guesses: " << pastGuesses << endl;
        cout << " ___________" << endl;
        cout << "|  _________|\tScore: " << score << endl;
        cout << "| |      |" << endl;
        cout << "| |      |" << endl;
        cout << "| |      O" << endl;
        cout << "| |     /|" << endl;
        cout << "| |     " << endl;
        cout << "| |" << endl;
        break;
    case 4:
        cout << "Word: " << blank << "  Wrong guesses: " << pastGuesses << endl;
        cout << " ___________" << endl;
        cout << "|  _________|\tScore: " << score << endl;
        cout << "| |      |" << endl;
        cout << "| |      |" << endl;
        cout << "| |      O" << endl;
        cout << "| |     /|\\ " << endl;
        cout << "| |     " << endl;
        cout << "| |" << endl;
        break;
    case 5:
        if (word.size() - correct >= 4)
        {
            cout << "Wow you really need help!" << endl;
            mercyHint();
        }
        cout << "Word: " << blank << "  Wrong guesses: " << pastGuesses << endl;
        cout << " ___________" << endl;
        cout << "|  _________|\tScore: " << score << endl;
        cout << "| |      |" << endl;
        cout << "| |      |" << endl;
        cout << "| |      O" << endl;
        cout << "| |     /|\\ " << endl;
        cout << "| |     /  " << endl;
        cout << "| |" << endl;
        break;
    case 6:
        cout << "Word: " << blank << "  Wrong guesses: " << pastGuesses << endl;
        cout << " ___________" << endl;
        cout << "|  _________|\tScore: " << score << endl;
        cout << "| |      |" << endl;
        cout << "| |      |" << endl;
        cout << "| |      O" << endl;
        cout << "| |     /|\\ " << endl;
        cout << "| |     / \\ " << endl;
        cout << "| |" << endl;
        break;
    }
}

// reveal first character and every character that is the same
void hint()
{
    char c = word[0];
    blank[0] = c;
    correct = 1;
    for (int i = 1; i < word.size(); i++)
    {
        if (word[i] == c)
        {
            blank[i * 2] = c;
            correct += 1;
        }
    }
}

// reveal first missing character and every character that is the same
void mercyHint()
{
    // find first unrevealed characters
    int i = blank.find('_');
    char c = word[i / 2];
    blank[i] = c;
    correct += 1;
    for (i = i + 1; i < word.size(); i++)
    {
        if (word[i] == c)
        {
            blank[i * 2] = c;
            correct += 1;
        }
    }
}

// check for digits
bool isNumeric(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]))
            return true; // when digit found, return false
    return false;
}


// print on loss or win
void gameover(int i)
{
    if (i == 1) cout << "You Got it!!" << endl;
    else
    {
        cout << "You killed him, you did this!" << endl;
        score -= 50;
    }

    // prompt the user for an input if its 1, restart and go to start menu, if anything else, quit
    string entry;
    cout << "Enter 1 to restart. Enter anything else to quit.\nYour current score is: " << score << endl;
    cin >> entry;
    if (entry == "1")
    {
        newGame();
    }
    else
        exit(0);
}