# DSA-C-
# Space Signal Hunter

A space-themed number guessing game written in C++. You play as a signal analyst tasked with locking onto a hidden radio frequency somewhere in deep space. Each mission rank increases the frequency range and reduces your scan attempts.

---

## Backstory

A mysterious signal has been detected from the far reaches of the universe. Your instruments can scan one frequency at a time. After each scan, your console reports whether the true signal is higher or lower — and how strong the proximity reading is. Lock on before your scans run out.

---

## How to Compile

You need a C++ compiler (g++ recommended).

```bash
g++ -o space_guesser space_guesser.cpp
```

---

## How to Run

```bash
./space_guesser
```

On Windows:

```bash
space_guesser.exe
```

---

## How to Play

At the main menu you will see three options:

```
[M] Mission   [L] Log   [Q] Quit
```

| Key | Action |
|-----|--------|
| `M` | Start a new mission (choose a rank first) |
| `L` | View your session mission log |
| `Q` | Quit and display the final log |

### Starting a mission

1. Press `M` and select a mission rank (1–4).
2. Enter a frequency number when prompted.
3. After each scan your console will tell you to go **higher** or **lower**, along with a signal strength reading.
4. Lock on to the target frequency before your scans run out.

---

## Mission Ranks

| Rank | Zone | Frequency Range | Scan Attempts |
|------|------|----------------|---------------|
| Cadet | Asteroid Belt | 1 – 50 | 9 |
| Pilot | Nebula Sector | 1 – 100 | 7 |
| Commander | Dark Matter Zone | 1 – 200 | 6 |
| Admiral | Event Horizon | 1 – 500 | 5 |

---

## Signal Strength Readings

After each scan, your console reports a proximity reading:

| Reading | Meaning |
|---------|---------|
| `LOCKED ON` | You are right on top of it |
| `PINGING` | Extremely close |
| `STRONG` | Very close |
| `MODERATE` | Getting warmer |
| `FAINT` | Some distance away |
| `STATIC` | Far off |
| `DEAD SPACE` | Nowhere near it |

---

## Scan Bar

The scan bar shows how many attempts you have left at a glance:

```
[>>>>>>>>>]  9     (full)
[>>>>>....] 5      (halfway)
[>..........]  1   (almost out)
```

---

## Mission Log

Your results are tracked for the current session. Press `L` at any time or `Q` at the end to view them:

```
========================================================
| Rank          | Result   | Scans     |
--------------------------------------------------------
| Commander     | SUCCESS  | 4         |
| Admiral       | LOST     | 5         |
========================================================
```

---

## Requirements

- C++11 or later
- Any standard terminal / command prompt
- No external libraries required

---

## File Structure

```
space_guesser.cpp   — full game source code
README.md           — this file
```

---

## Tips

- On Admiral rank (1–500, 5 scans) use binary search: always guess the midpoint of your remaining range.
- The `PINGING` and `STRONG` readings mean you are within 5–10% of the range — narrow in fast.
- Your scan history is printed before each guess so you never lose track of what you have tried.