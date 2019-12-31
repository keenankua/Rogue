#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "fileParsing.h"
#include "roomHandling.h"

FILE* openThisFile(char *fileToOpen, char *action)
{
    FILE* filePtr = NULL;

    filePtr = fopen(fileToOpen, action); // Opens the file name passed in for t$

    if (filePtr == NULL) // Error case if the file failed to open
    {
        printf("File failed to open properly!\n");
        exit(1); // Exit the program
    }

    else // If the file opened
    {
        printf("File successfully opened!\n");
    }
    return filePtr;
}

RoomInfo** parseRoomFile(FILE* roomFile)
{
    char fileText[150];
    RoomInfo** room;
    int roomNumber = 0;
    int spaceCounterArray[6];
//    char* ptr;

    room = malloc(sizeof(RoomInfo*)*6); //malloc for 6 RoomInfo pointers

    for (int i=0; i<6; i++) {
        room[i] = malloc(sizeof(RoomInfo)); //malloc for 6 RoomInfo variables in an array
    }

    while(fgets(fileText, 150, roomFile) != NULL)
    {
        int spaceCounter = 0;
        int length = strlen(fileText);
        char* ptr;

        //counts number of spaces
        for(int i=0; i<=length; i++){
            if (fileText[i] == ' ') {
                spaceCounter++;
            }
        }
        //parses the room dimensions and stores them in the struct variable
        ptr = strtok(fileText,"X");
        room[roomNumber]->height = atoi(ptr);
        ptr = strtok(NULL, " ");
        room[roomNumber]->width = atoi(ptr);

        spaceCounterArray[roomNumber] = spaceCounter;

        //dynamically mallocs for the array of strings in the struct
        int j = 0;
        ptr = strtok (NULL, " \n");
        while(ptr != NULL) {
            room[roomNumber]->other[j] = malloc(strlen(ptr) + 1);
            strcpy(room[roomNumber]->other[j], ptr);
            j++;
            ptr = strtok (NULL, " \n");
        }
     roomNumber++;
     }

//parses for the room's items and doors
char* dummyPtr;
char* dummyPtr2;
char* dummyPtr3;
for (int k=0; k<roomNumber; k++) {

    int doorCounter = 0;
    int itemCounter = 0;

    for (int l=0; l<spaceCounterArray[k]; l++) { //loops for the number of things after the dimensions
         //handles parsing for the doors
         if (room[k]->other[l][0] == 'd'){

             room[k]->doorWall[doorCounter] = room[k]->other[l][1];
             dummyPtr = strtok(room[k]->other[l], "nsew");
             if(dummyPtr) {
             }
             dummyPtr = strtok(NULL, "\0");
             room[k]->doorPosition[doorCounter] = atoi(dummyPtr);
             doorCounter++;
         }
         //handles parsing for the hero
         else if (room[k]->other[l][0] == 'h') {
             room[k]->itemVal[itemCounter] = '@';
             room[0]->heroRoom = k+1;
             dummyPtr = strtok(room[k]->other[l], "hzagGwWmeMp");
             room[k]->itemY[itemCounter] = strtol(dummyPtr, &dummyPtr2, 10);
             room[0]->heroYPos = room[k]->itemY[itemCounter];
             dummyPtr3 = strtok(dummyPtr2, ",");

             room[k]->itemX[itemCounter] = strtol(dummyPtr3, NULL, 10);
             room[0]->heroXPos = room[k]->itemX[itemCounter];

             itemCounter++;
         }
         //handles parsing for all items
         else {
             room[k]->itemVal[itemCounter] = room[k]->other[l][0];
             dummyPtr = strtok(room[k]->other[l], "hzagGwWmeMp");
             room[k]->itemY[itemCounter] = strtol(dummyPtr, &dummyPtr2, 10);
             dummyPtr3 = strtok(dummyPtr2, ",");

             room[k]->itemX[itemCounter] = strtol(dummyPtr3, NULL, 10);

             itemCounter++;
            }
        }
    }
    return room;

}
