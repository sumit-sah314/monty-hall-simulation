#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

int getUserChoice() {
    int choice;
    while (true) {
        cout << "Pick a door (1, 2, or 3): ";
        cin >> choice;
        if (choice >= 1 && choice <= 3) break;
        cout << "Invalid input. Please choose 1, 2, or 3.\n";
    }
    return choice - 1; // Convert to 0-based index
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

void displayDoors(int userChoice, int hostOpens, bool revealAll = false, int prizeDoor = -1) {
    cout << "\nDoors:\n";
    for (int i = 0; i < 3; ++i) {
        cout << "[" << (i + 1) << "] ";
        if (revealAll) {
            if (i == prizeDoor)
                cout << "(C) "; // Car
            else
                cout << "(G) "; // Goat
        } else if (i == hostOpens) {
            cout << "(G) "; // Host revealed goat
        } else {
            cout << "[ ] "; // Closed door
        }
    }
    cout << "\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    cout << "=== Welcome to the Monty Hall Game Show! ===\n\n";

    bool playAgain = true;

    // Tracking variables
    int gamesPlayed = 0;
    int switchWins = 0;
    int switchLosses = 0;
    int stayWins = 0;
    int stayLosses = 0;

    while (playAgain) {
        int prizeDoor = rand() % 3;
        int userChoice = getUserChoice();

        cout << "\nHere are the doors before Monty opens one:\n";
        displayDoors(-1, -1);

        // Host opens a door that is not the user's choice or the prize door
        int hostOpens;
        do {
            hostOpens = rand() % 3;
        } while (hostOpens == prizeDoor || hostOpens == userChoice);

        cout << "\nMonty opens door " << (hostOpens + 1) << " and reveals a goat.\n";
        displayDoors(-1, hostOpens);

        bool switchChoice = getYesOrNo("Do you want to switch your choice?");
        if (switchChoice) {
            for (int i = 0; i < 3; ++i) {
                if (i != userChoice && i != hostOpens) {
                    userChoice = i;
                    break;
                }
            }
        }

        cout << "\nYour final choice is door " << (userChoice + 1) << ".\n";
        displayDoors(userChoice, hostOpens, true, prizeDoor);

        if (userChoice == prizeDoor) {
            cout << ":) Congratulations! You won a CAR!\n";
            if (switchChoice) {
                switchWins++;
            } else {
                stayWins++;
            }
        } else {
            cout << ":( Sorry, you got a goat. The car was behind door " << (prizeDoor + 1) << ".\n";
            if (switchChoice) {
                switchLosses++;
            } else {
                stayLosses++;
            }
        }

        gamesPlayed++;
        playAgain = getYesOrNo("\nDo you want to play again?");
        cout << "--------------------------------------\n\n";
    }

    // Summary Report
    cout << "\n=== Game Summary ===\n";
    cout << "Total games played: " << gamesPlayed << "\n";
    cout << "Switched and won: " << switchWins << "\n";
    cout << "Switched and lost: " << switchLosses << "\n";
    cout << "Stayed and won: " << stayWins << "\n";
    cout << "Stayed and lost: " << stayLosses << "\n";

    if ((switchWins + switchLosses) > 0) {
        cout << "Switch Win Rate: " << (switchWins * 100.0 / (switchWins + switchLosses)) << "%\n";
    } else {
        cout << "Switch Win Rate: N/A\n";
    }
    if ((stayWins + stayLosses) > 0) {
        cout << "Stay Win Rate: " << (stayWins * 100.0 / (stayWins + stayLosses)) << "%\n";
    } else {
        cout << "Stay Win Rate: N/A\n";
    }
    cout << "====================\n";

    cout << "Thanks for playing the Monty Hall Game. Goodbye!\n";
    return 0;
}
