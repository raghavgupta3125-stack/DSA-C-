
#include <ncurses.h>
#include <chrono>
#include <cstdlib>
#include <string>
#include <thread>


constexpr int PADDLE_HEIGHT = 4;
constexpr int WIN_SCORE     = 5;
constexpr int FRAME_DELAY_MS = 30; // controls overall game speed

struct Ball {
    double x, y;
    double vx, vy;
};

struct Paddle {
    int x;      // fixed column
    int y;      // top of paddle (row)
};


void resetBall(Ball &ball, int rows, int cols) {
    ball.x = cols / 2.0;
    ball.y = rows / 2.0;
    ball.vx = (std::rand() % 2 == 0) ? 1.0 : -1.0;
    ball.vy = ((std::rand() % 3) - 1) * 0.5; // -0.5, 0, or 0.5
    if (ball.vy == 0.0) ball.vy = 0.5;
}


void clampPaddle(Paddle &p, int rows) {
    if (p.y < 1) p.y = 1;
    if (p.y + PADDLE_HEIGHT > rows - 1) p.y = rows - 1 - PADDLE_HEIGHT;
}

void drawBorders(int rows, int cols) {
    for (int x = 0; x < cols; ++x) {
        mvaddch(0, x, '-');
        mvaddch(rows - 1, x, '-');
    }
}

void drawPaddle(const Paddle &p, int rows) {
    for (int i = 0; i < PADDLE_HEIGHT; ++i) {
        int row = p.y + i;
        if (row > 0 && row < rows - 1) {
            mvaddch(row, p.x, '|');
        }
    }
}

void drawCenterLine(int rows, int cols) {
    for (int y = 1; y < rows - 1; y += 2) {
        mvaddch(y, cols / 2, ':');
    }
}

void drawScore(int scoreLeft, int scoreRight, int cols) {
    std::string text = std::to_string(scoreLeft) + "   PONG   " + std::to_string(scoreRight);
    int startCol = (cols - static_cast<int>(text.size())) / 2;
    if (startCol < 0) startCol = 0;
    mvprintw(0, startCol, "%s", text.c_str());
}

void showEndScreen(int rows, int cols, const std::string &message) {
    nodelay(stdscr, FALSE); // switch to blocking input to wait for keypress
    clear();
    int row = rows / 2;
    int col = (cols - static_cast<int>(message.size())) / 2;
    if (col < 0) col = 0;
    mvprintw(row, col, "%s", message.c_str());
    std::string prompt = "Press any key to exit...";
    mvprintw(row + 2, (cols - static_cast<int>(prompt.size())) / 2, "%s", prompt.c_str());
    refresh();
    getch();
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

   
    initscr();
    cbreak();               
    noecho();                
    curs_set(0);              
    nodelay(stdscr, TRUE);    
    keypad(stdscr, TRUE);     

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    if (rows < 10 || cols < 40) {
        endwin();
        std::printf("Terminal window too small. Please resize to at least 40x10 and try again.\n");
        return 1;
    }

    // ---------- Game state ----------
    Paddle leftPaddle{2, rows / 2 - PADDLE_HEIGHT / 2};
    Paddle rightPaddle{cols - 3, rows / 2 - PADDLE_HEIGHT / 2};
    Ball ball;
    resetBall(ball, rows, cols);

    int scoreLeft = 0;
    int scoreRight = 0;
    bool running = true;
    std::string endMessage;

    while (running) {
        // ---------- Input ----------
        int ch;
        while ((ch = getch()) != ERR) {
            switch (ch) {
                case 'w': case 'W':
                    leftPaddle.y -= 1;
                    break;
                case 's': case 'S':
                    leftPaddle.y += 1;
                    break;
                case KEY_UP:
                    rightPaddle.y -= 1;
                    break;
                case KEY_DOWN:
                    rightPaddle.y += 1;
                    break;
                case 'q': case 'Q':
                    running = false;
                    break;
                default:
                    break;
            }
        }
        clampPaddle(leftPaddle, rows);
        clampPaddle(rightPaddle, rows);

        // ---------- Update ball ----------
        ball.x += ball.vx;
        ball.y += ball.vy;

        // Bounce off top/bottom walls
        if (ball.y <= 1) {
            ball.y = 1;
            ball.vy = -ball.vy;
        } else if (ball.y >= rows - 2) {
            ball.y = rows - 2;
            ball.vy = -ball.vy;
        }

        // Check collision with left paddle
        int bx = static_cast<int>(ball.x + 0.5);
        int by = static_cast<int>(ball.y + 0.5);

        if (bx == leftPaddle.x + 1 &&
            by >= leftPaddle.y && by < leftPaddle.y + PADDLE_HEIGHT &&
            ball.vx < 0) {
            ball.vx = -ball.vx;
            // add slight angle change based on where it hit the paddle
            double relative = (by - leftPaddle.y) - PADDLE_HEIGHT / 2.0;
            ball.vy += relative * 0.15;
        }

        // Check collision with right paddle
        if (bx == rightPaddle.x - 1 &&
            by >= rightPaddle.y && by < rightPaddle.y + PADDLE_HEIGHT &&
            ball.vx > 0) {
            ball.vx = -ball.vx;
            double relative = (by - rightPaddle.y) - PADDLE_HEIGHT / 2.0;
            ball.vy += relative * 0.15;
        }

        // Score check — ball passed a paddle
        if (bx < 1) {
            scoreRight++;
            resetBall(ball, rows, cols);
        } else if (bx > cols - 2) {
            scoreLeft++;
            resetBall(ball, rows, cols);
        }

        // Check win condition
        if (scoreLeft >= WIN_SCORE) {
            endMessage = "Player 1 (left) wins! " + std::to_string(scoreLeft) + " - " + std::to_string(scoreRight);
            running = false;
        } else if (scoreRight >= WIN_SCORE) {
            endMessage = "Player 2 (right) wins! " + std::to_string(scoreRight) + " - " + std::to_string(scoreLeft);
            running = false;
        }

        // ---------- Render ----------
        clear();
        drawBorders(rows, cols);
        drawCenterLine(rows, cols);
        drawScore(scoreLeft, scoreRight, cols);
        drawPaddle(leftPaddle, rows);
        drawPaddle(rightPaddle, rows);
        mvaddch(by, bx, 'O');
        refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY_MS));
    }

    if (!endMessage.empty()) {
        showEndScreen(rows, cols, endMessage);
    }

    endwin();
    return 0;
}