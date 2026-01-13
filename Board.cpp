#include "Board.hpp"
#include <iostream>
#include <random>

/** ANSI color codes for terminal display */
#define COLOR_RED   "\x1B[91m"
#define COLOR_BLUE  "\x1B[94m"
#define COLOR_RESET "\x1B[m"
#define COLOR_BLINK "\x1B[5m"

/**
 * Board constructor: randomly places ships without overlapping.
 * Ensures 1-cell buffer around ships (no touching).
 */
Board::Board(int width, int height, int numShips)
    : w(width), h(height), field(width * height, '.') {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> rowDist(0, h-1);
    std::uniform_int_distribution<> colDist(0, w-1);
    std::uniform_int_distribution<> dirDist(0,1); // 0=horizontal, 1=vertical
    std::uniform_int_distribution<> sizeDist(2,4); // ship size 2–4
    int placed = 0;
    while (placed < numShips) {
        int shipSize = sizeDist(gen);
        bool horizontal = dirDist(gen) == 0;

        /** Adjust if ship would go out of bounds */
        int r = rowDist(gen);
        int c = colDist(gen);

        /** Adjust if ship would go out of bounds */
        if (horizontal && c + shipSize > w) c = w - shipSize;
        if (!horizontal && r + shipSize > h) r = h - shipSize;

        /** Check if ship can be placed (no overlap, 1-cell buffer) */
        bool canPlace = true;
        std::vector<std::pair<int,int>> coords;
        for (int i = 0; i < shipSize; ++i) {
            int ri = horizontal ? r : r + i;
            int ci = horizontal ? c + i : c;

            /** Check if cell or neighbors contain 'S' */
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    int nr = ri + dr;
                    int nc = ci + dc;
                    if (nr >= 0 && nr < h && nc >= 0 && nc < w) {
                        if (field[index(nr, nc)] == 'S') {
                            canPlace = false;
                            break;
                        }
                    }
                }
                if (!canPlace) break;
            }
            if (!canPlace) break;
            coords.push_back({ri, ci});
        }

        /** Place the ship */
        if (!canPlace) continue;
        for (auto [ri,ci] : coords) field[index(ri,ci)] = 'S';
        ships.push_back({coords});
        placed++;
    }
}

/** Convert 2D coordinates to linear index */
int Board::index(int row, int col) const {
    return row * w + col;
}

/** Shoot at a cell, update board, return hit/miss */
bool Board::shoot(int row, int col) {
    if (row<0 || row>=h || col<0 || col>=w) return false;  // already shot
    int i = index(row,col);
    if (field[i]=='X' || field[i]=='o') return false;

    lastRow = row;
    lastCol = col;

    if (field[i]=='S') {
        field[i] = 'X';
        return true;
    }

    field[i] = 'o';
    return false;
}

/** Check if all ships are sunk */
bool Board::allShipsSunk() const {
    for (const Ship& s : ships) {
        if (!s.isSunk(field,w)) return false;
    }
    return true;
}

/** Count the number of ships not yet sunk */
int Board::shipsRemaining() const {
    int count = 0;
    for (const Ship& s : ships) {
        if (!s.isSunk(field,w)) count++;
    }
    return count;
}

/** Draw board to terminal */
void Board::draw() const {
    /** Column numbers */
    std::cout << "    "; // space for row numbers
    for (int c = 0; c < w; ++c) {
        std::cout << c % 10 << ' ';
    }
    std::cout << '\n';

    /** Separator */
    std::cout << "  ";
    for (int c = 0; c < w * 2 + 1; ++c) std::cout << '-';
    std::cout << '\n';

    /** Rows */
    for (int r = 0; r < h; ++r) {
        std::cout << r % 10 << " | ";

        for (int c = 0; c < w; ++c) {
            char cell = field[index(r, c)];

            if (cell == 'X') std::cout << COLOR_RED << cell << COLOR_RESET << ' ';
            else if (cell == 'o') std::cout << COLOR_BLUE << cell << COLOR_RESET << ' ';
            else std::cout << ". ";
        }
        std::cout << '\n';
    }
}

/** Draw board with ships visible (for debugging) */
void Board::debugDrawShips() const {
    std::cout << "   "; 
    for (int c = 0; c < w; ++c) std::cout << c % 10 << ' ';
    std::cout << "\n  ";
    for (int c = 0; c < w * 2 + 1; ++c) std::cout << '-';
    std::cout << "\n";

    for (int r = 0; r < h; ++r) {
        std::cout << r % 10 << " | ";
        for (int c = 0; c < w; ++c) {
            char cell = field[index(r, c)];
            if (cell == 'S') std::cout << 'S' << ' ';  // show ships
            else if (cell == 'X') std::cout << COLOR_RED << 'X' << COLOR_RESET << ' ';
            else if (cell == 'o') std::cout << COLOR_BLUE << 'o' << COLOR_RESET << ' ';
            else std::cout << ". ";
        }
        std::cout << '\n';
    }
}
