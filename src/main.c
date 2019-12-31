#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileParsing.h"
#include "roomHandling.h"
#include <ncurses.h>
#include <time.h>

/**
- main
- Reads a file with room details, parses it accordingly, then prints the rooms and enters a game loop
- IN: Takes in the name of the file to be parsed
- OUT: Returns 0 on a successful run, otherwise may exit early
- ERROR: Changes not specified in the A3 specifications may cause the program to behave improperly
**/
int main(int argc, char* argv[])
{

    RoomInfo** room;
    Monsters** monstersArray = malloc(sizeof(Monsters*)*6);
    FILE* roomFile = NULL;

    srand(time(NULL));

    roomFile = openThisFile(argv[1], "r");
    room = parseRoomFile(roomFile);
    fclose(roomFile);

    monstersArray[0] = printRoom(room, 5, 5, 0);
    monstersArray[1] = printRoom(room, 5, 35, 1);
    monstersArray[2] = printRoom(room, 5, 65, 2);
    monstersArray[3] = printRoom(room, 30, 5, 3);
    monstersArray[4] = printRoom(room, 30, 35, 4);
    monstersArray[5] = printRoom(room, 30, 65, 5);

    printCentralHallway();

    moveToHeroStart(room);
    gameStart(room, monstersArray);

    freeRoom(room, 6);
    freeMonsters(monstersArray);

    return 0;
}
