# 🪨 Rock Paper Scissors — C++ Console Game

A feature-rich, terminal-based Rock Paper Scissors game written in C++. Play best-of-N matches against the computer with live scoreboards, ASCII hand art, and input validation.

---

## 📁 Project Structure

```
rock_paper_scissors/
├── rock_paper_scissors.cpp   # Full game source code
└── README.md                 # This file
```

---

## ⚙️ Requirements

| Tool | Minimum Version |
|------|----------------|
| C++ Compiler (g++ / clang++ / MSVC) | C++11 or later |
| Terminal / Command Prompt | Any |

No external libraries are needed — uses only the C++ Standard Library.

---

## 🚀 How to Compile & Run

### 🐧 Linux / 🍎 macOS

```bash
# Compile
g++ -o rps rock_paper_scissors.cpp

# Run
./rps
```

### 🪟 Windows — MinGW (g++)

```cmd
g++ -o rps.exe rock_paper_scissors.cpp
rps.exe
```

### 🪟 Windows — MSVC

```cmd
cl rock_paper_scissors.cpp /Fe:rps.exe
rps.exe
```

### 🪟 Windows — PowerShell shortcut

```powershell
g++ rock_paper_scissors.cpp -o rps; ./rps
```

---

## 🎮 How to Play

1. **Run the program** — you'll see the title screen.
2. **Choose a format** — enter how many rounds to play (e.g. `3` for best of 3, `5` for best of 5).
3. **Make your move each round:**
   - `1` → Rock ✊
   - `2` → Paper ✋
   - `3` → Scissors ✌️
   - `0` → Quit the game early
4. **First player to reach the required wins takes the match!**

---

## 🕹️ Game Rules

| Player | Computer | Result |
|--------|----------|--------|
| Rock | Scissors | ✅ Player Wins |
| Paper | Rock | ✅ Player Wins |
| Scissors | Paper | ✅ Player Wins |
| Rock | Paper | ❌ Computer Wins |
| Scissors | Rock | ❌ Computer Wins |
| Paper | Scissors | ❌ Computer Wins |
| Any | Same | 🤝 Tie (no point awarded) |

---

## ✨ Features

- **Best-of-N match system** — configure match length before starting
- **ASCII hand art** — visual display of each player's move
- **Live scoreboard** — tracks wins, losses, and ties each round
- **Random computer moves** — seeded with system time for true randomness
- **Input validation** — safely handles letters, symbols, and out-of-range numbers
- **Quit anytime** — press `0` at the move prompt to exit gracefully

---

## 📸 Sample Output

```
  ╔═══════════════════════════════════════╗
  ║    🪨  ROCK  PAPER  SCISSORS  ✂️      ║
  ╚═══════════════════════════════════════╝

  Best of how many rounds? (e.g. 3, 5, 7)
  --> 3

  First to 2 win(s) takes the match!

  =============================================
  Round 1  |  You: 0  CPU: 0  Ties: 0

  Your move:
    [1] Rock  ✊
    [2] Paper ✋
    [3] Scissors ✌
    [0] Quit
  --> 1

  You chose:      Rock  ✊
      _______
  ---'   ____)
        (_____)
        (_____)
        (____)
  ---.__(___) 

  Computer chose: Scissors ✌
      _______
  ---'   ____)____
            ______)
         __________)
        (____)
  ---.__(___)

  🎉  YOU WIN this round!

  =============================================

  ════ MATCH OVER ════

  Rounds played : 3
  Your wins     : 2
  CPU wins      : 1
  Ties          : 0

  🏆  CONGRATULATIONS — YOU WIN THE MATCH!
```

---

## 🧠 Code Overview

| Function | Purpose |
|----------|---------|
| `choiceName(int)` | Returns the display name + emoji for a move |
| `choiceArt(int)` | Returns ASCII art string for a move |
| `getComputerChoice()` | Generates a random move (1–3) for the CPU |
| `determineWinner(int, int)` | Returns `1` (player wins), `-1` (CPU wins), `0` (tie) |
| `getPlayerChoice()` | Prompts and validates user input |
| `printHeader()` | Displays the game title banner |
| `printSeparator()` | Prints a visual divider between rounds |
| `main()` | Match setup, game loop, and final result display |

---

## 🔧 Customisation Ideas

- **Add a difficulty level** — weight CPU's random choices to simulate strategy
- **Multiplayer mode** — let two human players take turns on the same keyboard
- **Rock Paper Scissors Lizard Spock** — extend `determineWinner()` to handle 5 choices
- **Save high scores** — write match results to a `.txt` file using `<fstream>`
- **Colour output** — use ANSI escape codes for coloured terminal text on Linux/macOS

---

