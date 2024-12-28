#include <iostream>
#include <conio.h> // For _kbhit() and _getch()
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>

using namespace std;

const int WIDTH = 20; // Width of the game area
const int HEIGHT = 10; // Height of the game area
const char CAR = 'C'; // Player's car representation
const char OBSTACLE = 'X'; // Obstacle representation
const char EMPTY = ' '; // Empty space representation

class Game {
public:
    Game() : carPosition(WIDTH / 2), score(0), gameOver(false) {
        srand(static_cast<unsigned int>(time(0))); // Seed for random number generation
        spawnObstacle();
    }

    void run() {
        while (!gameOver) {
            draw();
            input();
            logic();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Control game speed
        }
        cout << "Game Over! Your score: " << score << endl;
    }

private:
    int carPosition; // Player's car position
    int obstaclePosition; // Current obstacle position
    int score; // Player's score
    bool gameOver; // Game over flag

    void spawnObstacle() {
        obstaclePosition = rand() % (WIDTH - 1); // Random position for the obstacle
    }

    void draw() {
        system("cls"); // Clear the console (Windows)
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                if (i == HEIGHT - 1 && j == carPosition) {
                    cout << CAR;
                } else if (i == 0 && j == obstaclePosition) {
                    cout << OBSTACLE;
                } else {
                    cout << EMPTY;
                }
            }
            cout << endl;
        }
        cout << "Score: " << score << endl;
    }

    void input() {
        if (_kbhit()) { // Check if a key is pressed
            switch (_getch()) {
                case 'a': // Move left
                    if (carPosition > 0) --carPosition;
                    break;
                case 'd': // Move right
                    if (carPosition < WIDTH - 1) ++carPosition;
                    break;
                case 'q': // Quit the game
                    gameOver = true;
                    break;
            }
        }
    }

    void logic() {
        // Move the obstacle down (here we just check for collision)
        if (obstaclePosition == carPosition && score > 0) {
            gameOver = true; // Collision detected, end the game
        } else if (obstaclePosition == WIDTH - 1) {
            score++; // Increase score when obstacle is avoided
