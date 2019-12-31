#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "roomHandling.h"
#include "fileParsing.h"
#include "events.h"

Monsters* printRoom(RoomInfo** room, int startY, int startX, int roomNumber)
{
    int rows;
    int cols;
    Monsters* monsterArray;
    monsterArray = malloc(sizeof(Monsters));

    initscr();
    cbreak();
    noecho();
    getmaxyx(stdscr, rows, cols);

    //program exits if the terminal window is not big enough
    if (rows<55) {
        endwin();
        printf("The terminal window is too short. It has to be at least 55 rows, but yours is only %d\n", rows);
        exit(1);
    }

    if (cols<95) {
        endwin();
        printf("The terminal window is too narrow. It has to be at least 95 columns, but yours is only %d\n", cols);
        exit(1);
    }

    //prints the walls and adds the dots for the floor
    for (int i=0; i < room[roomNumber]->height+2; i++){
        mvaddch(startY+i, startX, '|');
        mvaddch(startY+i, startX+room[roomNumber]->width+1, '|');
        }
    for (int i=0; i < room[roomNumber]->width+2; i++){
        mvaddch(startY, startX+i, '-');
        mvaddch(startY+room[roomNumber]->height+1, startX+i, '-');
    }
    for (int i=0; i < room[roomNumber]->height; i++){
        for(int j=0; j < room[roomNumber]->width; j++){
            mvaddch(startY+i+1, startX+j+1, '.');
        }
    }

    //prints the items in their correct spots
    int k = 0;
    int monsterCounter = 0;

    while (room[roomNumber]->itemVal[k] != '\0') {
        int r = rand() % 4;
        if (room[roomNumber]->itemVal[k] == 'p') {
            mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, '!');
        }
        else if (room[roomNumber]->itemVal[k] == 'M') { //stores monster data in a struct
            mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, 'T');
            monsterArray->type[monsterCounter] = 'T';
            monsterArray->health[monsterCounter] = 50;
            monsterArray->attack[monsterCounter] = 5;
            monsterArray->speed[monsterCounter] = 3;
            monsterArray->yPos[monsterCounter] = startY+room[roomNumber]->itemY[k]+1;
            monsterArray->xPos[monsterCounter] = startX+room[roomNumber]->itemX[k]+1;
            monsterArray->status[monsterCounter] = 1;
            monsterCounter++;
        }
        else if (room[roomNumber]->itemVal[k] == 'z') {
            mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, '<');
        }
        else if (room[roomNumber]->itemVal[k] == 'a') {
            mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, '>');
        }
        else if (room[roomNumber]->itemVal[k] == 'g') {
            mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, '*');
        }
        else if (room[roomNumber]->itemVal[k] == 'G') {
            mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, '8');
        }
        else if (room[roomNumber]->itemVal[k] == 'w') {
            mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, ')');
        }
        else if (room[roomNumber]->itemVal[k] == 'W') {
            mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, '(');
        }
        else if (room[roomNumber]->itemVal[k] == 'e') {
            mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, ']');
        }
        else if (room[roomNumber]->itemVal[k] == 'm') { //stores monster data in a struct
            if (r == 0) {
                mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, 'A');
                monsterArray->type[monsterCounter] = 'A';
                monsterArray->health[monsterCounter] = 5;
                monsterArray->attack[monsterCounter] = 1;
                monsterArray->speed[monsterCounter] = 2;
                monsterArray->yPos[monsterCounter] = startY+room[roomNumber]->itemY[k]+1;
                monsterArray->xPos[monsterCounter] = startX+room[roomNumber]->itemX[k]+1;
                monsterArray->status[monsterCounter] = 1;
                monsterCounter++;
            }
            else if (r == 1) {
                mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, 'B');
                monsterArray->type[monsterCounter] = 'B';
                monsterArray->health[monsterCounter] = 2;
                monsterArray->attack[monsterCounter] = 5;
                monsterArray->speed[monsterCounter] = 4;
                monsterArray->yPos[monsterCounter] = startY+room[roomNumber]->itemY[k]+1;
                monsterArray->xPos[monsterCounter] = startX+room[roomNumber]->itemX[k]+1;
                monsterArray->status[monsterCounter] = 1;
                monsterCounter++;
            }
            else if (r == 2) {
                mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, 'S');
                monsterArray->type[monsterCounter] = 'S';
                monsterArray->health[monsterCounter] = 5;
                monsterArray->attack[monsterCounter] = 5;
                monsterArray->speed[monsterCounter] = 4;
                monsterArray->yPos[monsterCounter] = startY+room[roomNumber]->itemY[k]+1;
                monsterArray->xPos[monsterCounter] = startX+room[roomNumber]->itemX[k]+1;
                monsterArray->status[monsterCounter] = 1;
                monsterCounter++;
            }
            else if (r == 3) {
                mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, 'Z');
                monsterArray->type[monsterCounter] = 'Z';
                monsterArray->health[monsterCounter] = 15;
                monsterArray->attack[monsterCounter] = 5;
                monsterArray->speed[monsterCounter] = 2;
                monsterArray->yPos[monsterCounter] = startY+room[roomNumber]->itemY[k]+1;
                monsterArray->xPos[monsterCounter] = startX+room[roomNumber]->itemX[k]+1;
                monsterArray->status[monsterCounter] = 1;
                monsterCounter++;
            }
        }
        else {
            mvaddch(startY+room[roomNumber]->itemY[k]+1, startX+room[roomNumber]->itemX[k]+1, room[roomNumber]->itemVal[k]);
        }
        k++;
    }

    //prints the doors and hallways
    int l = 0;
    while (room[roomNumber]->doorWall[l] != '\0') {

        if (room[roomNumber]->doorWall[l] == 'n'){ //algorithm for if the door is on the north wall
            mvaddch(startY, startX+room[roomNumber]->doorPosition[l]+1, '+');
            mvaddch(startY-1, startX+room[roomNumber]->doorPosition[l]+1, '#');
            mvaddch(startY-2, startX+room[roomNumber]->doorPosition[l]+1, '#');

            if (roomNumber <= 2) {
                for (int i=0; i < ((room[roomNumber]->width)-(room[roomNumber]->doorPosition[l])+3); i++) {
                    mvaddch(startY-2, startX+room[roomNumber]->doorPosition[l]+1+i, '#');
                }
                for (int i=0; i < ((room[roomNumber]->height) + (24-room[roomNumber]->height)); i++) {
                    mvaddch(startY-2+i, startX + room[roomNumber]->width +3, '#');
                }
            }
        }

        else if (room[roomNumber]->doorWall[l] == 's'){ //algorithm for if the door is on the south wall
            mvaddch(startY+room[roomNumber]->height+1, startX+room[roomNumber]->doorPosition[l]+1, '+');

            if (roomNumber <=2) {
               for (int i=0; i < (21-room[roomNumber]->height); i++) {
                   mvaddch(startY+room[roomNumber]->height+2+i, startX+room[roomNumber]->doorPosition[l]+1, '#');
               }
            }

            else if (roomNumber >= 3) {
                mvaddch(startY+room[roomNumber]->height+2, startX+room[roomNumber]->doorPosition[l]+1, '#');
                mvaddch(startY+room[roomNumber]->height+3, startX+room[roomNumber]->doorPosition[l]+1, '#');

                for (int i=0; i < ((room[roomNumber]->width)-(room[roomNumber]->doorPosition[l])+3); i++) {
                    mvaddch(startY+room[roomNumber]->height+3, startX+room[roomNumber]->doorPosition[l]+1+i, '#');
                }
                for (int i=0; i < ((room[roomNumber]->height)+6); i++) {
                    mvaddch(startY+room[roomNumber]->height+3-i, startX + room[roomNumber]->width +3, '#');
                }
            }

        }

        else if (room[roomNumber]->doorWall[l] == 'e'){ //algorithm for if the door is on the east wall
            mvaddch(startY+room[roomNumber]->doorPosition[l]+1, startX+room[roomNumber]->width+1, '+');
            mvaddch(startY+room[roomNumber]->doorPosition[l]+1, startX+room[roomNumber]->width+2, '#');
            mvaddch(startY+room[roomNumber]->doorPosition[l]+1, startX+room[roomNumber]->width+3, '#');

            if (roomNumber <= 2) {
                for (int i=0; i < (22-room[roomNumber]->doorPosition[l]); i++) {
                    mvaddch(startY + room[roomNumber]->doorPosition[l]+1+i, startX + room[roomNumber]->width + 3, '#');
                }
            }

            else if (roomNumber >= 3) {
                for (int i=0; i < (room[roomNumber]->doorPosition[l]+4); i++) {
                    mvaddch(startY + room[roomNumber]->doorPosition[l]+1-i, startX+room[roomNumber]->width+3, '#');
                }
            }
        }

        else if (room[roomNumber]->doorWall[l] == 'w'){ //algorithm for if the door is on the west wall
            mvaddch(startY+room[roomNumber]->doorPosition[l]+1, startX, '+');
            mvaddch(startY+room[roomNumber]->doorPosition[l]+1, startX-1, '#');
            mvaddch(startY+room[roomNumber]->doorPosition[l]+1, startX-2, '#');
            mvaddch(startY+room[roomNumber]->doorPosition[l]+1, startX-3, '#');


            if (roomNumber <= 2) {
                for (int i=0; i < (21-room[roomNumber]->doorPosition[l]); i++) {
                    mvaddch(startY + room[roomNumber]->doorPosition[l]+1+i, startX-3, '#');
                }
            }

            else if (roomNumber >= 3) {
                for (int i=0; i < (room[roomNumber]->doorPosition[l]+4); i++) {
                    mvaddch(startY + room[roomNumber]->doorPosition[l]+1-i, startX-3, '#');
                }
            }


        }
        l++;
    }
    return monsterArray;
}

void printCentralHallway()
{
    for (int j=2; j<=97; j++) {
        mvaddch(27, j, '#');
    }
}

void moveToHeroStart(RoomInfo** room)
{
    //moves the cursor to the hero's starting position
    if (room[0]->heroRoom == 1) {
        move(5+room[0]->heroYPos+1, 5+room[0]->heroXPos+1);
    }
    else if (room[0]->heroRoom == 2) {
        move(5+room[0]->heroYPos+1, 35+room[0]->heroXPos+1);
    }
    else if (room[0]->heroRoom == 3) {
        move(5+room[0]->heroYPos+1, 65+room[0]->heroXPos+1);
    }
    else if (room[0]->heroRoom == 4) {
        move(30+room[0]->heroYPos+1, 5+room[0]->heroXPos+1);
    }
    else if (room[0]->heroRoom == 5) {
        move(30+room[0]->heroYPos+1, 35+room[0]->heroXPos+1);
    }
    else if (room[0]->heroRoom == 6) {
        move(30+room[0]->heroYPos+1, 65+room[0]->heroXPos+1);
    }
}

void gameStart(RoomInfo** room, Monsters** monstersArray) {

    char input;
    int x;
    int y;
    int goldAmount = 0;
    int potionCount = 1;
    int zombieMoveCounter = 0;
    int snakeTrollMoveCounter = 0;

    Inventory heroInventory;
    HeroStatistics heroStats;
    heroStats.health = 50;
    heroStats.attackRating = 5;
    heroInventory.numItems = 0;

    updateStatusBar(heroStats, heroInventory, potionCount);
    input = getch();

    //loops until the user presses q
    while (input != 'q') {
        if (input == 'p') {
            getyx(stdscr, y, x);
            move(1,5);
            clrtoeol();
            if (potionCount > 0) {
                usePotion(&potionCount, &heroStats);
            }
            else {
                potEmpty();
            }
            move(y,x);
        }

        else {
            int goOrNo;
            goOrNo = checkForCollision(input, &goldAmount, &potionCount, &heroInventory);

        //if it's okay to move, then move the hero and cursor
        if (goOrNo == 0) {
            moveHero(input);
        }
        else if (goOrNo == 2) { //monster combat
            int currentY;
            int currentX;
            getyx(stdscr, currentY, currentX);
            if (input == 'w') {
                combat(currentY-1, currentX, monstersArray, &heroStats, goldAmount, heroInventory);
            }
            else if (input == 'a') {
                combat(currentY, currentX-1, monstersArray, &heroStats, goldAmount, heroInventory);
            }
            else if (input == 's') {
                combat(currentY+1, currentX, monstersArray, &heroStats, goldAmount, heroInventory);
            }
            else if (input == 'd') {
                combat(currentY, currentX+1, monstersArray, &heroStats, goldAmount, heroInventory);
            }
        }
     }

    //monster movement
    moveBats(monstersArray);
    moveZombies(monstersArray, zombieMoveCounter);
    moveSnakes(monstersArray, snakeTrollMoveCounter);
    moveTrolls(monstersArray, snakeTrollMoveCounter);
    zombieMoveCounter++;
    snakeTrollMoveCounter++;
    if (zombieMoveCounter == 2) {
        zombieMoveCounter = 0;
    }
    if (snakeTrollMoveCounter == 4) {
        snakeTrollMoveCounter = 0;
    }

    updateStatusBar(heroStats, heroInventory, potionCount);
    input = getch();

    }


    endGame(goldAmount, heroInventory); //ends game after the while loop

}

void usePotion (int* potionCount, HeroStatistics* heroStats) {

    *potionCount = *potionCount - 1;
    heroStats->health = 50;
    potUse();
}

void combat(int monsterY, int monsterX, Monsters** monstersArray, HeroStatistics* heroStats, int gold, Inventory inventory) {
    int room = 0;
    if ((monsterY <= 25) && (monsterX <= 30)) {
        room = 0;
    }
    else if ((monsterY <= 25) && (monsterX >= 35) && (monsterX <= 60)) {
        room = 1;
    }
    else if ((monsterY <= 25) && (monsterX >= 65)) {
        room = 2;
    }
    else if ((monsterY >= 30) && (monsterX <= 30)) {
        room = 3;
    }
    else if ((monsterY >= 30) && (monsterX >= 35) && (monsterX <= 60)) {
        room = 4;
    }
    else if ((monsterY >= 30) && (monsterX >= 65)) {
        room = 5;
    }
    int monsterNumber = 0;
    int j=0;
    while (monstersArray[room]->type[j] != '\0') {
        if ((monstersArray[room]->yPos[j] == monsterY) && (monstersArray[room]->xPos[j] == monsterX)) { //finds which monster number the monster is
            monsterNumber = j;
        }
        j++;
    }

    int r = rand() % 10 + 1;
    if (r > (monstersArray[room]->speed[monsterNumber])) { //hero attacks
        monstersArray[room]->health[monsterNumber] = monstersArray[room]->health[monsterNumber]-heroStats->attackRating;
        giveDamage((heroStats->attackRating));
    }
    else { //monster attacks
        if (monstersArray[room]->type[monsterNumber] == 'A') { //if monster is an aquator
            if (heroStats->attackRating > 0) {
                heroStats->attackRating = heroStats->attackRating - monstersArray[room]->attack[monsterNumber];
                hitByAquator();
            }
            else { //hero is hit by an aquator but attack is already zero
                attackIsZero();
            }
        }
        else { //any monster not an aquator
            heroStats->health = heroStats->health - monstersArray[room]->attack[monsterNumber];
            takeDamage((monstersArray[room]->attack[monsterNumber]));
        }
    }

    if (monstersArray[room]->health[monsterNumber] <= 0) { //if the monster's health is zero or less
        int y;
        int x;
        monstersArray[room]->status[monsterNumber] = 0;
        getyx(stdscr, y, x);
        mvaddch(y, x, '.');
        mvaddch(monstersArray[room]->yPos[monsterNumber], monstersArray[room]->xPos[monsterNumber], '@');
        move(monstersArray[room]->yPos[monsterNumber], monstersArray[room]->xPos[monsterNumber]);
        kill(monstersArray[room]->type[monsterNumber]);
    }

    if (heroStats->health <= 0) { //if the hero dies
        endGame(gold, inventory);
    }
}

void moveBats(Monsters** monstersArray) {

    int goOrNo;
    int heroY;
    int heroX;
    int randomMove;

    getyx(stdscr, heroY, heroX);
    //loops through all of the elements in the 6 monster struct arrays
    for (int i=0; i<6; i++) {
        for (int j=0; j<10; j++) {
            if (monstersArray[i]->type[j] == 'B') {
                if (monstersArray[i]->status[j] == 1) {
                    randomMove = rand() % 4; //the bat will move in a direction specified by a random number between 0 and 3
                    if (randomMove == 0) {
                        goOrNo = monsterCheckForCollision('w', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j]-1, monstersArray[i]->xPos[j], 'B');
                            monstersArray[i]->yPos[j] = monstersArray[i]->yPos[j]-1;
                        }
                    }
                    else if (randomMove == 1) {
                        goOrNo = monsterCheckForCollision('a', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j]-1, 'B');
                            monstersArray[i]->xPos[j] = monstersArray[i]->xPos[j]-1;
                        }
                    }
                    else if (randomMove == 2) {
                        goOrNo = monsterCheckForCollision('s', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j]+1, monstersArray[i]->xPos[j], 'B');
                            monstersArray[i]->yPos[j] = monstersArray[i]->yPos[j]+1;
                        }
                    }
                    else if (randomMove == 3) {
                        goOrNo = monsterCheckForCollision('d', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j]+1, 'B');
                            monstersArray[i]->xPos[j] = monstersArray[i]->xPos[j]+1;
                        }
                    }
                }
            }
        }
    }
    move(heroY, heroX);
}

void moveSnakes(Monsters** monstersArray, int snakeMoveCounter) {

    int goOrNo;
    int heroY;
    int heroX;

    getyx(stdscr, heroY, heroX);

    for (int i=0; i<6; i++) {
        for (int j=0; j<10; j++) {
            if (monstersArray[i]->type[j] == 'S') {
                if (monstersArray[i]->status[j] == 1) {

                    if (snakeMoveCounter == 0) { //first move in the patrol, other 3 are below
                        goOrNo = monsterCheckForCollision('d', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j]+1, 'S');
                            monstersArray[i]->xPos[j] = monstersArray[i]->xPos[j]+1;
                        }
                    }
                    else if (snakeMoveCounter == 1) {
                        goOrNo = monsterCheckForCollision('d', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j]+1, 'S');
                            monstersArray[i]->xPos[j] = monstersArray[i]->xPos[j]+1;
                        }
                    }
                    else if (snakeMoveCounter == 2) {
                        goOrNo = monsterCheckForCollision('a', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j]-1, 'S');
                            monstersArray[i]->xPos[j] = monstersArray[i]->xPos[j]-1;
                        }
                    }
                    else if (snakeMoveCounter == 3) {
                        goOrNo = monsterCheckForCollision('a', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j]-1, 'S');
                            monstersArray[i]->xPos[j] = monstersArray[i]->xPos[j]-1;
                        }
                    }
                }
            }
        }
    }
    move(heroY, heroX);
}


void moveZombies(Monsters** monstersArray, int zombieMoveCounter) {

    int goOrNo;
    int heroY;
    int heroX;

    getyx(stdscr, heroY, heroX);

    for (int i=0; i<6; i++) {
        for (int j=0; j<10; j++) {
            if (monstersArray[i]->type[j] == 'Z') {
                if (monstersArray[i]->status[j] == 1) {
                    if (zombieMoveCounter == 0) {
                        goOrNo = monsterCheckForCollision('w', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j]-1, monstersArray[i]->xPos[j], 'Z');
                            monstersArray[i]->yPos[j] = monstersArray[i]->yPos[j] - 1;
                        }
                    }
                    else if (zombieMoveCounter == 1) {
                        goOrNo = monsterCheckForCollision('s', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j]+1, monstersArray[i]->xPos[j], 'Z');
                            monstersArray[i]->yPos[j] = monstersArray[i]->yPos[j] + 1;
                        }
                    }
                }
            }
        }
    }
    move(heroY, heroX);
}

void moveTrolls(Monsters** monstersArray, int trollMoveCounter) {
   int goOrNo;
    int heroY;
    int heroX;

    getyx(stdscr, heroY, heroX);

    for (int i=0; i<6; i++) {
        for (int j=0; j<10; j++) {
            if (monstersArray[i]->type[j] == 'T') {
                if (monstersArray[i]->status[j] == 1) {

                    if (trollMoveCounter == 0) {
                        goOrNo = monsterCheckForCollision('w', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j]-1, monstersArray[i]->xPos[j], 'T');
                            monstersArray[i]->yPos[j] = monstersArray[i]->yPos[j]-1;
                        }
                    }
                    else if (trollMoveCounter == 1) {
                        goOrNo = monsterCheckForCollision('d', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j]+1, 'T');
                            monstersArray[i]->xPos[j] = monstersArray[i]->xPos[j]+1;
                        }
                    }
                    else if (trollMoveCounter == 2) {
                        goOrNo = monsterCheckForCollision('s', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j]+1, monstersArray[i]->xPos[j], 'T');
                            monstersArray[i]->yPos[j] = monstersArray[i]->yPos[j]+1;
                        }
                    }
                    else if (trollMoveCounter == 3) {
                        goOrNo = monsterCheckForCollision('a', monstersArray, i, j);
                        if (goOrNo == 0) {
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j], '.');
                            mvaddch(monstersArray[i]->yPos[j], monstersArray[i]->xPos[j]-1, 'T');
                            monstersArray[i]->xPos[j] = monstersArray[i]->xPos[j]-1;
                        }
                    }
                }
            }
        }
    }
    move(heroY, heroX);
}

int monsterCheckForCollision(char in, Monsters** monstersArray, int room, int monsterNumber) {

    int y;
    int x;
    char nextSpot;

    move(monstersArray[room]->yPos[monsterNumber], monstersArray[room]->xPos[monsterNumber]);
    getyx(stdscr, y ,x);

    switch(in){
        case 'w':
            y--;
            break;

        case 's':
            y++;
            break;

        case 'a':
            x--;
            break;

        case 'd':
            x++;
            break;

        default:
            break;
    }

    nextSpot = mvinch(y,x);

    if (nextSpot == '.') { //the monster can only move if the next spot is a dot
        return 0;
    }
    else {
        return 1;
    }
}


void updateStatusBar(HeroStatistics heroStats, Inventory heroInventory, int potionCount) {

    int y;
    int x;

    getyx(stdscr, y, x);
    move(53, 5);
    clrtoeol();
    //prints the status bar and then moves the cursor back to the hero's position
    printw("Health: %d  Potions: %d  Attack: %d  Inv: %d/5", heroStats.health, potionCount, heroStats.attackRating, heroInventory.numItems);
    move(y,x);
}

void moveHero(char in) {

    int y;
    int x;
    int oldY;
    int oldX;

    getyx(stdscr, y, x);
    getyx(stdscr, oldY, oldX);

    //if the hero is currently standing on a door, print a door on the current position then move
    if (((mvinch(y+1,x)== '|') && (mvinch(y-1,x)== '|')) || ((mvinch(y,x-1)== '-') && (mvinch(y,x+1)== '-')) ||
    ((mvinch(y+1,x) == '|') && (mvinch(y-1,x) == '-')) || ((mvinch(y+1,x) == '-') && (mvinch(y-1,x) == '|'))) {
        switch(in){
            case 'w':
                y--;
                mvaddch(y,x,'@');
                mvaddch(oldY, oldX, '+');
                move(y,x);
                break;

            case 'a':
                x--;
                mvaddch(y,x,'@');
                mvaddch(oldY, oldX, '+');
                move(y,x);
                break;

            case 's':
                y++;
                mvaddch(y,x,'@');
                mvaddch(oldY, oldX, '+');
                move(y,x);
                break;

            case 'd':
                x++;
                mvaddch(y,x,'@');
                mvaddch(oldY, oldX, '+');
                move(y,x);
                break;

            default:
                mvaddch(y,x,'@');
                move(y,x);
                break;
        }
    }

    //don't ask LOL these are the scenarios that indicate the hero is on a hallway spot
    else if (((mvinch(y+1,x)== '#') && (mvinch(y-1,x) == '#')) || ((mvinch(y,x+1)== '#') && (mvinch(y,x-1) == '#')) || ((mvinch(y+1,x)== '+')
    && (mvinch(y-1,x) == '#')) || ((mvinch(y+1,x)== '#') && (mvinch(y-1,x) == '+')) || ((mvinch(y,x+1)== '+') && (mvinch(y,x-1) == '#')) ||
    ((mvinch(y,x+1)== '#') && (mvinch(y,x-1) == '+')) || ((mvinch(y+1,x)== ' ') && (mvinch(y-1,x) == '#')) || ((mvinch(y+1,x)== '#')
    && (mvinch(y-1,x) == ' ')) || ((mvinch(y,x+1)== ' ') && (mvinch(y,x-1) == '#')) || ((mvinch(y,x+1)== '#') && (mvinch(y,x-1) == ' '))) {
        switch(in){
            case 'w':
                y--;
                mvaddch(y,x,'@');
                mvaddch(oldY, oldX, '#');
                move(y,x);
                break;

            case 'a':
                x--;
                mvaddch(y,x,'@');
                mvaddch(oldY, oldX, '#');
                move(y,x);
                break;

            case 's':
                y++;
                mvaddch(y,x,'@');
                mvaddch(oldY, oldX, '#');
                move(y,x);
                break;

            case 'd':
                x++;
                mvaddch(y,x,'@');
                mvaddch(oldY, oldX, '#');
                move(y,x);
                break;

            default:
                mvaddch(y,x,'@');
                move(y,x);
                break;
        }
    }

    else { //normal movement (ie. in a room)
        switch(in){
            case 'w':
                y--;
                mvaddch(y,x,'@');
                mvaddch(oldY, oldX, '.');
                move(y,x);
                break;

            case 'a':
                x--;
                mvaddch(y,x,'@');
                mvaddch(oldY, oldX, '.');
                move(y,x);
                break;

            case 's':
                y++;
                mvaddch(y,x,'@');
                mvaddch(oldY, oldX, '.');
                move(y,x);
                break;

            case 'd':
                x++;
                mvaddch(y,x,'@');
                mvaddch(oldY, oldX, '.');
                move(y,x);
                break;

            default:
                mvaddch(y,x,'@');
                move(y,x);
                break;
        }
    }

}

int checkForCollision(char in, int* gold, int* potionCount, Inventory* heroInventory) {

    int y;
    int x;
    int oldY;
    int oldX;
    char nextSpot;

    getyx(stdscr, y ,x);
    getyx(stdscr, oldY, oldX);

    switch(in){
        case 'w':
            y--;
            move(1,5);
            clrtoeol();
            move(oldY,oldX);
            break;

        case 's':
            y++;
            move(1,5);
            clrtoeol();
            move(oldY,oldX);
            break;

        case 'a':
            x--;
            move(1,5);
            clrtoeol();
            move(oldY,oldX);
            break;

        case 'd':
            x++;
            move(1,5);
            clrtoeol();
            move(oldY,oldX);
            break;

        default:
            break;
    }

    nextSpot = mvinch(y,x);
    move(oldY,oldX);

    //returns a different integer value based on the next spot
    if ((nextSpot == 'T') || (nextSpot == 'A') || (nextSpot == 'B') || (nextSpot == 'S') || (nextSpot == 'Z')) {
        return 2;
    }

    else if ((nextSpot == '-') || (nextSpot == '|')) {
        return 1;
    }

    else if (nextSpot == '!') {
        *potionCount = *potionCount + 1;
        pickup('!');
        return 0;
    }

    else if ((nextSpot == '<') || (nextSpot == '>')) {
        endGame(*gold, *heroInventory);
        exit(1);
    }

    else if (nextSpot == '#') {
        return 0;
    }

    else if (nextSpot == ' ') {
        return 1;
    }

    else if (nextSpot == '*') {
        *gold = *gold + (rand() % 50 + 1);
        pickup('*');
        return 0;
    }

    else if (nextSpot == '8') {
        *gold = *gold + (rand() % 200 + 51);
        pickup('8');
        return 0;
    }

    else if (nextSpot == '+') {
        door();
        return 0;
    }
    //adds the appropriate item to the inventory if the next spot is an item
    else if ((nextSpot == ')') || (nextSpot == '(') || (nextSpot == ']')) {
        if (heroInventory->numItems < 5) {
            heroInventory->numItems++;
            if (nextSpot == ')') {
                heroInventory->itemLabel[heroInventory->numItems-1] = ')';
                heroInventory->itemStat[heroInventory->numItems-1] = rand() % 9 + 1;
                pickup(nextSpot);
            }
            else if (nextSpot == '(') {
                heroInventory->itemLabel[heroInventory->numItems-1] = '(';
                heroInventory->itemStat[heroInventory->numItems-1] = rand() % 5 + 10;
                pickup(nextSpot);
            }
            else if (nextSpot == ']') {
                heroInventory->itemLabel[heroInventory->numItems-1] = ']';
                heroInventory->itemStat[heroInventory->numItems-1] = rand() % 21;
                pickup(nextSpot);
            }
        }
        else {
            bagFull(nextSpot);
         }

        return 0;
    }

    else {
        return 0;
    }

}

void endGame(int gold, Inventory heroInventory) {
    //prints a message about the gold earned and the ending inventory and then closes up ncurses
    erase();
    mvprintw(3, 3, "The game is over! You got %d gold.", gold);
    mvprintw(5, 3, "Ending inventory: ");
    for (int i=0; i < heroInventory.numItems; i++) {
        if (heroInventory.itemLabel[i] == ')') {
            mvprintw(6+i, 3, "Common weapon with an attack rating of: %d", heroInventory.itemStat[i]);
        }
        if (heroInventory.itemLabel[i] == '(') {
            mvprintw(6+i, 3, "Rare weapon with an attack rating of: %d", heroInventory.itemStat[i]);
        }
        if (heroInventory.itemLabel[i] == ']') {
            mvprintw(6+i, 3, "Equipment with a defense rating of: %d", heroInventory.itemStat[i]);
        }
    }

    mvprintw(13, 3, "Press any key to quit.");
    getch();
    endwin();
    exit(0);
}

void freeRoom(RoomInfo** room, int numRooms) {
    //frees the room struct pointer array
    for (int i=0; i<numRooms; i++) {
        int j=0;
        while (*room[i]->other[j] != '\0') {
            free(room[i]->other[j]);
            j++;
        }
    }

    for (int i=0; i<numRooms; i++) {
        free(room[i]);
    }

    free(room);

}

void freeMonsters(Monsters** monstersArray) {
    //frees the monster struct pointer array
    for (int i=0; i<6; i++){
        free(monstersArray[i]);
    }
    free(monstersArray);
}
