/**
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

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int player_x = 16, player_y = 14;

int startIRoom1 = 8, finishIRoom1 = 27;
int startJRoom1 = 8, finishJRoom1 = 16;
int doorI1 = 26, doorJ1 = 12;

int startIHall = 27, finishIHall = 32;
int starJHall = 11, finishJHall = 14;

int startIRoom2 = 34, finishIRoom2 = 44;
int startJRoom2 = 8, finishJRoom2 = 20;

int incX = 1, incY = 1;

// struct player
// {
//     int positionX;
//     int positionY;
//      int incX;
//      int incY;
//     int sword;
//     int shield;
// };

struct enemy_skull
{
    int skull_x;
    int skull_y;
};

int skull_x = 22;
int skull_y = 10;

void printSkull(struct enemy_skull skull)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(skull_x, skull_y);
    printf("    ");
    skull_x = skull.skull_x;
    skull_y = skull.skull_y;
    screenGotoxy(skull_x, skull_y);
    printf("💀");
}

void printPlayer(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(player_x, player_y);
    printf("    ");
    player_x = nextX;
    player_y = nextY;
    screenGotoxy(player_x, player_y);
    printf("🐱");
}

void printRooms(int starIRoom, int finishIRoom, int startJRoom, int finishJRoom, int lastJ, int room)
{
    screenSetColor(CYAN, DARKGRAY);
    if ((player_x + 1 == starIRoom) && (room != 0))
    {
        for (int i = starIRoom; i < finishIRoom; i++)
        {
            for (int j = startJRoom; j < finishJRoom; j++)
            {
                if (i == doorI1 && j == doorJ1)
                {
                    screenGotoxy(i, j);
                    printf("🚪");
                }
                else if (j == startJRoom || j == finishJRoom - 1)
                {
                    screenGotoxy(i, j);
                    printf("-");
                }
                else if (i == starIRoom || i == finishIRoom - 1)
                {
                    screenGotoxy(i, j);
                    printf("|");
                }

                lastJ = j;
            }
            screenGotoxy(i, lastJ);
            printf("\n");
        }
    }
    else if (room == 0)
    {
        for (int i = starIRoom; i < finishIRoom; i++)
        {
            for (int j = startJRoom; j < finishJRoom; j++)
            {
                if (i == doorI1 && j == doorJ1)
                {
                    screenGotoxy(i, j);
                    printf("🚪");
                }
                else if (j == startJRoom || j == finishJRoom - 1)
                {
                    screenGotoxy(i, j);
                    printf("-");
                }
                else if (i == starIRoom || i == finishIRoom - 1)
                {
                    screenGotoxy(i, j);
                    printf("|");
                }

                lastJ = j;
            }
            screenGotoxy(i, lastJ);
            printf("\n");
        }
    }
}

void printHorizontalHall(int startIHall, int finishIHall, int starJHall, int finishJHall)
{
    if (player_x >= startIHall - 2 && player_x < finishIHall)
    {
        screenGotoxy(player_x + 2, starJHall);
        printf("=");
        screenGotoxy(player_x + 2, finishJHall - 1);
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
    struct enemy_skull skeleton;

    screenInit(1);
    keyboardInit();
    timerInit(100);
    screenGotoxy(MINX + 1, MINY + 1);
    printf("🐱🐱🐱");
    printPlayer(player_x, player_y);
    screenGotoxy(player_x, player_y - 5);
    skeleton.skull_x = skull_x;
    skeleton.skull_y = skull_y;

    printf("🗡️");

    printRooms(8, 27, 8, 16, 8, 0); // first room

    printSkull(skeleton);
    screenUpdate();

    int skull_verify = 1;

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

            int collisionXRoom1 = newY > startJRoom1 - 1 && newY < finishJRoom1;
            int collisionYRoom1 = newX >= startIRoom1 && newX < finishIRoom1;

            int collisionYHall = newX >= finishIRoom1 - strlen("🐱") && newX <= finishIHall + 1;

            if (skull_verify == 1)
            {
                printSkull(skeleton);
            }

            if (ch == 97)
            {
                // if ()

                // printSkull(skeleton);

                newX = player_x - incX;

                if (newY != 12 && (newX == finishIRoom1 - 1 && collisionXRoom1))
                {
                    newX += 1;
                }
                else if ((newX == startIRoom1 && collisionXRoom1))
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

                if (newY != 12 && (newX == finishIRoom1 - 4 && collisionXRoom1))
                {
                    newX -= 1;
                }
                else if (newX == startIRoom1 - 1 && collisionXRoom1)
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

                // printSkull(skeleton);
                newY = player_y + incY;

                if (newY == startJRoom1 && collisionYRoom1)
                {
                    newY -= 1;
                }
                else if (newY == finishJRoom1 - 1 && collisionYRoom1)
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

                // printSkull(skeleton);
                newY = player_y - incY;

                if (newY == startJRoom1 && collisionYRoom1)
                {
                    newY += 1;
                }
                else if (newY == finishJRoom1 && collisionYRoom1)
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

            printRooms(34, 44, 8, 20, 8, 1);
            printPlayer(newX, newY);
            if (newX == skull_x && newY == skull_y)
            {
                skull_verify = 0;
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