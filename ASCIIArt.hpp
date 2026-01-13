#pragma once
#include <string>

/**
* rainbowSeaBattle: colorized ASCII art for Battleship intro
* 
* Usage: std::cout << ASCIIArt::rainbowSeaBattle << std::endl;
* 
* Contains multiple lines of colorful cats, used for
* the start screen to set the mood :З
* ANSI escape codes are used for colors (red, yellow, green, cyan, blue, magenta).
*/

namespace ASCIIArt {
    const std::string rainbowSeaBattle =
        "\x1B[91m /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\ \x1B[0m\n"
        "\x1B[93m( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )\x1B[0m\n"
        "\x1B[92m > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ < \x1B[0m\n"
        "\x1B[96m /\\_/\\    ____  _____    _      ____    _  _____ _____ _     _____     /\\_/\\ \x1B[0m\n"
        "\x1B[94m( o.o )  / ___|| ____|  / \\    | __ )  / \\|_   _|_   _| |   | ____|   ( o.o )\x1B[0m\n"
        "\x1B[95m > ^ <   \\___ \\|  _|   / _ \\   |  _ \\ / _ \\ | |   | | | |   |  _|      > ^ < \x1B[0m\n"
        "\x1B[91m /\\_/\\    ___) | |___ / ___ \\  | |_) / ___ \\| |   | | | |___| |___     /\\_/\\ \x1B[0m\n"
        "\x1B[93m( o.o )  |____/|_____/_/   \\_\\ |____/_/   \\_\\_|   |_| |_____|_____|   ( o.o )\x1B[0m\n"
        "\x1B[92m > ^ <                                                                 > ^ < \x1B[0m\n"
        "\x1B[96m /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\  /\\_/\\ \x1B[0m\n"
        "\x1B[94m( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )( o.o )\x1B[0m\n"
        "\x1B[95m > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ <  > ^ < \x1B[0m\n";
}
