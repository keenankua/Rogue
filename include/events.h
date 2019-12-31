#ifndef __KKUA_events__
#define __KKUA_events__

/**
- pickup
- Displays a notification when an item is picked up
-IN: The item picked up
OUT: --
ERROR: --
**/
void pickup(char item);

/**
- bagfull
- Displays a notification if the inventory is full and the hero tries to pick up an item
-IN: --
OUT: --
ERROR: --
**/
void bagFull();

/**
- takeDamage
- Displays a notification if the user takes damage
-IN: The monster's attack
OUT: --
ERROR: --
**/
void takeDamage(int monsterAttack);

/**
- giveDamage
- Displays a notification if the hero attacks a monster
-IN: The hero's attack stat
OUT: --
ERROR: --
**/
void giveDamage(int attackRating);

/**
- kill
- Displays a notification if the hero kills a monster
-IN: The monster type
OUT: --
ERROR: --
**/
void kill(char monsterType);

/**
- hitByAquator
- Displays a notification if the hero is hit by an aquator
-IN: --
OUT: --
ERROR: --
**/
void hitByAquator();

/**
- attackIsZero
- Displays a notification if the hero's attack tries to fall below zero
-IN: --
OUT: --
ERROR: --
**/
void attackIsZero();

/**
- door
- Displays a notification if the hero steps on a door
-IN: --
OUT: --
ERROR: --
**/
void door();

/**
- potUse
- Displays a notification if the user uses a potion on the hero
-IN: --
OUT: --
ERROR: --
**/
void potUse();

/**
- potEmpty
- Displays a notification if the user tries to use a potion but the hero has none available
-IN: --
OUT: --
ERROR: --
**/
void potEmpty();

#endif

