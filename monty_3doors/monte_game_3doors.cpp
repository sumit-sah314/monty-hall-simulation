/*
   ============================
       MONTY HALL - 3 DOORS
   ============================

        [1]     [2]     [3]
      +-----+ +-----+ +-----+
      | ??? | | ??? | | ??? |
      +-----+ +-----+ +-----+

    - One door hides a CAR 🚗
    - The other two hide GOATS 🐐

    Game Flow:
    -------------------------------
    1. Player picks a door
    2. Monty opens a GOAT door
    3. Player decides to switch
    4. Reveal prize and update stats
    -------------------------------

    Probabilities:
    - Stay:    1/3 (33.3%)
    - Switch:  2/3 (66.6%)
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

int getUserChoice() {
    int choice;
    while (true) {
        cout << "\nPick a door (1, 2, or 3): ";
        cin >> choice;
        if (choice >= 1 && choice <= 3) break;
        cout << "Invalid input. Please choose 1, 2, or 3.\n";
    }
    return choice - 1; // convert to 0-based index
}

bool getYesOrNo(const string& prompt) {
    char input;
    while (true) {
        cout << prompt << " (y/n): ";
        cin >> input;
        input = tolower(input);
        if (input == 'y') return true;
        if (input == 'n') return false;
        cout << "Please enter 'y' or 'n'.\n";
    }
}

void displayDoors(int highlight = -1, int openedGoat = -1, int car = -1, bool finalReveal = false) {
    cout << "\n";
    cout << "        [1]     [2]     [3]\n";
    cout << "      +-----+ +-----+ +-----+\n";
    cout << "      |";

    for (int i = 0; i < 3; ++i) {
        if(i !=0){
            cout<<" |";
        }
        if (finalReveal) {
            if (i == car) cout << "CAR ";
            else cout << "GOAT";
        } else if (i == openedGoat) {
            cout << "GOAT";
        } else if (i == highlight) {
            cout << " ???";
        } else {
            cout << " ???";
        }
        cout << " |";
    }

    cout << "\n      +-----+ +-----+ +-----+\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    cout << R"(
   ============================
       MONTY HALL - 3 DOORS
   ============================

        [1]     [2]     [3]
      +-----+ +-----+ +-----+
      | ??? | | ??? | | ??? |
      +-----+ +-----+ +-----+

    - One door hides a CAR 
    - The other two hide GOATS 
    )" << endl;

    bool playAgain = true;
    int gamesPlayed = 0;
    int switchWins = 0, switchLosses = 0, stayWins = 0, stayLosses = 0;

    while (playAgain) {

        int prizeDoor = rand() % 3;
        int userChoice = getUserChoice();

        // Monty reveals a goat that's not the prize or user's choice
        int hostOpens;
        do {
            hostOpens = rand() % 3;
        } while (hostOpens == prizeDoor || hostOpens == userChoice);

        cout << "\nMonty opens door " << (hostOpens + 1) << " and reveals a goat:\n";
        displayDoors(userChoice, hostOpens);

        bool switchChoice = getYesOrNo("Do you want to switch your choice?");
        if (switchChoice) {
            for (int i = 0; i < 3; ++i) {
                if (i != userChoice && i != hostOpens) {
                    userChoice = i;
                    break;
                }
            }
        }

        cout << "\nFinal reveal:\n";
        displayDoors(userChoice, hostOpens, prizeDoor, true);

        if (userChoice == prizeDoor) {
            cout << "\n:) You WON the car!\n";
            if (switchChoice) switchWins++; else stayWins++;
        } else {
            cout << "\n:( You got a goat. The car was behind door " << (prizeDoor + 1) << ".\n";
            if (switchChoice) switchLosses++; else stayLosses++;
        }

        gamesPlayed++;
        playAgain = getYesOrNo("\nDo you want to play again?");
    }

    // Summary
    cout << "\n=== Game Summary ===\n";
    cout << "Total games played: " << gamesPlayed << "\n";
    cout << "Switched and won: " << switchWins << "\n";
    cout << "Switched and lost: " << switchLosses << "\n";
    cout << "Stayed and won: " << stayWins << "\n";
    cout << "Stayed and lost: " << stayLosses << "\n";

    return 0;
}
