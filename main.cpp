#include "Game.hpp"
#include "ArgParser.hpp"
#include <iostream>
#include <limits>
#include <string>

int main(int argc, char* argv[]) {
    /** Parse CLI arguments */
    ProgramArguments args = ArgParser::parse(argc, argv);
    
    /** Show help and exit */
    if (args.help) {
        std::cout << "Sea Battle Lite\n";
        std::cout << "Usage: ./seabattle [options]\n";
        std::cout << "  -w, --width   Width of the board (" << ARG_WIDTH_MIN << "-" << ARG_WIDTH_MAX << ")\n";
        std::cout << "  -h, --height  Height of the board (" << ARG_HEIGHT_MIN << "-" << ARG_HEIGHT_MAX << ")\n";
        std::cout << "  -s, --ships   Number of ships (" << ARG_SHIPS_MIN << "-" << ARG_SHIPS_MAX << ")\n";
        std::cout << "  --difficulty  Difficulty (0=Easy, 1=Normal, 2=Hard)\n";
        std::cout << "  --help        Show this help\n";
        return 0;
    }

    GameSettings settings;

    /** Determine settings from difficulty */
    if (args.difficulty != Difficulty::None) {
        switch (args.difficulty) {
            case Difficulty::Easy:
                settings = {6, 6, 4, 20}; // smaller board, fewer shipsv
                break;
            case Difficulty::Normal:
                settings = {8, 8, 5, 34};
                break;
            case Difficulty::Hard:
                settings = {10, 10, 7, 50}; // larger board, more ships, less attempts
                break;
            default: break;
        }
    }
    /** Use custom board settings from cli */
    else if (args.width != ARG_WIDTH_DEFAULT || args.height != ARG_HEIGHT_DEFAULT || args.ships != ARG_SHIPS_DEFAULT) {
        int defaultMaxAttempts = args.width * args.height * 3 / 4; // ~75% of board
        settings = {args.width, args.height, args.ships, defaultMaxAttempts};
    }
    /** Interactive difficulty selection */
    else {
        while (true) {
            std::cout << "Select difficulty or q to quit:\n";
            std::cout << "1 - Easy\n2 - Normal\n3 - Hard\n> ";

            std::string line;
            std::getline(std::cin, line);

            /** Quit option */
            if (line == "q" || line == "Q") {
                std::cout << "Goodbye!\n";
                return 0;
            }

            /** Parse user input */
            int choice;
            try {
                choice = std::stoi(line);
            } catch (...) {
                std::cout << "Invalid input!\n";
                continue; // reprompt
            }

            /** Map input to settings */
            switch (choice) {
                case 1: settings = {6, 6, 4, 20}; break;
                case 2: settings = {8, 8, 5, 34}; break;
                case 3: settings = {10, 10, 7, 50}; break;
                default:
                    std::cout << "Invalid choice!\n";
                    continue; // reprompt
            }
            break; // valid choice
        }
    }

    Game game(settings);
    game.run();

    return 0;
}
