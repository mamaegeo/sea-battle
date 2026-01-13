# A single player Sea Battle game in C++

<img src="https://gitlab.fel.cvut.cz/mamaegeo/sea-battle/-/raw/main/game_img.png?ref_type=heads" alt="GameImage" width="400" height="250">

## Task



Implement a single-player Battleship (Sea Battle) game played in the terminal.



The player attempts to sink all hidden ships placed randomly on a rectangular board.



The player repeatedly enters coordinates to shoot at the board.

The program evaluates each shot (hit or miss), updates the game state, and displays the current board in the terminal.



The game ends when:



all ships are sunk (win), or



the maximum number of attempts is reached (lose), or



the player quits the game manually.



## Description of Used Algorithms



### Random Ship Placement



Ships are placed randomly on the game board using a pseudo-random number generator (std::mt19937).

Each ship is assigned:



a random starting position,



a random orientation (horizontal or vertical),



a random length in the range 2–4.



Before placing a ship, the algorithm checks:



board boundaries,



overlap with existing ships,



a one-cell buffer around ships to prevent touching.



If placement is invalid, a new position is generated.





### Shooting Evaluation



When the player shoots at a coordinate:



the position is checked for validity,



already used cells are ignored,



hits are marked as 'X',



misses are marked as 'o'.



The algorithm immediately updates the board state and returns whether the shot was a hit or miss.



### Win / Lose Detection



A win occurs when all ships are fully destroyed.



A loss occurs when the maximum number of allowed attempts is reached.



Ship destruction is detected by checking whether all cells of a ship have been hit.



### Program Structure and Class Description

#### Ship



Represents a single ship on the board.



Stores coordinates of all ship cells.



Method ```isSunk()``` checks whether all parts of the ship have been hit.



#### Board



Handles the game board and ship logic.



Randomly places ships.



Processes player shots.



Tracks hits, misses, and remaining ships.



Renders the board to the terminal.



Main methods:



```shoot(row, col)```



```draw()```



```allShipsSunk()```



```shipsRemaining()```



#### Game



Controls the main game loop and threading.



Manages input, rendering, and timing threads.



Synchronizes threads using mutexes and condition variables.



Displays game messages and statistics.



Main methods:



```run()```



```printStats()```



#### ArgParser



Processes command-line arguments.



Parses board size, ship count, difficulty, and help flag.



Validates input ranges.



Implements the mandatory --help switch.



## Program compilation and run



### Compilation



```

mkdir build

cd build

cmake ..

make

```



The game is launched from the command line.



Supported parameters:



```-w, --width ``` – width of the game board



```-h, --height``` – height of the game board



```-s, --ships``` – number of ships



```--difficulty``` – predefined difficulty level



0 – Easy



1 – Normal



2 – Hard



```--help``` – display help and exit (mandatory switch)



If no parameters are provided, the program starts in interactive mode, where the player selects the difficulty manually.



Difficulty presets:

Difficulty	Board Size	Ships	Max Attempts

Easy	6 × 6	4	20

Normal	8 × 8	5	34

Hard	10 × 10	7	50



Example executions:



```

./Battleship

./Battleship --help

./Battleship --difficulty 1

./Battleship --width 7 --height 6 --ships 4

./Battleship -w 8 -h 8 -s 5

```



## Hanlding the program



After starting the game, the board is displayed in the terminal.

Hidden ships are not visible to the player.



The game continuously redraws the board and prints status messages such as:



hit / miss,



number of ships remaining,



number of attempts used.



Zadávání souřadnic



The player enters coordinates as two integers separated by a space:



```row column```





Rows and columns are zero-based (starting from 0)



Example:



```2 3```





This shoots at row 2, column 3.



## Ending the program



The game automatically ends when:



all ships are sunk (victory),



the maximum number of attempts is reached (defeat).



The game can be terminated at any time by entering:



```q```





After the game ends, final statistics are printed:



total attempts,



number of hits,



number of misses,



shooting accuracy.



## Testing of program



### Shooting logic (hit / miss)



#### Test 1 – Ship Hit



##### Input:



```2 3```





##### Precondition:



A ship occupies position (2,3).



##### Expected Result:



Cell (2,3) is marked with X



Console output:



```Hit!```





The hit counter (hits) is incremented by 1



#### Test 2 – Missed Shot



##### Input:



```0 0```





##### Precondition:



No ship is located at position (0,0).



##### Expected Result:



Cell (0,0) is marked with o



Console output:



```Miss!```



The miss counter (misses) is incremented by 1



#### Test 3 – Repeated Shot on a Hit Cell



##### Input:



```

2 3

2 3

```





##### Precondition:



The first shot results in a hit (X).



##### Expected Result:



The second shot is ignored



The board state remains unchanged



Attempt counter is not incremented







##### Test 4 – Repeated Shot on a Missed Cell



###### Input:



```

0 0

0 0

```



###### Expected Result:



The second shot is ignored



The cell remains marked as o



Additional attempt is counted



##### Test 5 – Mixed Hits and Misses



###### Input:



```

1 1

4 2

1 2

```



###### Expected Result:



Each shot is evaluated correctly as either hit or miss



The board visualization reflects all shots



Console messages match the game state



##### Test 6 – Winning by Sinking All Ships



##### Input:



(shots hitting all ship cells)





##### Expected Result:



After the final hit, the console displays:



You win!





The running flag is set to false



The game terminates correctly



##### Test 7 – Invalid Input Handling



Input:



a b





##### Expected Result:



No shot is executed



Console output:



Invalid input! Enter row and col separated by space.





### All Ships Sunk Detection



#### Test 1 – Single Ship Not Fully Hit



##### Input:



```2 2```





##### Precondition:



A ship of length ≥ 2 occupies multiple cells.



Only one cell of the ship is hit.



##### Expected Result:



The ship is not considered sunk



The Ships remaining counter did not go down



allShipsSunk() returns false



The game continues



#### Test 2 – Single Ship Fully Sunk



##### Input:



```

2 2

2 3

```

##### Precondition:



A ship of length 2 occupies cells (2,2) and (2,3).



##### Expected Result:



Both ship cells are marked with X



The ship is considered sunk



If no other ships exist, allShipsSunk() returns true



The Ships remaining counter went down



The game continues



#### Test 3 – Multiple Ships, One Remaining



##### Input:



```

(hit all cells of ship A)

(hit some cells of ship B)

```



##### Expected Result:



Ship A is sunk



Ship B is not sunk



allShipsSunk() returns false



Game does not end







#### Test 4 – All Ships Sunk



##### Input:



```

(hit all cells of all ships)

```



##### Expected Result:



All ships return isSunk() == true



allShipsSunk() returns true



Console output:



```

You win!

```



Game loop terminates correctly



#### Test 5 – Verification Using Debug Mode



#### Method:



Enable debugDrawShips() during testing



Expected Result:



Ship positions are visible



Ship sinking logic matches visible ship state



No false positives or missed ships





### Maximum Attempts / Lose Condition



#### Test 1 – Attempts Counter Increases Correctly



##### Input:



```

0 0

0 1

0 2

```



##### Expected Result:



Each valid shot increases the attempts counter by 1



Hits and misses are both counted as attempts



Display updates correctly:



Attempts: 3 / maxAttempts



#### Test 2 – Misses Also Count as Attempts



##### Input:



```

(empty cell)

```



##### Expected Result:



Shot is marked as miss (o)



attempts increases by 1



misses counter increases



No special behavior compared to a hit



#### Test 3 – Reaching Maximum Attempts



##### Input:



```

(20 valid shots)

```



\##### Expected Result:



On the 20th attempt:



attempts == maxAttempts



Game immediately ends



Console output:

```

You lose! Maximum attempts reached.

```





\#### Test 4 – Win Before Maximum Attempts



\##### Scenario:



All ships are sunk



attempts < maxAttempts



\##### Expected Result:



Game ends immediately with win message



Maximum attempts condition is not triggered



Output:



```

You win! Total attempts: X

```



\#### Test 5 – Statistics After Losing



\##### Scenario:



Player loses due to maximum attempts



\##### Expected Result:



Game statistics are still printed:



```

--- Game statistics ---

Attempts: X

Hits:     Y

Misses:   Z

Accuracy: N%

```



### CLI Parameters \& Difficulty Parsing



#### Test 1 – Help Argument 



##### Input:



```

./Battleship --help

```



##### Expected Result:



Program prints help message



Description of all supported arguments is shown



Program terminates without starting the game



Exit code: 0



#### Test 2 – Difficulty Easy



##### Input:



```

./Battleship --difficulty 0

```



##### Expected Result:



Difficulty set to Easy



Game settings:



Board size: 6 x 6



Ships: 4



Maximum attempts: 20



Game starts immediately without interactive menu



#### Test 3 – Difficulty Normal



##### Input:



```

./Battleship --difficulty 1

```



##### Expected Result:



Difficulty set to Normal



Game settings:



Board size: 8 x 8



Ships: 5



Maximum attempts: 34





#### Test 4 – Difficulty Hard



##### Input:



```

./Battleship --difficulty 2

```



##### Expected Result:



Difficulty set to Hard



Game settings:



Board size: 10 x 10



Ships: 7



Maximum attempts: 50



#### Test 5 – Custom Board Size and Ships



##### Input:



```

./Battleship --width 7 --height 6 --ships 4

```



##### Expected Result:



Custom values are used



Difficulty is ignored



Game settings:



Board size: 7 x 6



Ships: 4



Maximum attempts calculated automatically:



maxAttempts = width \* height \* 3 / 4



#### Test 6 – Priority: Difficulty vs Custom Arguments



##### Input:



```

./Battleship --difficulty 1 --width 10 --height 10 --ships 8

```



##### Expected Result:



Difficulty takes priority



Custom width/height/ships are ignored



Game settings correspond to Normal difficulty



8 x 8, 5 ships, 34 attempts



#### Test 7 – Invalid Difficulty Value



##### Input:



```

./Battleship --difficulty 5

```



##### Expected Result:



Invalid value is detected by ArgParser



Either:



Argument is ignored and interactive menu is shown

or



Program reports invalid argument (depending on implementation)



Program does not crash



#### Test 8 – Invalid Width / Height / Ships



##### Input:



```

./Battleship --width 2 --height 100 --ships -1

```



##### Expected Result:



Values are clamped or rejected based on validation rules



Program falls back to defaults



No undefined behavior or crash



#### Test 9 – No Arguments (Interactive Mode)



##### Input:



```

./Battleship

```



##### Expected Result:



Interactive difficulty selection menu is shown:



1 - Easy

2 - Normal

3 - Hard





User input determines game settings





## Used Sources



C++ reference



CMake docs



AI assistance for syntax and documentation



## Documentation written for commit: `bfffbd6c`



