#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

void pickup(char item) {

    int y;
    int x;
    getyx(stdscr, y, x);
    move(1,5);
    clrtoeol();

    if (item == ')') {
        mvprintw(1, 5, "Hero picked up a common weapon!");
    }
    else if (item == '(') {
        mvprintw(1, 5, "Hero picked up a rare weapon!");
    }
    else if (item == ']') {
        mvprintw(1, 5, "Hero picked up equipment!");
    }
    else if (item == '!') {
        mvprintw(1, 5, "Hero picked up a potion!");
    }
    else if (item == '*') {
        mvprintw(1, 5, "Hero picked up a small gold!");
    }
    else if (item == '8') {
        mvprintw(1, 5, "Hero picked up a large gold!");
    }

    move(y, x);

}

void bagFull(char item) {

    int y;
    int x;
    getyx(stdscr, y, x);
    move(1,5);
    clrtoeol();

    if (item == ')') {
        mvprintw(1, 5, "Hero stepped on a common weapon, and broke it!");
    }
    else if (item == '(') {
        mvprintw(1, 5, "Hero stepped on a rare weapon, and broke it!");
    }
    else if (item == ']') {
        mvprintw(1, 5, "Hero stepped on an equipment, and broke it!");
    }

    move(y, x);


}

void takeDamage(int monsterAttack) {

    int y;
    int x;
    getyx(stdscr, y, x);
    move(1,5);
    clrtoeol();
    mvprintw(1, 5, "Hero took %d damage!", monsterAttack);
    move(y,x);

}

void giveDamage(int attackRating) {

    int y;
    int x;
    getyx(stdscr, y, x);
    move(1,5);
    clrtoeol();
    mvprintw(1, 5, "Hero dealt %d damage!", attackRating);
    move(y,x);
}

void kill(char monsterType) {

    int y;
    int x;
    getyx(stdscr, y, x);
    move(1,5);
    clrtoeol();

    if (monsterType == 'T') {
        mvprintw(1, 5, "Hero killed a troll!");
    }
    if (monsterType == 'A') {
        mvprintw(1, 5, "Hero killed an aquator!");
    }

    if (monsterType == 'B') {
        mvprintw(1, 5, "Hero killed a bat!");
    }

    if (monsterType == 'S') {
        mvprintw(1, 5, "Hero killed a snake!");
    }

    if (monsterType == 'Z') {
        mvprintw(1, 5, "Hero killed a zombie!");
    }

    move(y,x);
}

void hitByAquator() {

    int y;
    int x;
    getyx(stdscr, y, x);
    move(1,5);
    clrtoeol();
    mvprintw(1, 5, "Hero was hit by the Aquator and lost 1 attack rating!");
    move(y,x);
}

void attackIsZero() {

    int y;
    int x;
    getyx(stdscr, y, x);
    move(1,5);
    clrtoeol();
    mvprintw(1, 5, "Hero was hit by the Aquator, but is unable to go below 0 attack!");
    move(y,x);
}

void door() {

    int y;
    int x;
    getyx(stdscr, y, x);

    mvprintw(1, 5, "Opened a door!");
    move(y,x);

}

void potUse() {

    int y;
    int x;
    getyx(stdscr, y, x);

    mvprintw(1, 5, "Used a potion: Hero's health was restored to 50!");
    move(y, x);
}

void potEmpty() {

    int y;
    int x;
    getyx(stdscr, y, x);

    mvprintw(1, 5, "Out of potions!");
    move(y,x);

}

