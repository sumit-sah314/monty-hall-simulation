#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool playMontyHall(bool switchDoor) {
    int prizeDoor = rand() % 3;          // Car is randomly placed behind one door
    int playerChoice = rand() % 3;       // Player makes a random choice

    // Host opens a door that is neither the player's choice nor the prize door
    int hostOpens;
    do {
        hostOpens = rand() % 3;
    } while (hostOpens == prizeDoor || hostOpens == playerChoice);

    if (switchDoor) {
        // Player switches: pick the remaining unopened door
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
    srand(time(0));  // Seed random number generator

    int simulations;
    cout << "Enter the number of simulations to run: ";
    cin >> simulations;

    int winsIfSwitched = 0;
    int winsIfStayed = 0;

    for (int i = 0; i < simulations; ++i) {
        if (playMontyHall(true)) winsIfSwitched++;
        if (playMontyHall(false)) winsIfStayed++;
    }

    cout << "\nResults after " << simulations << " simulations:\n";
    cout << "Wins if switched: " << winsIfSwitched << " (" << (winsIfSwitched * 100.0 / simulations) << "%)\n";
    cout << "Wins if stayed  : " << winsIfStayed << " (" << (winsIfStayed * 100.0 / simulations) << "%)\n";

    return 0;
}
