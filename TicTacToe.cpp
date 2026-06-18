#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class TicTacToe {
private:
    vector<char> board;   // 9 cells, indices 0-8
    char currentPlayer;

public:
    TicTacToe() {
        board = vector<char>(9, ' ');
        currentPlayer = 'X';
    }

    void printBoard() {
        cout << "\n";
        for (int row = 0; row < 3; row++) {
            cout << " " << board[row * 3] << " | " << board[row * 3 + 1]
                 << " | " << board[row * 3 + 2] << " \n";
            if (row < 2) cout << "---+---+---\n";
        }
        cout << "\n";
    }

    void printGuide() {
        cout << "Positions are numbered like this:\n";
        cout << " 1 | 2 | 3 \n---+---+---\n 4 | 5 | 6 \n---+---+---\n 7 | 8 | 9 \n\n";
    }

    bool isValidMove(int pos) {
        return pos >= 1 && pos <= 9 && board[pos - 1] == ' ';
    }

    void makeMove(int pos) {
        board[pos - 1] = currentPlayer;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    bool checkWin() {
        int wins[8][3] = {
            {0,1,2}, {3,4,5}, {6,7,8}, // rows
            {0,3,6}, {1,4,7}, {2,5,8}, // columns
            {0,4,8}, {2,4,6}           // diagonals
        };
        for (auto &w : wins) {
            if (board[w[0]] != ' ' && board[w[0]] == board[w[1]] && board[w[1]] == board[w[2]])
                return true;
        }
        return false;
    }

    bool isBoardFull() {
        for (char c : board)
            if (c == ' ') return false;
        return true;
    }

    char getCurrentPlayer() { return currentPlayer; }

    void play() {
        cout << "=========================\n";
        cout << "     TIC TAC TOE GAME    \n";
        cout << "=========================\n\n";
        printGuide();

        while (true) {
            printBoard();
            cout << "Player " << currentPlayer << ", enter your move (1-9): ";

            int pos;
            if (!(cin >> pos)) {
                // Clear invalid (non-numeric) input
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 9.\n";
                continue;
            }

            if (!isValidMove(pos)) {
                cout << "Invalid move! That cell is either occupied or out of range. Try again.\n";
                continue;
            }

            makeMove(pos);

            if (checkWin()) {
                printBoard();
                cout << "*** Player " << currentPlayer << " wins! Congratulations! ***\n";
                break;
            }

            if (isBoardFull()) {
                printBoard();
                cout << "It's a draw! Good game.\n";
                break;
            }

            switchPlayer();
        }
    }
};

int main() {
    char playAgain;
    do {
        TicTacToe game;
        game.play();

        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\nThanks for playing! Goodbye.\n";
    return 0;
}