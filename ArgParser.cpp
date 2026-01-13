#include "ArgParser.hpp"

/**
 * Converts a string to an integer with error checking.
 */
int ArgParser::str2int(int* res, const char* str) {
    try {
        *res = std::stoi(str);
    } catch (const std::invalid_argument&) {
        return -1; // input is not a valid integer
    } catch (const std::out_of_range&) {
        return -2; // number is out of range for int
    }
    return 0;
}

/**
 * Parses command-line arguments into a ProgramArguments struct.
 * Supports width, height, number of ships, difficulty, and help flags.
 *
 * CLI examples:
 *   ./Battleship -w 8 -h 8 -s 5
 *   ./Battleship --difficulty 1
 *
 */
ProgramArguments ArgParser::parse(int argc, char* argv[]) {
    ProgramArguments args;
    
    /** Initialize with defaults */
    args.width = ARG_WIDTH_DEFAULT;
    args.height = ARG_HEIGHT_DEFAULT;
    args.ships = ARG_SHIPS_DEFAULT;
    args.help = false;
    args.difficulty = Difficulty::None;

    /** Loop through all arguments */
    for (int i = 1; i < argc; ++i) {
        /** Width */
        if (!std::strcmp(argv[i], "-w") || !std::strcmp(argv[i], "--width")) {
            int val;
            if (i + 1 < argc && str2int(&val, argv[i + 1]) == 0 &&
                val >= ARG_WIDTH_MIN && val <= ARG_WIDTH_MAX) {
                args.width = val; // set custom width
            }
            ++i; // skip value
        }
        /** Height */
        else if (!std::strcmp(argv[i], "-h") || !std::strcmp(argv[i], "--height")) {
            int val;
            if (i + 1 < argc && str2int(&val, argv[i + 1]) == 0 &&
                val >= ARG_HEIGHT_MIN && val <= ARG_HEIGHT_MAX) {
                args.height = val; // set custom height
            }
            ++i;
        }
        /** Ships */
        else if (!std::strcmp(argv[i], "-s") || !std::strcmp(argv[i], "--ships")) {
            int val;
            if (i + 1 < argc && str2int(&val, argv[i + 1]) == 0 &&
                val >= ARG_SHIPS_MIN && val <= ARG_SHIPS_MAX) {
                args.ships = val; // set custom number of ships
            }
            ++i;
        }
        /** Difficulty */
        else if (!std::strcmp(argv[i], "--difficulty")) {
            if (i + 1 < argc) {
                int diff;
                if (str2int(&diff, argv[i + 1]) == 0) {
                    switch (diff) {
                        case 0: args.difficulty = Difficulty::Easy; break;
                        case 1: args.difficulty = Difficulty::Normal; break;
                        case 2: args.difficulty = Difficulty::Hard; break;
                        default:
                            std::cerr << "Invalid difficulty: " << diff << ". Use 0=Easy,1=Normal,2=Hard.\n";
                            exit(1);  // exit immediately on invalid difficulty
                    }
                } else {
                    std::cerr << "Invalid difficulty value: " << argv[i+1] << "\n";
                    exit(1); // // exit if cannot convert to int
                }
            } else {
                std::cerr << "--difficulty requires a number (0=Easy,1=Normal,2=Hard)\n";
                exit(1);
            }
            ++i; // skip the value
        }
        /** Help */
        else if (!std::strcmp(argv[i], "--help")) {
            args.help = true; // flag to show help
        }
    }

    return args;
}
