#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

using namespace std;



string choiceName(int choice) {
    switch (choice) {
        case 1: return "Rock  ✊";
        case 2: return "Paper ✋";
        case 3: return "Scissors ✌";
        default: return "Unknown";
    }
}

string choiceArt(int choice) {
    switch (choice) {
        case 1: return
            "    _______\n"
            "---'   ____)\n"
            "      (_____)\n"
            "      (_____)\n"
            "      (____)\n"
            "---.__(___)\n";
        case 2: return
            "    _______\n"
            "---'   ____)____\n"
            "          ______)\n"
            "          _______)\n"
            "         _______)\n"
            "---.__________)\n";
        case 3: return
            "    _______\n"
            "---'   ____)____\n"
            "          ______)\n"
            "       __________)\n"
            "      (____)      \n"
            "---.__(___)       \n";
        default: return "";
    }
}

void printSeparator() {
    cout << "\n" << string(45, '=') << "\n";
}

void printHeader() {
    cout << "\n";
    cout << "  ╔═══════════════════════════════════════╗\n";
    cout << "  ║    🪨  ROCK  PAPER  SCISSORS  ✂️      ║\n";
    cout << "  ╚═══════════════════════════════════════╝\n";
}


int getComputerChoice() {
    return (rand() % 3) + 1;   
}


int determineWinner(int player, int computer) {
    if (player == computer) return 0;

    
    if ((player == 1 && computer == 3) ||
        (player == 2 && computer == 1) ||
        (player == 3 && computer == 2))
        return 1;

    return -1;
}

int getPlayerChoice() {
    int choice;
    while (true) {
        cout << "\n  Your move:\n";
        cout << "    [1] Rock  ✊\n";
        cout << "    [2] Paper ✋\n";
        cout << "    [3] Scissors ✌\n";
        cout << "    [0] Quit\n";
        cout << "  --> ";

        if (cin >> choice) {
            if (choice >= 0 && choice <= 3) return choice;
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "  ⚠️  Invalid input! Enter 0, 1, 2, or 3.\n";
    }
}



int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int playerWins    = 0;
    int computerWins  = 0;
    int ties          = 0;
    int rounds        = 0;

    printHeader();
    cout << "\n  Best of how many rounds? (e.g. 3, 5, 7)\n  --> ";
    int bestOf;
    while (!(cin >> bestOf) || bestOf < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Please enter a positive number: ";
    }
    int winsNeeded = (bestOf / 2) + 1;
    cout << "\n  First to " << winsNeeded << " win(s) takes the match!\n";

    
    while (playerWins < winsNeeded && computerWins < winsNeeded) {
        printSeparator();
        cout << "  Round " << (rounds + 1)
             << "  |  You: " << playerWins
             << "  CPU: " << computerWins
             << "  Ties: " << ties << "\n";

        int playerChoice = getPlayerChoice();
        if (playerChoice == 0) {
            cout << "\n  👋 Quitting early. Goodbye!\n\n";
            return 0;
        }

        int cpuChoice = getComputerChoice();
        rounds++;

        
        cout << "\n  You chose:      " << choiceName(playerChoice) << "\n";
        cout << choiceArt(playerChoice);
        cout << "\n  Computer chose: " << choiceName(cpuChoice) << "\n";
        cout << choiceArt(cpuChoice);

        
        int result = determineWinner(playerChoice, cpuChoice);

        if (result == 0) {
            cout << "  🤝  It's a TIE!\n";
            ties++;
        } else if (result == 1) {
            cout << "  🎉  YOU WIN this round!\n";
            playerWins++;
        } else {
            cout << "  💻  COMPUTER WINS this round!\n";
            computerWins++;
        }
    }

    
    printSeparator();
    cout << "\n  ════ MATCH OVER ════\n\n";
    cout << "  Rounds played : " << rounds      << "\n";
    cout << "  Your wins     : " << playerWins  << "\n";
    cout << "  CPU wins      : " << computerWins<< "\n";
    cout << "  Ties          : " << ties        << "\n\n";

    if (playerWins >= winsNeeded) {
        cout << "  🏆  CONGRATULATIONS — YOU WIN THE MATCH!\n\n";
    } else {
        cout << "  🤖  THE COMPUTER WINS THE MATCH. Better luck next time!\n\n";
    }

    return 0;
}