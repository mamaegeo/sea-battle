#include "Game.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include "ASCIIArt.hpp"
#define CLEAR_SCREEN "clear"

/**
 * Constructor: initializes the board and game settings
 */
Game::Game(const GameSettings& settings)
    : board(settings.width, settings.height, settings.ships),
      maxAttempts(settings.maxAttempts),
      updated(true),
      running(true),
      attempts(0) {}

/** Print rainbow ASCII art */
void Game::printRainbowASCII() {
    std::cout << ASCIIArt::rainbowSeaBattle << std::endl;
}

/**
 * Main game loop
 * Uses three threads:
 *  - inputThread: handles user input
 *  - renderThread: redraws the board when updated
 *  - computeThread: optional timing/animations
 */
void Game::run() {
    /** Input thread */
    inputThread = std::thread([this]() {
        while (running) {
            std::string line;
            std::getline(std::cin, line); // read the full line

            /** Quit command */
            if (line == "q") {
                std::lock_guard<std::mutex> lock(mtx);
                running = false;
                updated = true;
                lastMessage = "Goodbye!";
                cv.notify_all();
                break;
            }

            /** Parse row and column */
            std::istringstream iss(line);
            int row, col;
            if (!(iss >> row >> col)) {
                std::lock_guard<std::mutex> lock(mtx);
                lastMessage = "Invalid input! Enter row and col separated by space.";
                updated = true;
                cv.notify_all();
                continue; // skip this iteration
            }

            /** Shoot at cell */
            bool hit = board.shoot(row, col);
            attempts++;
            if (hit) hits++;
            else misses++;

            /** Check max attempts */
            if (attempts >= maxAttempts) {
                std::lock_guard<std::mutex> lock(mtx);
                lastMessage = "You lose! Maximum attempts reached.";
                running = false;
                updated = true;
                cv.notify_all();
                break;
            }

            /** Update UI message */
            std::lock_guard<std::mutex> lock(mtx);
            lastMessage =
                std::string(hit ? "Hit!" : "Miss!") +
                " | Ships remaining: " + std::to_string(board.shipsRemaining()) +
                " | Attempts: " + std::to_string(attempts) +
                "/" + std::to_string(maxAttempts);
            updated = true;
            cv.notify_all();

            /** Check win condition */
            if (board.allShipsSunk()) {
                std::lock_guard<std::mutex> lock(mtx);
                lastMessage = "You win! Total attempts: " + std::to_string(attempts);
                running = false;
                updated = true;
            }
        }
    });

    /** Render thread */
    renderThread = std::thread([this]() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this]() { return updated; });

            system(CLEAR_SCREEN);
            std::cout << "A single player Sea Battle game in C++\n";
            printRainbowASCII();
            std::cout << "Enter row col or q to quit\n\n";
            board.draw();

            if (!lastMessage.empty()) {
                std::cout << lastMessage << "\n";
                lastMessage.clear();
            }

            updated = false;

            if (!running && !updated) break; // exit after final draw
        }
    });


    /** Compute */
    computeThread = std::thread([this]() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            // future: maybe timers, animations, scoring
        }
    });

    /** Wait for threads */
    inputThread.join();
    renderThread.join();
    computeThread.join();
    printStats();
} 

/** Print final game statistics */
void Game::printStats() {
    std::cout << "\n--- Game statistics ---\n";
    std::cout << "Attempts: " << attempts << "\n";
    std::cout << "Hits:     " << hits << "\n";
    std::cout << "Misses:   " << misses << "\n";

    if (attempts > 0) {
        double accuracy = (double)hits / attempts * 100.0;
        std::cout << "Accuracy: " << accuracy << "%\n";
    }
}