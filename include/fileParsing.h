#ifndef __KKUA_fileParsing__
#define __KKUA_fileParsing__

struct roomInfo {
    int width;
    int height;
    char* other[10];
    int itemY[10];
    int itemX[10];
    char itemVal[10];
    char doorWall[10];
    int doorPosition[10];
    int heroRoom;
    int heroYPos;
    int heroXPos;
};

typedef struct roomInfo RoomInfo;

/**
- openThisFile
- Opens a specified file and prints whether or not the open was successful.
- IN: Takes in the name of the file to be opened (fileToOpen) and the
      action to be performed after opening the file (action).
- OUT: Returns the pointer to the opened file to be assigned to a variable
       in main.
- ERROR: If an nonexisting file is attempted to be opened, the function will
         exit the program.
**/
FILE* openThisFile(char *fileToOpen, char *action);


/**
- parseRoomFile
- Parses the room file and stores the information in a room struct pointer array.
- IN: Takes in a pointer to an opened room file.
- OUT: Returns the room struct pointer array.
- ERROR: Not following the A2 specifications (ie. >150 characters per line).

**/
RoomInfo** parseRoomFile(FILE* file);


#endif
