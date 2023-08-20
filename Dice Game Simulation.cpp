// Dice Game Simulation

// preprocessor directives
// library includes
#include <iostream>     // standard input and output
#include <string>       // string methods
#include <iomanip>      // manipulators for formatting output
#include <cstdlib>      // contains random number generator
#include <ctime>        // allows using the system clock for a seed

// set namespace
using namespace std;


/// -------------------------------------------------------------------------
/// Function Prototype(s)
/// -------------------------------------------------------------------------
int  rndInt(int a, int b);
int  getPosInt(const string& prompt);
void printReport(const int totalGames,
                 const int playerWinCount, const int playerWinnings,
                 const int houseWinCount, const int houseWinnings);

/// -------------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -------------------------------------------------------------------------
int main() {
    // Local constant definition(s)

    // Variable declaration(s)
    int exitState;              // tracks the exit code for the process
    exitState = EXIT_SUCCESS;   // set state to successful run

    int bet = 0;                    // tracks player bet
    int totalGames = 0;             // tracks total games played
    int playerWinnings = 0;         // tracks player winnings
    int playerWinCount = 0;         // increments when the player wins
    int houseWinnings  = 0;         // tracks house winnings
    int houseWinCount  = 0;         // increments when the house wins
    int die1;                       // one of two playing dice
    int die2;                       // two of two playing dice
    int dieTotal;                   // total dice value rolled
    int subTotal;                   // holds temp win value for output
    char replay = 'n';              // answer to play again

    // set the random number seed
    // srand(static_cast<unsigned int>(time(nullptr)));
    srand(42);

    do {
        /* ******* Input Phase ******************************************* */
        bet = getPosInt("Enter a bet in integer dollars: ");

        /* ******* Processing Phase ************************************** */
        if (bet > 0) {
            cout << "The bet is: " << bet << endl;
            totalGames++;
            die1 = rndInt(1, 6);
            die2 = rndInt(1, 6);
            dieTotal = die1 + die2;

            cout << "Roll = " << die1
            << " and " << die2
            << " totaling " << dieTotal << endl;

            // game logic 7, 11: player win
            if (dieTotal == 7 || dieTotal == 11) {
                playerWinCount++;
                subTotal = 2 * bet;
                playerWinnings += subTotal;
                cout << "Player Wins $" << subTotal << "!\n\n";

                // pairs 2, 4, and 5: player win
            } else if ((die1 == 2 || die1 == 4 || die1 == 5) && die1 == die2) {
                playerWinCount++;
                subTotal = static_cast<int>(1.5 * bet);
                playerWinnings += subTotal;
                cout << "Player Wins $" << subTotal << "!\n\n";

                // pairs 1, 3 or 6: house win
            } else if ((die1 == 1 || die1 == 3 || die1 == 6) && die1 == die2) {
                houseWinCount++;
                houseWinnings += bet;
                cout << "House Wins!\n\n";

                // totals 3, 5, 9: house win
            } else if (dieTotal == 3 || dieTotal == 5 || dieTotal == 9) {
                houseWinCount++;
                houseWinnings += bet;
                cout << "House Wins!\n\n";

                // otherwise no one wins
            } else {
                cout << "No Winner!\n\n";
            }
        } else {
            // input was not valid. message user.
            cout << "\nInvalid input, session over.\n\n";
        }
        cout << "Do you want to play again Y/N? ";
        cin >> replay;

        // clear the stream in case user types in more than one char.
        cin.ignore(255, '\n');

    } while (static_cast<char>(tolower(replay)) == 'y');

    if (totalGames > 0) {
        cout << "\nGame over. Thanks for playing!\n\n";
        printReport(totalGames, playerWinCount, playerWinnings,
                    houseWinCount, houseWinnings);
    }


    return exitState;
}

/// -------------------------------------------------------------------------
/// Function Implementation(s)
/// -------------------------------------------------------------------------

/// This function returns a positive integer
/// @param prompt is a prompt to the user.
int getPosInt(const string& prompt) {
    int value = 0;              // user bet
    int attempts = 3;           // attempt counter
    bool valid_input = false;   // LCV flag for valid input

    while (attempts > 0 && !valid_input) {
        attempts--;         // decrement attempts count
                            // prompt user for integer input
        cout << prompt;
        cin >> value;

        // validate input - clear stream if invalid
        if (cin.fail() || value < 1) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Error... " << attempts << " attempt(s) left!\n" << endl;
        } else {
            valid_input = true;
        }
    }

    // if the input is valid, return the value, otherwise -1
    return valid_input ? value : -1;
}


/// This function returns a random number between a and b
/// @param a is one limiting number
/// @param b is a second limiting number
/// @return a random number between a and b
int rndInt(int a, int b) {
    int temp;       // used to sort the parameters
    int rndVal;     // holds rand value

    // if the range values are the same, return the value
    if (a == b) {
        rndVal = a;
    } else {
        // sort the values
        if (a > b) {
            temp = a;
            a = b;
            b = temp;
        }

        // generate the random number
        // requires <cstdlib>
        rndVal = rand() % b + a;
    }

    return rndVal;
}


/// This function prints the game statistics
/// @param totalGames number of games played
/// @param playerWinCount number of times the player won
/// @param playerWinnings money the player won
/// @param houseWinCount number of times the house won
/// @param houseWinnings money lost to the house
void printReport(const int totalGames,
                 const int playerWinCount, const int playerWinnings,
                 const int houseWinCount, const int houseWinnings) {
    const int COL1 = 5;
    const int COL2 = 33;

    cout << "Game Stats" << endl;
    cout << string(40, '-') << endl;
    cout << right << setw(COL2) << "Total Games: "
    << right << setw(COL1) << totalGames << endl;
    cout << right << setw(COL2) << "Number of times the player won: "
    << right << setw(COL1) << playerWinCount << endl;
    cout << right << setw(COL2) << "Player Winnings: "
    << right << setw(COL1) << playerWinnings << endl;
    cout << right << setw(COL2) << "Number of times the house won: "
    << right << setw(COL1) << houseWinCount << endl;
    cout << right << setw(COL2) << "House Winnings: "
    << right << setw(COL1) << houseWinnings << endl;
    cout << endl;

}