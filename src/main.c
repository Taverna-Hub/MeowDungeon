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

int playerX = 10, playerY = 12;
int startIRoom1 = 8, finishIRoom1 = 27;
int startJRoom1 = 8, finishJRoom1 = 16;

int incX = 1, incY = 1;

void printPlayer(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(playerX, playerY);
    printf("    ");
    playerX = nextX;
    playerY = nextY;
    screenGotoxy(playerX, playerY);
    printf("🐱");
}

void printRoom1()
{
    int lastJ = 8;
    for (int i = startIRoom1; i < finishIRoom1; i++)
    {
        for (int j = startJRoom1; j < finishJRoom1; j++)
        {
            if (i == finishIRoom1 - 1 && j == 12)
            {
                screenGotoxy(i, j);
                printf("🚪");
            }
            else if (i == startIRoom1 || i == finishIRoom1 - 1)
            {
                screenGotoxy(i, j);
                printf("|");
            }
            else if (j == startJRoom1)
            {
                screenGotoxy(i, j);
                printf("‾");
            }
            else if (j == finishJRoom1 - 1)
            {
                screenGotoxy(i, j);
                printf("_");
            }

            lastJ = j;
        }
        screenGotoxy(i, lastJ);
        printf("\n");
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

    screenInit(1);
    keyboardInit();
    timerInit(100);

    screenGotoxy(MINX + 1, MINY + 1);
    printf("🐱🐱🐱");
    printPlayer(playerX, playerY);
    printRoom1();
    screenUpdate();

    while (ch != 10)
    {
        if (keyhit())
        {
            ch = readch();
            printKey(ch);
            screenUpdate();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1)
        {
            int newX = playerX, newY = playerY;
            if (ch == 97)
            {
                newX = playerX - incX;

                if (newY != 12 && (newX == finishIRoom1 - 1 && newY > startJRoom1 && newY < finishJRoom1 || newX == finishIRoom1 - 1 && playerY > startJRoom1 && playerY < finishJRoom1))
                {
                    newX += 1;
                }
                else if ((newX == startIRoom1 && newY > startJRoom1 && newY < finishJRoom1 || newX == startIRoom1 && playerY > startJRoom1 && playerY < finishJRoom1))
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
                newX = playerX + incX;

                if (newY != 12 && (newX == finishIRoom1 - 4 && newY > startJRoom1 && newY < finishJRoom1 || newX == finishIRoom1 - 4 && playerY > startJRoom1 && playerY < finishJRoom1))
                {
                    newX -= 1;
                }
                else if (newX == startIRoom1 - 1 && newY > startJRoom1 && newY < finishJRoom1 || newX == startIRoom1 - 1 && playerY > startJRoom1 && playerY < finishJRoom1)
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
                newY = playerY + incY;

                if (newY == startJRoom1 && newX > startIRoom1 && newX < finishIRoom1 || newY == startJRoom1 && playerX > startIRoom1 && playerX < finishIRoom1)
                {
                    newY -= 1;
                }
                else if (newY == finishJRoom1 - 1 && newX > startIRoom1 && newX < finishIRoom1 || newY == finishJRoom1 - 1 && playerX > startIRoom1 && playerX < finishIRoom1)
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
                newY = playerY - incY;

                if (newY == startJRoom1 && newX > startIRoom1 && newX < finishIRoom1 || newY == startJRoom1 && playerX > startIRoom1 && playerX < finishIRoom1)
                {
                    newY += 1;
                }
                else if (newY == finishJRoom1 && newX > startIRoom1 && newX < finishIRoom1 || newY == finishJRoom1 && playerX > startIRoom1 && playerX < finishIRoom1)
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

            printPlayer(newX, newY);

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