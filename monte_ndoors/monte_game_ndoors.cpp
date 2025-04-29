#include <iostream>
#include <vector>
#include <algorithm> // For random_shuffle
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

int getUserChoice(int numberOfDoors) {
    int choice;
    while (true) {
        cout << "Pick a door (1 to " << numberOfDoors << "): ";
        cin >> choice;
        if (choice >= 1 && choice <= numberOfDoors) break;
        cout << "Invalid input. Please choose between 1 and " << numberOfDoors << ".\n";
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

void displayDoors(int numberOfDoors, const vector<int>& openedDoors, bool revealAll = false, int prizeDoor = -1) {
    cout << "\nDoors:\n";
    for (int i = 0; i < numberOfDoors; ++i) {
        cout << "[" << (i + 1) << "] ";
        bool isOpened = find(openedDoors.begin(), openedDoors.end(), i) != openedDoors.end();
        if (revealAll) {
            if (i == prizeDoor)
                cout << "(C) ";
            else
                cout << "(G) ";
        } else if (isOpened) {
            cout << "(G) ";
        } else {
            cout << "[ ] ";
        }
    }
    cout << "\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    cout << "=== Welcome to the Monty Hall Game Show! ===\n\n";

    int numberOfDoors;
    cout << "Enter number of doors (minimum 3): ";
    cin >> numberOfDoors;
    if (numberOfDoors < 3) numberOfDoors = 3;

    bool playAgain = true;

    // Tracking variables
    int gamesPlayed = 0;
    int switchWins = 0;
    int switchLosses = 0;
    int stayWins = 0;
    int stayLosses = 0;

    while (playAgain) {
        int prizeDoor = rand() % numberOfDoors;
        int userChoice = getUserChoice(numberOfDoors);

        cout << "\nHere are the doors before Monty opens any:\n";
        displayDoors(numberOfDoors, {});

        // Step 1: Build list of doors Monty can open (not user choice, not prize)
        vector<int> openableGoatDoors;
        for (int i = 0; i < numberOfDoors; ++i) {
            if (i != userChoice && i != prizeDoor) {
                openableGoatDoors.push_back(i);
            }
        }

        // Step 2: Shuffle and pick (numberOfDoors - 2) doors to open
        random_shuffle(openableGoatDoors.begin(), openableGoatDoors.end());

        vector<int> montyOpens;
        for (int i = 0; i < numberOfDoors - 2; ++i) {
            montyOpens.push_back(openableGoatDoors[i]);
        }

        // Step 3: Display which doors Monty opens
        cout << "\nMonty opens " << montyOpens.size() << " doors and reveals goats:\n";
        for (int door : montyOpens) {
            cout << "Door " << (door + 1) << " has a goat.\n";
        }
        cout << "\n";

        displayDoors(numberOfDoors, montyOpens);

        // Step 4: Build list of unopened doors
        vector<int> unopenedDoors;
        for (int i = 0; i < numberOfDoors; ++i) {
            if (find(montyOpens.begin(), montyOpens.end(), i) == montyOpens.end()) {
                unopenedDoors.push_back(i);
            }
        }

        // Step 5: Ask if user wants to switch
        bool switchChoice = getYesOrNo("Do you want to switch your choice?");
        if (switchChoice) {
            for (int door : unopenedDoors) {
                if (door != userChoice) {
                    userChoice = door;
                    break;
                }
            }
        }

        cout << "\nYour final choice is door " << (userChoice + 1) << ".\n";
        displayDoors(numberOfDoors, {}, true, prizeDoor);

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
