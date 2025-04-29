#include <iostream>
#include <vector>
#include <algorithm> // For random_shuffle
#include <cstdlib>
#include <ctime>
#include <iomanip>   // For setw, setprecision

using namespace std;

// Simulate one game of Monty Hall with N doors
bool playMontyHallSimulation(int numberOfDoors, bool switchChoice) {
    int prizeDoor = rand() % numberOfDoors;
    int playerChoice = rand() % numberOfDoors;

    // Build list of goat doors Monty can open (not prize, not player choice)
    vector<int> openableGoatDoors;
    for (int i = 0; i < numberOfDoors; ++i) {
        if (i != playerChoice && i != prizeDoor) {
            openableGoatDoors.push_back(i);
        }
    }

    random_shuffle(openableGoatDoors.begin(), openableGoatDoors.end());

    // Monty opens (numberOfDoors - 2) goat doors
    vector<int> montyOpens;
    for (int i = 0; i < numberOfDoors - 2; ++i) {
        montyOpens.push_back(openableGoatDoors[i]);
    }

    // Find remaining unopened doors
    vector<int> unopenedDoors;
    for (int i = 0; i < numberOfDoors; ++i) {
        if (find(montyOpens.begin(), montyOpens.end(), i) == montyOpens.end()) {
            unopenedDoors.push_back(i);
        }
    }

    // If player switches, switch to the other unopened door
    if (switchChoice) {
        for (int door : unopenedDoors) {
            if (door != playerChoice) {
                playerChoice = door;
                break;
            }
        }
    }

    // Return true if player wins
    return playerChoice == prizeDoor;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int numberOfDoors;
    cout << "Enter number of doors (minimum 3): ";
    cin >> numberOfDoors;
    if (numberOfDoors < 3) numberOfDoors = 3;

    int simulations;
    cout << "Enter number of simulations to run for each strategy: ";
    cin >> simulations;

    int switchWins = 0;
    int stayWins = 0;

    // Simulate switching strategy
    for (int i = 0; i < simulations; ++i) {
        if (playMontyHallSimulation(numberOfDoors, true)) {
            switchWins++;
        }
    }

    // Simulate staying strategy
    for (int i = 0; i < simulations; ++i) {
        if (playMontyHallSimulation(numberOfDoors, false)) {
            stayWins++;
        }
    }

    // Calculate losses
    int switchLosses = simulations - switchWins;
    int stayLosses = simulations - stayWins;

    double switchWinPercent = switchWins * 100.0 / simulations;
    double stayWinPercent = stayWins * 100.0 / simulations;
    double switchLossPercent = 100.0 - switchWinPercent;
    double stayLossPercent = 100.0 - stayWinPercent;

    // Display results nicely
    cout << "\n=== Monty Hall Simulation Results ===\n";
    cout << "Number of Doors: " << numberOfDoors << "\n";
    cout << "Simulations per strategy: " << simulations << "\n\n";

    cout << setw(15) << "Strategy"
         << setw(15) << "Wins"
         << setw(15) << "Losses"
         << setw(20) << "Win Percentage"
         << setw(20) << "Loss Percentage" << endl;
    cout << string(85, '-') << endl;

    cout << setw(15) << "Switch"
         << setw(15) << switchWins
         << setw(15) << switchLosses
         << setw(19) << fixed << setprecision(2) << switchWinPercent << "%"
         << setw(19) << fixed << setprecision(2) << switchLossPercent << "%" << endl;

    cout << setw(15) << "Stay"
         << setw(15) << stayWins
         << setw(15) << stayLosses
         << setw(19) << fixed << setprecision(2) << stayWinPercent << "%"
         << setw(19) << fixed << setprecision(2) << stayLossPercent << "%" << endl;

    return 0;
}
