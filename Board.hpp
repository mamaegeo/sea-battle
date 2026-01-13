#pragma once
#include <vector>

/**
 * Ship represents a single ship on the board.
 * Stores the coordinates of all cells the ship occupies.
 */

struct Ship {
    std::vector<std::pair<int,int>> cells; // coordinates of this ship

    /**
     * Check if the ship is fully sunk.
     */
    bool isSunk(const std::vector<char>& field, int width) const {
        for (auto [r, c] : cells)
            if (field[r*width + c] == 'S') return false; // at least one part still intact
        return true;
    }
};

/**
 * Board class: handles the game board, ships, and shooting logic.
 */

class Board {
public:
    /**
     * Create a Board with specified dimensions and number of ships.
     * Ships are randomly placed with no overlap and a 1-cell buffer.
     */
    Board(int width, int height, int numShips = 3);
    
    /** Draw the current board state to the console */
    void draw() const;

    /**
     * Shoot at a given cell.
     */
    bool shoot(int row, int col);

    /** Check if all ships have been sunk */
    bool allShipsSunk() const;

    /** Check if all ships have been sunk */
    int shipsRemaining() const;

    /** Draw the board with ship positions visible (debug mode) */
    void debugDrawShips() const;

private:
    int w, h; // // board dimensions
    std::vector<char> field; // '.' = empty, 'S' = ship, 'X' = hit, 'o' = miss
    std::vector<Ship> ships; // track ships individually
    int lastRow{-1}, lastCol{-1}; // last shot coordinates

    /** Convert (row, col) to linear index for the field vector */
    int index(int row, int col) const;
};
