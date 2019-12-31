#ifndef __KKUA_roomHandling__
#define __KKUA_roomHandling__
#include "fileParsing.h"

//Struct to hold hero inventory data
struct inventory {

    char itemLabel[5];
    int itemStat[5];
    int numItems;

};

typedef struct inventory Inventory;

//Struct to hold the hero's stats
struct heroStatistics {

    int health;
    int attackRating;

};

typedef struct heroStatistics HeroStatistics;

//Struct to hold all the monster data
struct monsters {

    char type[10];
    int health[10];
    int attack[10];
    int speed[10];
    int yPos[10];
    int xPos[10];
    int status[10];

};

typedef struct monsters Monsters;

/**
- printRoom
- Prints out a room based on the starting position and room number
-IN: Takes in the room struct pointer array, starting coordinates, and a room number
-OUT: The monster struct with data filled in
-ERROR: --
**/
Monsters* printRoom(RoomInfo** room, int startY, int startX, int roomNumber);

/**
- printCentralHallway
- Prints the long horizontal hallway in the middle of the rooms
-IN: --
OUT: --
ERROR: --
**/
void printCentralHallway();

/**
- moveToHeroStart
- Moves the cursor to the position that the hero starts at at the beginning of the game
-IN: The room struct pointer array, which contains the coordinates and room the hero starts in
-OUT: --
-ERROR: --
**/
void moveToHeroStart(RoomInfo** room);

/**
- usePotion
- Uses an available potion to refill the hero's health and subtracts from the potion count
-IN: A pointer to the potion count and the hero stats struct
OUT: --
ERROR: --
**/
void usePotion (int* potionCount, HeroStatistics* heroStats);

/**
- combat
- Handles the combat between hero and monster
-IN: Monster's y and x ordinates, monster data structs, hero stats struct, gold count, and inventory struct
OUT: --
ERROR: --
**/
void combat(int monsterY, int monsterX, Monsters** monstersArray, HeroStatistics* heroStats, int gold, Inventory inventory);

/**
- moveBats
- Moves all of the bats in a random direction each turn
-IN: The monster struct pointer array
OUT: --
ERROR: --
**/
void moveBats(Monsters** monstersArray);

/**
- moveSnakes
- Moves all of the snakes in their proper patrol
-IN: The monster struct pointer array and the turn counter
OUT: --
ERROR: --
**/
void moveSnakes(Monsters** monstersArray, int snakeMoveCounter);

/**
- moveZombies
- Moves all of the zombies in their proper patrol
-IN: The monster struct pointer array and the turn counter
OUT: --
ERROR: --
**/
void moveZombies(Monsters** monstersArray, int zombieMoveCounter);

/**
- moveTrolls
- Moves all of the trolls in their proper patrol
-IN: The monster struct pointer array and the turn counter
OUT: --
ERROR: --
**/
void moveTrolls(Monsters** monstersArray, int trollMoveCounter);

/**
- monsterCheckForCollision
- Checks if the monster is allowed to move without bumping into anything
-IN: The direction to move, the monster data, the room the monster is in, the monster number for that room
OUT: Returns an integer that is used to indicate if the monster can move or not
ERROR: --
**/
int monsterCheckForCollision (char in, Monsters** monstersArray, int room, int monsterNumber);

/**
- updateStatusBar
- Refreshes the status bar at the bottom every keypress
-IN: The hero stats data, inventory data, and potion count
OUT: --
ERROR: --
**/
void updateStatusBar(HeroStatistics heroStats, Inventory heroInventory, int potionCount);

/**
- gameStart
- Executes the game loop
-IN: Takes in the room struct pointer array and monster struct pointer array
-OUT: --
-ERROR: --
**/
void gameStart(RoomInfo** room, Monsters** monstersArray);

/**
- moveHero
- Moves the hero based on user input and collision detection
-IN: Takes in a user keypress
-OUT: --
-ERROR: --
**/
void moveHero(char in);

/**
- checkForCollision
- Checks if the next spot based on user input is okay to walk on or not
-IN: Takes in the user keypress and gold pointer
-OUT: Returns an integer based on what is in the next spot according to the user keypress
-ERROR: Unspecified items will be treated as walkable-on
**/
int checkForCollision(char in, int* gold, int* potionCount, Inventory* heroInventory);

/**
- endGame
- Ends ncurses and displays a message including amount of gold picked up and the ending inventory
-IN: Amount of gold picked up and the hero inventory data
-OUT: --
-ERROR: --
**/
void endGame(int gold, Inventory heroInventory);

/**
- freeRoom
- Frees the malloc'd rooms based on number of rooms
-IN: The malloc'd room to be freed and the number of rooms (6)
-OUT: --
-ERROR: --
**/
void freeRoom(RoomInfo** room, int numRooms);

/**
- freeMonsters
- Frees the malloc'd monster data
-IN: The monster pointer array to be freed
-OUT: --
-ERROR: --
**/
void freeMonsters(Monsters** monstersArray);

#endif

