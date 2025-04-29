#include <iostream>
#include <vector>
#include <algorithm> // For random_shuffle
#include <cstdlib>
#include <ctime>

using namespace std;

bool playMontyHallSimulation(int numberOfDoors, bool switchChoice) {
    int prizeDoor = rand() % numberOfDoors;
    int playerChoice = rand() % numberOfDoors;

    // Step 1: Build list of doors Monty can open (not player choice, not prize)
    vector<int> openableGoatDoors;
    for (int i = 0; i < numberOfDoors; ++i) {
        if (i != playerChoice && i != prizeDoor) {
            openableGoatDoors.push_back(i);
        }
    }

    // Step 2: Monty opens (numberOfDoors - 2) goat doors
    random_shuffle(openableGoatDoors.begin(), openableGoatDoors.end());
    vector<int> montyOpens;
    for (int i = 0; i < numberOfDoors - 2; ++i) {
        montyOpens.push_back(openableGoatDoors[i]);
    }

    // Step 3: Find unopened doors
    vector<int> unopenedDoors;
    for (int i = 0; i < numberOfDoors; ++i) {
        if (find(montyOpens.begin(), montyOpens.end(), i) == montyOpens.end()) {
            unopenedDoors.push_back(i);
        }
    }

    // Step 4: If player switches, pick the other unopened door
    if (switchChoice) {
        for (int door : unopenedDoors) {
            if (door != playerChoice) {
                playerChoice = door;
                break;
            }
        }
    }

    // Step 5: Return whether player wins
    return playerChoice == prizeDoor;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int numberOfDoors;
    cout << "Enter number of doors (minimum 3): ";
    cin >> numberOfDoors;
    if (numberOfDoors < 3) numberOfDoors = 3;

    int simulations;
    cout << "Enter number of simulations: ";
    cin >> simulations;

    int switchWins = 0;
    int stayWins = 0;

    for (int i = 0; i < simulations; ++i) {
        if (playMontyHallSimulation(numberOfDoors, true)) {
            switchWins++;
        }
        if (playMontyHallSimulation(numberOfDoors, false)) {
            stayWins++;
        }
    }

    cout << "\nResults after " << simulations << " simulations:\n";
    cout << "Wins if switched: " << switchWins << " (" << (switchWins * 100.0 / simulations) << "%)\n";
    cout << "Wins if stayed  : " << stayWins << " (" << (stayWins * 100.0 / simulations) << "%)\n";

    return 0;
}
