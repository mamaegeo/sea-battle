#pragma once
#include "Board.hpp"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

/**
 * Settings for a single game instance
 */
struct GameSettings {
    int width;
    int height;
    int ships;
    int maxAttempts;
};

/**
 * Main game class: handles the board, user input, rendering, and game logic.
 */
class Game {
public:
    Game(const GameSettings& settings);

    /** Run the main game loop (starts threads for input, rendering, optional compute) */
    void run();

    /** Print the colorful rainbow ASCII art */
    void printRainbowASCII();

    /** Print the colorful rainbow ASCII art */
    void printStats();

private:
    Board board;
    int attempts;
    int maxAttempts;
    int hits = 0;
    int misses = 0;

    /** Threads and synchronization */
    std::thread inputThread; // input handling
    std::thread renderThread; // board rendering
    std::thread computeThread; // optional timing
    std::mutex mtx; // mutex for shared state
    std::condition_variable cv; // signal for rendering updates
    bool updated; // flag indicating board needs redraw
    std::atomic<bool> running; // game running flag
    std::string lastMessage; // message to display in terminal
};
