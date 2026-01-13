#ifndef BATTLESHIP_ARGPARSER_H
#define BATTLESHIP_ARGPARSER_H

#include <string>
#include <iostream>
#include <cstring>

/* Default parameter values */
#define ARG_WIDTH_DEFAULT 5
#define ARG_WIDTH_MIN 3
#define ARG_WIDTH_MAX 10
#define ARG_HEIGHT_DEFAULT 5
#define ARG_HEIGHT_MIN 3
#define ARG_HEIGHT_MAX 10
#define ARG_SHIPS_DEFAULT 3
#define ARG_SHIPS_MIN 1
#define ARG_SHIPS_MAX 5

enum class Difficulty {
    Easy,
    Normal,
    Hard,
    None // default if not set
};

/* Strcture for storing program parameters */
struct ProgramArguments {
    int width;
    int height;
    int ships;
    bool help;
    Difficulty difficulty = Difficulty::None; // default
};

class ArgParser {
public:
    /*
     * Parses arguments from the command line
     * argc, argv - standard arguments of main()
     */
    static ProgramArguments parse(int argc, char* argv[]);

private:
    /* Converting a string to an integer with validation */
    static int str2int(int* res, const char* str);
};

#endif // BATTLESHIP_ARGPARSER_H
