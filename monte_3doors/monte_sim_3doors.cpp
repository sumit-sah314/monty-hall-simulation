#include <iostream>
#include <iomanip>  // for setw and setprecision
#include <cstdlib>
#include <ctime>

using namespace std;

// Simulates one game of Monty Hall
bool playMontyHall(bool switchDoor) {
    int prizeDoor = rand() % 3;          // Car is randomly placed behind one door
    int playerChoice = rand() % 3;       // Player picks randomly

    // Host opens a door that is neither the player's choice nor the prize door
    int hostOpens;
    do {
        hostOpens = rand() % 3;
    } while (hostOpens == prizeDoor || hostOpens == playerChoice);

    if (switchDoor) {
        // Player switches: pick the other unopened door
        for (int i = 0; i < 3; ++i) {
            if (i != playerChoice && i != hostOpens) {
                playerChoice = i;
                break;
            }
        }
    }

    return playerChoice == prizeDoor;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator

    int simulations;
    cout << "Enter the number of simulations to run for each strategy: ";
    cin >> simulations;

    int winsIfSwitched = 0;
    int winsIfStayed = 0;

    // Simulate switching strategy
    for (int i = 0; i < simulations; ++i) {
        if (playMontyHall(true)) {
            winsIfSwitched++;
        }
    }

    // Simulate staying strategy
    for (int i = 0; i < simulations; ++i) {
        if (playMontyHall(false)) {
            winsIfStayed++;
        }
    }

    // Calculate stats
    int lossesIfSwitched = simulations - winsIfSwitched;
    int lossesIfStayed = simulations - winsIfStayed;

    double switchWinPercent = winsIfSwitched * 100.0 / simulations;
    double stayWinPercent = winsIfStayed * 100.0 / simulations;
    double switchLossPercent = 100.0 - switchWinPercent;
    double stayLossPercent = 100.0 - stayWinPercent;

    // Display results nicely
    cout << "\n=== Monty Hall Simulation Results ===\n\n";
    cout << setw(15) << "Strategy"
         << setw(15) << "Wins"
         << setw(15) << "Losses"
         << setw(20) << "Win Percentage"
         << setw(20) << "Loss Percentage" << endl;
    cout << string(85, '-') << endl;

    cout << setw(15) << "Switch"
         << setw(15) << winsIfSwitched
         << setw(15) << lossesIfSwitched
         << setw(19) << fixed << setprecision(2) << switchWinPercent << "%"
         << setw(19) << fixed << setprecision(2) << switchLossPercent << "%" << endl;

    cout << setw(15) << "Stay"
         << setw(15) << winsIfStayed
         << setw(15) << lossesIfStayed
         << setw(19) << fixed << setprecision(2) << stayWinPercent << "%"
         << setw(19) << fixed << setprecision(2) << stayLossPercent << "%" << endl;

    return 0;
}
