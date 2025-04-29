/*
   ============================
       MONTY HALL - n DOORS
   ============================

   [1]   [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]        [n]
  +----+ +----+ +----+ +----+ +----+ +----+ +----+ +----+ +----+     +----+
  | ???| | ???| | ???| | ???| | ???| | ???| | ???| | ???| | ???| ... | ???|
  +----+ +----+ +----+ +----+ +----+ +----+ +----+ +----+ +----+     +----+

    - One door hides a CAR 🚗
    - The other nine hide GOATS 🐐

    Game Flow:
    -------------------------------
    1. Player picks a door
    2. Monty opens n-2 goat doors
    3. Two doors remain closed (player's and one more)
    4. Player decides to switch or stay
    5. Reveal prize and update stats
    -------------------------------

    Probabilities:
    - Stay:    1/n
    - Switch:  (n-1)/n
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

int getUserChoice(int numDoors) {
    int choice;
    while (true) {
        cout << "\nPick a door (1 to " << numDoors << "): ";
        cin >> choice;
        if (choice >= 1 && choice <= numDoors) break;
        cout << "Invalid input. Please choose a valid door.\n";
    }
    return choice - 1;
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

void printIntroDiagram(int numDoors) {
    cout << "\n   ============================\n";
    cout << "       MONTY HALL - " << numDoors << " DOORS\n";
    cout << "   ============================\n\n";

    // Door numbers
    cout << "    ";
    for (int i = 0; i < numDoors; ++i)
        cout << "[" << (i + 1) << "]     ";
    cout << "\n";

    // Top borders
    cout << "   ";
    for (int i = 0; i < numDoors; ++i)
        cout << "+-----+ ";
    cout << "\n";

    // Middle "???" row
    cout << "   ";
    for (int i = 0; i < numDoors; ++i)
        cout << "| ??? | ";
    cout << "\n";

    // Bottom borders
    cout << "   ";
    for (int i = 0; i < numDoors; ++i)
        cout << "+-----+ ";
    cout << "\n";

    cout << "\n   - One door hides a CAR\n";
    cout << "   - The others hide GOATS\n";
    cout << "   - Monty will reveal all goat doors except one\n";
}

void displayDoors(int numDoors, vector<int> revealedGoats = {}, int userPick = -1, int prize = -1, bool final = false) {
    cout << "\n   Doors:\n   ";
    for (int i = 0; i < numDoors; ++i)
        cout << "[" << (i + 1) << "]     ";
    cout << "\n   ";
    for (int i = 0; i < numDoors; ++i)
        cout << "+-----+ ";
    cout << "\n   ";
    for (int i = 0; i < numDoors; ++i) {
        if (final) {
            if (i == prize) cout << "| CAR | ";
            else cout << "|GOAT | ";
        } else if (find(revealedGoats.begin(), revealedGoats.end(), i) != revealedGoats.end()) {
            cout << "|GOAT | ";
        } else {
            cout << "| ??? | ";
        }
    }
    cout << "\n   ";
    for (int i = 0; i < numDoors; ++i)
        cout << "+-----+ ";
    cout << "\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int numDoors;
    cout << "Enter number of doors (minimum 3): ";
    cin >> numDoors;
    if (numDoors < 3) numDoors = 3;

    printIntroDiagram(numDoors);

    bool playAgain = true;
    int gamesPlayed = 0;
    int switchWins = 0, switchLosses = 0, stayWins = 0, stayLosses = 0;

    while (playAgain) {
        int prizeDoor = rand() % numDoors;
        int userChoice = getUserChoice(numDoors);

        // Monty reveals all goat doors except one
        vector<int> revealCandidates;
        for (int i = 0; i < numDoors; ++i) {
            if (i != userChoice && i != prizeDoor)
                revealCandidates.push_back(i);
        }

        random_shuffle(revealCandidates.begin(), revealCandidates.end());

        vector<int> revealedGoats;
        for (int i = 0; i < numDoors - 2; ++i)
            revealedGoats.push_back(revealCandidates[i]);

        cout << "\nMonty opens " << revealedGoats.size() << " goat doors:\n";
        displayDoors(numDoors, revealedGoats, userChoice);

        // Get remaining unopened doors
        vector<int> unopened;
        for (int i = 0; i < numDoors; ++i) {
            if (find(revealedGoats.begin(), revealedGoats.end(), i) == revealedGoats.end())
                unopened.push_back(i);
        }

        bool switchChoice = getYesOrNo("Do you want to switch your choice?");
        if (switchChoice) {
            for (int door : unopened) {
                if (door != userChoice) {
                    userChoice = door;
                    break;
                }
            }
        }

        cout << "\nFinal reveal:\n";
        displayDoors(numDoors, {}, userChoice, prizeDoor, true);

        if (userChoice == prizeDoor) {
            cout << "\n:) You WON the car!\n";
            if (switchChoice) switchWins++; else stayWins++;
        } else {
            cout << "\n:(You got a goat. The car was behind door " << (prizeDoor + 1) << ".\n";
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
