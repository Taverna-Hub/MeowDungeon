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
#include <time.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int start_i_room1 = 8, finish_i_room1 = 27;
int start_j_room1 = 8, finish_j_room1 = 16;
int door_i1 = 26, door_j1 = 12;

int start_i_hall = 27, finish_i_hall = 32;
int star_j_hall = 11, finish_j_hall = 14;

int start_i_room2 = 34, finish_i_room2 = 44;
int start_j_room2 = 8, finish_j_room2 = 20;

int incX = 1, incY = 1;

int player_x = 16, player_y = 14;
struct player
{
    int sword;
    int shield;
    int score;
    int steps;
    char name[4];
};

char *enemies[] = {"💀", "👿", "👹", "👻"};
struct enemy_obj
{
    int x;
    int y;
};

void print_enemy(struct enemy_obj skull, int new_enemy_x, int new_enemy_y)
{
    screenGotoxy(skull.x, skull.y);
    printf(" ");
    skull.x = new_enemy_x;
    skull.y = new_enemy_y;
    screenGotoxy(skull.x, skull.y);
    printf("💀");
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

/* animação de ataque em area (ou blik)
 \ | /
--🐱--
 / | \
*/
// void print_sword()

void printRooms(int start_i_room, int finish_i_room, int start_j_room, int finish_j_room, int room)
{
    screenSetColor(CYAN, DARKGRAY);
    int last_j = start_j_room;
    if ((player_x + 1 == start_i_room) && (room != 0))
    {
        for (int i = start_i_room; i < finish_i_room; i++)
        {
            for (int j = start_j_room; j < finish_j_room; j++)
            {
                if (i == door_i1 && j == door_j1)
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
                if (i == door_i1 && j == door_j1)
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

void printHorizontalHall(int start_i_hall, int finish_i_hall, int star_j_hall, int finish_j_hall)
{
    if (player_x >= start_i_hall - 2 && player_x < finish_i_hall)
    {
        screenGotoxy(player_x + 2, star_j_hall);
        printf("=");
        screenGotoxy(player_x + 2, finish_j_hall - 1);
        printf("=");
    }
}

void printKey(int ch)
{
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    printf("Key code :");

    screenGotoxy(34, 23);
    printf("            ");

    if (ch == 27)
        screenGotoxy(36, 23);
    else
        screenGotoxy(39, 23);

    printf("%d ", ch);
    while (keyhit())
    {
        printf("%d ", readch());
    }
}

int main()
{
    static int ch = 0;
    struct enemy_obj skeleton;
    struct enemy_obj demon;
    struct player player;

    player.sword = 0;
    player.shield = 0;
    player.steps = 0;
    player.score = 0;
    struct enemy_obj enemy_room_2;

    screenInit(1);
    keyboardInit();
    timerInit(100);

    screenGotoxy(MINX + 1, MINY + 1);
    printf("🐱🐱🐱");
    printf("\t| Iventory |");

    if (player.shield == 0)
    {
        screenGotoxy(MINX + 22, MINY + 2);
        printf("┏━━━┓");
        screenGotoxy(MINX + 22, MINY + 3);
        printf("┃🛡️  ┃");
        screenGotoxy(MINX + 22, MINY + 4);
        printf("┗━━━┛");
    }

    print_player(player_x, player_y);
    screenGotoxy(player_x, player_y - 5);

    skeleton.x = 22;
    skeleton.y = 10;

    demon.x = 39;
    demon.y = 11;

    enemy_room_2.x = 36;
    enemy_room_2.y = 10;

    screenGotoxy(player_x, player_y - 5);
    printf("🗡️");

    printRooms(start_i_room1, finish_i_room1, start_j_room1, finish_j_room1, 0); // first room

    print_enemy(skeleton, skeleton.x, skeleton.y);
    print_enemy(enemy_room_2, enemy_room_2.x, enemy_room_2.y);
    screenUpdate();

    int skull_verify = 1;
    int demon_verify = 1;
    while (ch != 10)
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

            int collisionXRoom1 = newY > start_j_room1 - 1 && newY < finish_j_room1;
            int collisionYRoom1 = newX >= start_i_room1 && newX < finish_i_room1;

            int collisionXRoom2 = newY > start_j_room2 - 1 && newY < finish_j_room2;
            int collisionYRoom2 = newX >= start_i_room2 && newX < finish_i_room2;

            int collisionYHall = newX >= finish_i_room1 - strlen("🐱") && newX <= finish_i_hall + 1;

            if (enemy_room_2.x >= finish_i_room2 - strlen("🐱") - 1)
            {
                enemy_room_2.x = enemy_room_2.x - 1;
            }
            else
            {
                enemy_room_2.x = enemy_room_2.x + 1;
            }
            if (demon_verify == 1)
            {
                print_enemy(demon, demon.x, demon.y);
            }

            print_enemy(enemy_room_2, enemy_room_2.x, enemy_room_2.y);

            if (ch == 97)
            {
                newX = player_x - incX;

                // Colisão room 0
                if ((newX == finish_i_room1 - 1 && collisionXRoom1))
                {
                    newX += 1;
                }
                else if (newY != 12 && (newX == start_i_room1 && collisionXRoom1))
                {
                    newX += 1;
                }

                // Colisão room 2
                if (newY != 12 && (newX == finish_i_room2 - 1 && collisionXRoom2))
                {
                    newX += 1;
                }
                else if (newX == start_i_room2 && collisionXRoom2)
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

            if (ch == 100)
            {
                newX = player_x + incX;

                if (newY != 12 && (newX == finish_i_room1 - 4 && collisionXRoom1))
                {
                    newX -= 1;
                }
                else if (newX == start_i_room1 - 1 && collisionXRoom1)
                {
                    newX -= 1;
                }

                if (newX == finish_i_room2 - 4 && collisionXRoom2)
                {
                    newX -= 1;
                }
                else if (newY != 12 && (newX == start_i_room2 - 1 && collisionXRoom2))
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

            if (ch == 115)
            {
                newY = player_y + incY;

                if (newY == start_j_room1 && collisionYRoom1)
                {
                    newY -= 1;
                }
                else if (newY == finish_j_room1 - 1 && collisionYRoom1)
                {
                    newY -= 1;
                }

                if (newY == start_j_room2 && collisionYRoom2)
                {
                    newY -= 1;
                }
                else if (newY == finish_j_room2 - 1 && collisionYRoom2)
                {
                    newY -= 1;
                }

                if (collisionYHall)
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

            if (ch == 119)
            {
                newY = player_y - incY;

                if (newY == start_j_room1 && collisionYRoom1)
                {
                    newY += 1;
                }
                else if (newY == finish_j_room1 && collisionYRoom1)
                {
                    newY += 1;
                }

                if (newY == start_j_room2 && collisionYRoom2)
                {
                    newY += 1;
                }
                else if (newY == finish_j_room2 && collisionYRoom2)
                {
                    newY += 1;
                }

                if (collisionYHall)
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

            printHorizontalHall(27, 32, 11, 14);
            printHorizontalHall(44, 48, 16, 19);

            printRooms(start_i_room2, finish_i_room2, start_j_room2, finish_j_room2, 2);
            print_player(newX, newY);

            if (newX == skeleton.x && newY == skeleton.y)
            {
                skull_verify = 0;
            }
            if (newX == demon.x && newY == demon.y)
            {
                demon_verify = 0;
            }

            if (newX == 16 && newY == 9)
            {
                player.sword = 1;
            }

            if (player.sword == 1)
            {
                screenGotoxy(MINX + 15, MINY + 2);
                printf("┏━━━┓");
                screenGotoxy(MINX + 15, MINY + 3);
                printf("┃🗡️  ┃");
                screenGotoxy(MINX + 15, MINY + 4);
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