/*
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 * Altered by Ana, Gabriel and Sophia <Taverna/>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

// 1
#define STARTIROOM1 8
#define FINISHIROOM1 27
#define STARTJROOM1 8
#define FINISHJROOM1 16

#define DOORI1 26
#define DOORJ1 12

#define STARTIHALL1 27
#define FINISHIHALL1 32
#define STARTJHALL1 11
#define FINISHJHALL1 14

// 2
#define STARTIROOM2 34
#define FINISHIROOM2 44
#define STARTJROOM2 8
#define FINISHJROOM2 20

#define ENTERDOORI2 34
#define ENTERDOORJ2 12

#define EXITDOORI2 38
#define EXITDOORJ2 19

#define STARTIHALL2 36
#define FINISHIHALL2 41
#define STARTJHALL2 20
#define FINISHJHALL2 24

// 3
#define STARTIROOM3 27
#define FINISHIROOM3 85
#define STARTJROOM3 24
#define FINISHJROOM3 32

#define ENTERDOORI3 38
#define ENTERDOORJ3 24

#define EXITDOORI3 84
#define EXITDOORJ3 28

#define STARTIHALL3 85
#define FINISHIHALL3 92
#define STARTJHALL3 27
#define FINISHJHALL3 30

// 4
#define STARTIROOM4 94
#define FINISHIROOM4 112
#define STARTJROOM4 10
#define FINISHJROOM4 32

#define ENTERDOORI4 94
#define ENTERDOORJ4 28

#define EXITDOORI4 94
#define EXITDOORJ4 13

#define STARTIHALL4 92
#define FINISHIHALL4 80
#define STARTJHALL4 12
#define FINISHJHALL4 15

// 5 (boos entrance)
#define STARTIROOM5 50
#define FINISHIROOM5 80
#define STARTJROOM5 7
#define FINISHJROOM5 20

#define ENTERDOORI5 94
#define ENTERDOORJ5 13

#define EXITDOORI5 94
#define EXITDOORJ5 13

char *enemies[] = {"💀", "👿", "👹", "👻", "👽", "🧟", "🧛"};

int incX = 1, incY = 1;

int player_x = 16, player_y = 14;

int enemies1 = 1;
int enemies2 = 0;
int enemies3 = 0;
int enemies4 = 0;
int enemies5 = 0;
struct player
{
    int sword;
    int shield;
    int score;
    int steps;
    char name[4];
    int hp;
};

struct enemy_obj
{
    int x;
    int y;
    int is_dead;
    int inc_x;
    char *image;
};
struct trap_obj
{
    int x;
    int y;
    int previous_x;
    int previous_y;
    int inc_x;
    int inc_y;
};
void print_trap(struct trap_obj trap, int new_shot_x, int new_shot_y)
{
    screenGotoxy(trap.previous_x, trap.previous_y);
    printf(" ");
    trap.x = new_shot_x;
    trap.y = new_shot_y;
    screenGotoxy(trap.x, trap.y);
    printf("*");
}

void print_enemy(struct enemy_obj enemy, int new_enemy_x, int new_enemy_y)
{
    screenGotoxy(enemy.x, enemy.y);
    printf(" ");
    enemy.x = new_enemy_x;
    enemy.y = new_enemy_y;
    screenGotoxy(enemy.x, enemy.y);
    printf("%s", enemy.image);
}

void print_player(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(player_x, player_y);
    printf("  ");
    player_x = nextX;
    player_y = nextY;
    screenGotoxy(player_x, player_y);
    printf("🐱");
}

void print_sword(int pos_X, int pos_Y)
{
    int cont = 55;
    while (cont > 0)
    {
        screenGotoxy(pos_X - 1, pos_Y - 1);
        printf("╲");
        printf(" ");
        screenGotoxy(pos_X, pos_Y - 1);
        printf("|");
        printf(" ");
        screenGotoxy(pos_X + 1, pos_Y - 1);
        printf("╱");
        printf(" ");
        screenGotoxy(pos_X - 1, pos_Y);
        printf("─ ");
        printf(" ");
        screenGotoxy(pos_X + 1, pos_Y);
        printf(" ─");
        printf(" ");
        screenGotoxy(pos_X - 1, pos_Y + 1);
        printf("╱");
        printf(" ");
        screenGotoxy(pos_X, pos_Y + 1);
        printf("|");
        printf(" ");
        screenGotoxy(pos_X + 1, pos_Y + 1);
        printf("╲");
        printf(" ");

        usleep(5000);

        screenGotoxy(pos_X - 1, pos_Y - 1);
        printf("  ");
        screenGotoxy(pos_X, pos_Y - 1);
        printf("  ");
        screenGotoxy(pos_X + 1, pos_Y - 1);
        printf("  ");
        screenGotoxy(pos_X - 1, pos_Y);
        printf("  ");
        screenGotoxy(pos_X + 1, pos_Y);
        printf("  ");
        screenGotoxy(pos_X - 1, pos_Y + 1);
        printf("  ");
        screenGotoxy(pos_X, pos_Y + 1);
        printf("  ");
        screenGotoxy(pos_X + 1, pos_Y + 1);
        printf("  ");

        cont--;
    }
}

void print_shield(int pos_X, int pos_Y)
{
    int cont = 55;
    while (cont > 0)
    {
        screenSetColor(YELLOW, DARKGRAY);
        screenGotoxy(pos_X - 1, pos_Y - 1);
        printf("┌");
        printf(" ");
        screenGotoxy(pos_X, pos_Y - 1);
        printf("──");
        printf(" ");
        screenGotoxy(pos_X + 2, pos_Y - 1);
        printf("┐");
        printf(" ");
        screenGotoxy(pos_X - 1, pos_Y);
        printf("│ ");
        printf(" ");
        screenGotoxy(pos_X + 1, pos_Y);
        printf(" │");
        printf(" ");
        screenGotoxy(pos_X - 1, pos_Y + 1);
        printf("└");
        printf(" ");
        screenGotoxy(pos_X, pos_Y + 1);
        printf("──");
        printf(" ");
        screenGotoxy(pos_X + 2, pos_Y + 1);
        printf("┘");
        printf(" ");

        usleep(5000);

        screenGotoxy(pos_X - 1, pos_Y - 1);
        printf(" ");
        screenGotoxy(pos_X, pos_Y - 1);
        printf("  ");
        screenGotoxy(pos_X + 2, pos_Y - 1);
        printf(" ");
        screenGotoxy(pos_X - 1, pos_Y);
        printf(" ");
        screenGotoxy(pos_X + 1, pos_Y);
        printf("  ");
        screenGotoxy(pos_X - 1, pos_Y + 1);
        printf(" ");
        screenGotoxy(pos_X, pos_Y + 1);
        printf("  ");
        screenGotoxy(pos_X + 2, pos_Y + 1);
        printf(" ");

        cont--;
    }
}

void printRooms(int start_i_room, int finish_i_room, int start_j_room, int finish_j_room, int room, int *room_enemies, int enter_door_i, int enter_door_j, int exit_door_i, int exit_door_j)
{
    int roomRange = (player_x + 1 >= start_i_room) && (player_x <= finish_i_room) && (player_y - 1 >= start_j_room) && (player_y <= finish_j_room);

    screenSetColor(CYAN, DARKGRAY);
    int last_j = start_j_room;
    if (roomRange && (room != 0))
    {
        *room_enemies = 1;
        for (int i = start_i_room; i < finish_i_room; i++)
        {
            for (int j = start_j_room; j < finish_j_room; j++)
            {
                if ((i == enter_door_i && j == enter_door_j) || (i == exit_door_i && j == exit_door_j))
                {
                    screenGotoxy(i, j);
                    printf("🚪");
                }
                else if (j == start_j_room || j == finish_j_room - 1)
                {
                    screenGotoxy(i, j);
                    printf("-");
                }
                else if (i == start_i_room || i == finish_i_room - 1)
                {
                    screenGotoxy(i, j);
                    printf("|");
                }

                last_j = j;
            }
            screenGotoxy(i, last_j);
            printf("\n");
        }
    }
    else if (room == 0)
    {
        for (int i = start_i_room; i < finish_i_room; i++)
        {
            for (int j = start_j_room; j < finish_j_room; j++)
            {
                if (i == enter_door_i && j == enter_door_j)
                {
                    screenGotoxy(i, j);
                    printf("🚪");
                }
                else if (j == start_j_room || j == finish_j_room - 1)
                {
                    screenGotoxy(i, j);
                    printf("-");
                }
                else if (i == start_i_room || i == finish_i_room - 1)
                {
                    screenGotoxy(i, j);
                    printf("|");
                }

                last_j = j;
            }
            screenGotoxy(i, last_j);
            printf("\n");
        }
    }
}

void printHorizontalHall(int start_i_hall, int finish_i_hall, int start_j_hall, int finish_j_hall)
{
    if (player_x >= start_i_hall - 2 && player_x < finish_i_hall && player_y > start_j_hall && player_y < finish_j_hall)
    {
        screenGotoxy(player_x + 2, start_j_hall);
        printf("═");
        screenGotoxy(player_x + 2, finish_j_hall - 1);
        printf("═");
    }
}

void printVerticalHall(int start_i_hall, int finish_i_hall, int start_j_hall, int finish_j_hall)
{
    if ((player_y >= start_j_hall) && (player_y < finish_j_hall))
    {
        screenGotoxy(start_i_hall, player_y);
        printf("║");
        screenGotoxy(finish_i_hall, player_y);
        printf("║");
    }
}

void printHp(int health)
{
    screenGotoxy(MINX + 1, MINY + 1);
    printf("      ");
    for (int h = 1; h < health + 1; h++)
    {
        screenGotoxy(MINX + h + h, MINY + 1);
        screenSetColor(RED, DARKGRAY);
        printf("♥");
        screenSetColor(CYAN, DARKGRAY);
    }
    if (health == 0)
    {
        printf("☠️ You died! ☠️");
    }
}

void printKey(int ch)
{
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(65, 2);
    printf("Key code :");

    screenGotoxy(64, 3);
    printf("            ");

    if (ch == 27)
        screenGotoxy(66, 3);
    else
        screenGotoxy(69, 3);

    printf("%d ", ch);
    while (keyhit())
    {
        printf("%d ", readch());
    }
}

void printSteps(struct player p)
{
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(130, 2);
    printf("Steps:");

    screenGotoxy(129, 3);
    printf("    ");
    printf("%d", p.steps);
}

void asciiPrint()
{
    FILE *file;
    char string[128];

    file = fopen("src/files/menu.txt", "r+");

    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    while (fgets(string, sizeof(string), file) != NULL)
    {
        printf("%s", string);
    }

    fclose(file);
}

int main()
{
    srand(time(NULL));
    static int ch = 0;
    struct player player;
    struct enemy_obj enemy_room_1;
    struct enemy_obj enemy_room_2;

    struct trap_obj trap1;

    enemy_room_1.x = 22;
    enemy_room_1.y = 10;
    enemy_room_1.image = enemies[(rand() % 7)];

    enemy_room_2.x = 36;
    enemy_room_2.y = 17;
    enemy_room_2.inc_x = 1;
    enemy_room_2.is_dead = 0;
    enemy_room_2.image = enemies[(rand() % 7)];

    player.sword = 0;
    player.shield = 0;
    player.steps = 0;
    player.score = 0;
    player.hp = 3;

    // sala 3
    trap1.x = 40;
    trap1.y = FINISHJROOM3 - 1;
    trap1.previous_x = 40;
    trap1.previous_y = FINISHJROOM3 - 1;
    trap1.inc_y = -1;

    // initial screen display
    screenInit(0);
    keyboardInit();

    screenSetColor(RED, DARKGRAY);
    asciiPrint();

    screenSetColor(LIGHTGRAY, DARKGRAY);

    screenGotoxy(60, 19);
    printf("START GAME");

    screenGotoxy(62, 21);
    printf("SCORES");

    screenGotoxy(63, 23);
    printf("EXIT");

    int menu_cont = 0;
    screenSetColor(RED, DARKGRAY);

    while (ch != 32)
    {
        if (keyhit())
        {
            ch = readch();
        }

        if ((ch == 115) || (ch == 83))
        {
            menu_cont++;

            if (menu_cont == 3)
            {
                menu_cont = 0;
            }

            ch = 0;
        }

        if ((ch == 119) || (ch == 87))
        {
            menu_cont--;

            if (menu_cont < 0)
            {
                menu_cont = 2;
            }

            ch = 0;
        }

        if (menu_cont == 0)
        {
            screenGotoxy(58, 19);
            printf(">");
            screenGotoxy(71, 19);
            printf("<");
            screenGotoxy(60, 21);
            printf(" ");
            screenGotoxy(69, 21);
            printf(" ");
            screenGotoxy(61, 23);
            printf(" ");
            screenGotoxy(68, 23);
            printf(" ");
        }

        if (menu_cont == 1)
        {
            screenGotoxy(58, 19);
            printf(" ");
            screenGotoxy(71, 19);
            printf(" ");
            screenGotoxy(60, 21);
            printf(">");
            screenGotoxy(69, 21);
            printf("<");
            screenGotoxy(61, 23);
            printf(" ");
            screenGotoxy(68, 23);
            printf(" ");
        }

        if (menu_cont == 2)
        {
            screenGotoxy(58, 19);
            printf(" ");
            screenGotoxy(71, 19);
            printf(" ");
            screenGotoxy(60, 21);
            printf(" ");
            screenGotoxy(69, 21);
            printf(" ");
            screenGotoxy(61, 23);
            printf(">");
            screenGotoxy(68, 23);
            printf("<");
        }
    }
    ch = 0;

    if (menu_cont == 2)
    {
        printf("\n");
        keyboardDestroy();
        screenDestroy();
        return 0;
    }

    screenSetColor(LIGHTGRAY, DARKGRAY);
    screenInit(1);
    timerInit(150);

    screenGotoxy(MINX + 1, MINY + 1);

    printHp(player.hp);

    screenSetColor(WHITE, DARKGRAY);
    screenGotoxy(MINX + 35, MINY + 1);
    printf("┃ Inventory ┃");

    if (player.shield == 0)
    {
        screenGotoxy(MINX + 42, MINY + 2);
        printf("┏━━━┓");
        screenGotoxy(MINX + 42, MINY + 3);
        printf("┃🛡️  ┃");
        screenGotoxy(MINX + 42, MINY + 4);
        printf("┗━━━┛");
    }

    print_player(player_x, player_y);

    screenGotoxy(player_x, player_y - 5);
    printf("🗡️");

    printRooms(STARTIROOM1, FINISHIROOM1, STARTJROOM1, FINISHJROOM1, 0, &enemies1, DOORI1, DOORJ1, DOORI1, DOORJ1); // first room

    print_enemy(enemy_room_1, enemy_room_1.x, enemy_room_1.y);

    screenUpdate();

    while (ch != 32)
    {
        if (keyhit())
        {
            ch = readch();
            printKey(ch);
            screenUpdate();
        }

        screenGotoxy(MINX + 1, MINY + 2);
        printf("%d %d", player_x, player_y);

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1)
        {
            int newX = player_x, newY = player_y;
            enemy_room_2.x = enemy_room_2.x + enemy_room_2.inc_x;

            int collisionXRoom1 = newY > STARTJROOM1 - 1 && newY < FINISHJROOM1;
            int collisionYRoom1 = newX >= STARTIROOM1 && newX < FINISHIROOM1;

            int collisionXRoom2 = newY > STARTJROOM2 - 1 && newY < FINISHJROOM2;
            int collisionYRoom2 = newX >= STARTIROOM2 && newX < FINISHIROOM2;

            int collisionXRoom3 = newY > STARTJROOM3 - 1 && newY < FINISHJROOM3;
            int collisionYRoom3 = newX >= STARTIROOM3 && newX < FINISHIROOM3;

            int collisionXRoom4 = newY > STARTJROOM4 - 1 && newY < FINISHJROOM4;
            int collisionYRoom4 = newX >= STARTIROOM4 && newX < FINISHIROOM4;

            int collisionYHall1 = newX >= FINISHIROOM1 - strlen("🐱") && newX <= FINISHIHALL1 + 1 && newY > STARTJHALL1 && newY < FINISHJHALL1;
            int collisionXHall2 = newY >= FINISHJROOM2 && newY <= FINISHJHALL2 + 1 && newX > STARTIHALL2 && newX < FINISHIHALL2;
            int collisionYHall3 = newX >= FINISHIROOM3 - strlen("🐱") && newX <= FINISHIHALL3 + 1 && newY > STARTJHALL3 && newY < FINISHJHALL3;
            int collisionYHall4 = newX < STARTIHALL4 + strlen("🐱") && newX >= FINISHIHALL4 - 1 && newY > STARTJHALL4 && newY < FINISHJHALL4;

            if (enemy_room_2.x >= FINISHIROOM2 - strlen("    ") || enemy_room_2.x - 2 < STARTIROOM2)
            {
                enemy_room_2.inc_x = -enemy_room_2.inc_x;
            }

            if ((ch == 97) || (ch == 65)) // left
            {
                newX = player_x - incX;
                player.steps++;

                // Colisão room 1
                if ((newX == FINISHIROOM1 - 1 && collisionXRoom1))
                {
                    newX += 1;
                }
                else if (newY != DOORJ1 && newX == STARTIROOM1 && collisionXRoom1)
                {
                    newX += 1;
                }

                // Colisão room 2
                if (newY != 12 && newX == FINISHIROOM2 - 1 && collisionXRoom2)
                {
                    newX += 1;
                }
                else if (newX == STARTIROOM2 && collisionXRoom2)
                {
                    newX += 1;
                }

                // Colisão room 3
                if (newX == FINISHIROOM3 - 1 && collisionXRoom3)
                {
                    newX += 1;
                }
                else if (newX == STARTIROOM3 && collisionXRoom3)
                {
                    newX += 1;
                }

                // Colisão room 4
                if (newX == FINISHIROOM4 - 1 && collisionXRoom4)
                {
                    newX += 1;
                }
                else if (newY != EXITDOORJ4 && newX == STARTIROOM4 && collisionXRoom4)
                {
                    newX += 1;
                }

                if (collisionXHall2)
                {
                    newX += 1;
                }

                if (!(newX <= MINX + 1))
                {
                    incX = 1;
                }
                if (newX <= MINX + 1)
                {
                    incX = 0;
                }

                ch = 0;
            }

            if ((ch == 100) || (ch == 68)) // right
            {
                newX = player_x + incX;
                player.steps++;

                // ROOM 0
                if (newY != DOORJ1 && (newX == FINISHIROOM1 - 2 && collisionXRoom1))
                {
                    newX -= 1;
                }
                else if (newX == STARTIROOM1 - 1 && collisionXRoom1)
                {
                    newX -= 1;
                }

                // ROOM 2
                if (newX == FINISHIROOM2 - 2 && collisionXRoom2)
                {
                    newX -= 1;
                }
                else if (newY != 12 && (newX == STARTIROOM2 - 1 && collisionXRoom2))
                {
                    newX -= 1;
                }

                // ROOM 3
                if (newY != EXITDOORJ3 && newX == FINISHIROOM3 - 2 && collisionXRoom3)
                {
                    newX -= 1;
                }
                else if (newX == STARTIROOM3 - 1 && collisionXRoom3)
                {
                    newX -= 1;
                }

                // ROOM 4
                if (newX == FINISHIROOM4 - 2 && collisionXRoom4)
                {
                    newX -= 1;
                }
                else if (newY != ENTERDOORJ4 && newX == STARTIROOM4 - 1 && collisionXRoom4)
                {
                    newX -= 1;
                }

                if (collisionXHall2)
                {
                    newX -= 1;
                }

                if (newX <= (MAXX - strlen("🐱") - 1))
                {
                    incX = 1;
                }
                if (newX >= (MAXX - strlen("🐱") - 1))
                {
                    incX = 0;
                }

                ch = 0;
            }

            if ((ch == 115) || (ch == 83)) // down
            {
                newY = player_y + incY;
                player.steps++;

                // Colisão room 1
                if (newY == STARTJROOM1 && collisionYRoom1)
                {
                    newY -= 1;
                }
                else if (newY == FINISHJROOM1 - 1 && collisionYRoom1)
                {
                    newY -= 1;
                }

                // Colisão room 2
                if (newY == STARTJROOM2 && collisionYRoom2)
                {
                    newY -= 1;
                }
                else if (newX != EXITDOORI2 && newY == FINISHJROOM2 - 1 && collisionYRoom2)
                {
                    newY -= 1;
                }

                // Colisão room 3
                if (newY != ENTERDOORJ3 && newY == STARTJROOM3 && collisionYRoom3)
                {
                    newY -= 1;
                }
                else if (newY == FINISHJROOM3 - 1 && collisionYRoom3)
                {
                    newY -= 1;
                }

                // Colisão room 4
                if (newY != ENTERDOORJ4 && newY == STARTJROOM4 && collisionYRoom4)
                {
                    newY -= 1;
                }
                else if (newY == FINISHJROOM4 - 1 && collisionYRoom4)
                {
                    newY -= 1;
                }

                if (collisionYHall1 || collisionYHall3 || collisionYHall4)
                {
                    newY -= 1;
                }

                if (newY >= MAXY - 3)
                {
                    incY = 0;
                }

                if (newY <= MAXY - 3)
                {
                    incY = 1;
                }

                ch = 0;
            }

            if ((ch == 119) || (ch == 87)) // up
            {
                newY = player_y - incY;
                player.steps++;

                // Colisão room 1
                if (newY == STARTJROOM1 && collisionYRoom1)
                {
                    newY += 1;
                }
                else if (newY == FINISHJROOM1 && collisionYRoom1)
                {
                    newY += 1;
                }

                // Colisão room 2
                if (newY == STARTJROOM2 && collisionYRoom2)
                {
                    newY += 1;
                }
                else if (newY == FINISHJROOM2 && collisionYRoom2)
                {
                    newY += 1;
                }

                // Colisão room 3
                if (newY == STARTJROOM3 && collisionYRoom3)
                {
                    newY += 1;
                }
                else if (newY == FINISHJROOM3 && collisionYRoom3)
                {
                    newY += 1;
                }

                // Colisão room 4
                if (newY == STARTJROOM4 && collisionYRoom4)
                {
                    newY += 1;
                }
                else if (newY == FINISHJROOM4 && collisionYRoom4)
                {
                    newY += 1;
                }

                if (collisionYHall1 || collisionYHall3 || collisionYHall4)
                {
                    newY += 1;
                }

                if (newY <= MINY + 3)
                {
                    incY = 0;
                }

                if (newY >= MINY + 3)
                {
                    incY = 1;
                }

                ch = 0;
            }

            if (((ch == 106) || (ch == 74)) && (player.sword == 1))
            {
                print_sword(newX, newY);
                if (abs(newX - enemy_room_2.x) == 1 || abs(newY - enemy_room_2.y) == 1)
                {
                    enemy_room_2.is_dead = 1;
                }

                ch = 0;
            }

            if (((ch == 107) || (ch == 75)) && (player.shield == 0)) // falta adicionar o escudo no mapa
            {
                print_shield(newX, newY);
                ch = 0;
            }

            printHorizontalHall(STARTIHALL1, FINISHIHALL1, STARTJHALL1, FINISHJHALL1);
            printHorizontalHall(STARTIHALL3, FINISHIHALL3, STARTJHALL3, FINISHJHALL3);
            printHorizontalHall(FINISHIHALL4, STARTIHALL4, STARTJHALL4, FINISHJHALL4);
            printVerticalHall(STARTIHALL2, FINISHIHALL2, STARTJHALL2, FINISHJHALL2);

            printRooms(STARTIROOM2, FINISHIROOM2, STARTJROOM2, FINISHJROOM2, 2, &enemies2, ENTERDOORI2, ENTERDOORJ2, EXITDOORI2, EXITDOORJ2);
            printRooms(STARTIROOM3, FINISHIROOM3, STARTJROOM3, FINISHJROOM3, 3, &enemies3, ENTERDOORI3, ENTERDOORJ3, EXITDOORI3, EXITDOORJ3);
            printRooms(STARTIROOM4, FINISHIROOM4, STARTJROOM4, FINISHJROOM4, 4, &enemies4, ENTERDOORI4, ENTERDOORJ4, EXITDOORI4, EXITDOORJ4);
            printRooms(STARTIROOM5, FINISHIROOM5, STARTJROOM5, FINISHJROOM5, 5, &enemies5, ENTERDOORI5, ENTERDOORJ5, EXITDOORI5, EXITDOORJ5);

            print_player(newX, newY);
            printSteps(player);

            if (enemy_room_2.x == newX && enemy_room_2.y == newY && !enemy_room_2.is_dead)
            {
                player.hp--;
                printHp(player.hp);
            }

            if (enemies2 == 1 && enemy_room_2.is_dead == 0)
            {
                print_enemy(enemy_room_2, enemy_room_2.x, enemy_room_2.y);
            }

            if (enemies3 == 1)
            {
                trap1.previous_y = trap1.y;
                trap1.y = trap1.y + trap1.inc_y;
                if (trap1.y == STARTJROOM3)
                {
                    trap1.y = FINISHJROOM3 - 2;
                }

                print_trap(trap1, trap1.x, trap1.y);
            }

            if ((newX == 16 || newX == 15) && newY == 9)
            {
                player.sword = 1;
            }

            if (player.sword == 1)
            {
                screenSetColor(WHITE, DARKGRAY);
                screenGotoxy(MINX + 35, MINY + 2);
                printf("┏━━━┓");
                screenGotoxy(MINX + 35, MINY + 3);
                printf("┃🗡️  ┃");
                screenGotoxy(MINX + 35, MINY + 4);
                printf("┗━━━┛");
            }

            // Updating screen
            printKey(ch);
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}