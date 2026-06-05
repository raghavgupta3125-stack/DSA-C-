#include <bits/stdc++.h>
using namespace std;

class Difficulty {
public:
    string name;
    int maxNum;
    int maxGuesses;
    string flavour;
    string zone;
    Difficulty(string n, int m, int g, string f, string z) {
        name = n; maxNum = m; maxGuesses = g; flavour = f; zone = z;
    }
};

struct Record {
    string level;
    int guesses;
    bool won;
};

vector<Difficulty> LEVELS = {
    {"Cadet",    50,  9, "A faint signal echoes from the asteroid belt.", "Asteroid Belt"},
    {"Pilot",   100,  7, "The signal drifts deep into the nebula.", "Nebula Sector"},
    {"Commander",200, 6, "Dark matter clouds your instruments.", "Dark Matter Zone"},
    {"Admiral", 500,  5, "The signal originates from the edge of the known universe.", "Event Horizon"}
};

vector<Record> session;

void divider(char ch = '-', int w = 56) {
    for (int i = 0; i < w; i++) cout << ch;
    cout << "\n";
}

void boxLine(string text, int w = 54) {
    cout << "| " << left << setw(w) << text << " |\n";
}

void banner() {
    divider('*', 56);
    boxLine("   *  S P A C E   S I G N A L   H U N T E R  *");
    divider('*', 56);
    boxLine("  \"A signal has been detected. Can you lock on?\"");
    divider('-', 56);
    cout << "\n";
}

string proximity(int diff, int range) {
    double pct = (double)diff / range;
    if      (pct <= 0.02) return "[LOCKED ON ]  Signal acquired!";
    else if (pct <= 0.05) return "[PINGING   ]  Extremely close!";
    else if (pct <= 0.10) return "[STRONG    ]  Signal is strong.";
    else if (pct <= 0.20) return "[MODERATE  ]  Signal detected nearby.";
    else if (pct <= 0.35) return "[FAINT     ]  Signal growing weaker.";
    else if (pct <= 0.50) return "[STATIC    ]  Mostly interference.";
    else                  return "[DEAD SPACE ]  No signal found.";
}

string scanBar(int remaining, int total) {
    string bar = "[";
    for (int i = 0; i < total; i++)
        bar += (i < remaining) ? ">" : ".";
    bar += "]";
    return bar;
}

void showScoreboard() {
    if (session.empty()) {
        cout << "No missions logged yet.\n";
        return;
    }
    divider('=', 56);
    cout << "| " << left << setw(14) << "Rank"
         << "| " << setw(9)  << "Result"
         << "| " << setw(10) << "Scans"
         << "|\n";
    divider('-', 56);
    for (auto& r : session) {
        cout << "| " << left << setw(13) << r.level
             << "| " << setw(8)  << (r.won ? "SUCCESS" : "LOST")
             << "| " << setw(10) << r.guesses << "|\n";
    }
    divider('=', 56);
}

void playRound(Difficulty& d) {
    int secret = rand() % d.maxNum + 1;
    int scansLeft = d.maxGuesses;
    int totalScans = 0;
    bool won = false;
    vector<int> history;

    cout << "\n  >> MISSION ZONE: " << d.zone << "\n";
    cout << "  " << d.flavour << "\n\n";
    divider('-', 56);
    cout << "  Frequency range : 1 - " << d.maxNum << "\n";
    cout << "  Scan attempts   : " << d.maxGuesses << "\n";
    divider('-', 56);

    while (scansLeft > 0) {
        if (!history.empty()) {
            cout << "\n  Past scans: ";
            for (int x : history) cout << x << " ";
            cout << "\n";
        }

        cout << "\n  Scans remaining : " << scanBar(scansLeft, d.maxGuesses)
             << " " << scansLeft << "\n";
        cout << "  Enter frequency : ";

        string line;
        getline(cin, line);

        bool valid = !line.empty();
        for (char c : line) if (!isdigit(c)) { valid = false; break; }

        if (!valid) { cout << "  Invalid input. Enter a number.\n"; continue; }

        int guess = stoi(line);
        if (guess < 1 || guess > d.maxNum) {
            cout << "  Frequency must be between 1 and " << d.maxNum << ".\n";
            continue;
        }

        history.push_back(guess);
        totalScans++;
        scansLeft--;

        if (guess == secret) {
            won = true;
            cout << "\n";
            divider('*', 56);
            cout << "  SIGNAL LOCKED!\n";
            cout << "  Target frequency : " << secret << "\n";
            cout << "  Scans used       : " << totalScans << "\n";
            divider('*', 56);
            break;
        }

        cout << "\n";
        cout << "  --> Scan " << (guess < secret ? "HIGHER" : "LOWER") << "\n";
        cout << "  --> " << proximity(abs(secret - guess), d.maxNum) << "\n";
    }

    if (!won) {
        cout << "\n";
        divider('*', 56);
        cout << "  SIGNAL LOST\n";
        cout << "  Scan attempts exhausted.\n";
        cout << "  Target frequency was : " << secret << "\n";
        divider('*', 56);
    }

    divider('-', 56);
    cout << "  MISSION LOG\n";
    cout << "  Rank   : " << d.name << "\n";
    cout << "  Result : " << (won ? "SUCCESS" : "LOST") << "\n";
    cout << "  Scans  : " << totalScans << "\n";
    divider('-', 56);

    session.push_back({d.name, totalScans, won});
}

int chooseRank() {
    divider('-', 56);
    cout << "  Select mission rank:\n\n";
    for (int i = 0; i < (int)LEVELS.size(); i++) {
        cout << "  [" << (i + 1) << "] " << left << setw(14) << LEVELS[i].name
             << "  Range: 1-" << LEVELS[i].maxNum
             << "  Scans: " << LEVELS[i].maxGuesses << "\n";
    }
    divider('-', 56);

    while (true) {
        cout << "  Enter rank (1-" << LEVELS.size() << "): ";
        string in;
        getline(cin, in);

        bool valid = !in.empty();
        for (char c : in) if (!isdigit(c)) { valid = false; break; }

        if (valid) {
            int ch = stoi(in);
            if (ch >= 1 && ch <= (int)LEVELS.size()) return ch - 1;
        }
        cout << "  Invalid. Try again.\n";
    }
}

int main() {
    srand(time(0));
    banner();

    while (true) {
        cout << "\n  [M] Mission   [L] Log   [Q] Quit\n  > ";
        string cmd;
        if (!getline(cin, cmd) || cmd.empty()) continue;

        char ch = tolower(cmd[0]);

        if (ch == 'q') {
            cout << "\n  Mission Log\n";
            showScoreboard();
            cout << "\n  Signing off. Safe travels, Commander.\n";
            break;
        } else if (ch == 'l') {
            showScoreboard();
        } else if (ch == 'm') {
            int idx = chooseRank();
            playRound(LEVELS[idx]);
        } else {
            cout << "  Unknown command. Use M, L, or Q.\n";
        }
    }
    return 0;
}