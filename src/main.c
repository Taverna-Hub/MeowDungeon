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

int playerX = 16, playerY = 14;

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
    int skull_X;
    int skull_Y;
};

int skullX = 22;
int skullY = 10;

void printSkull(struct enemy_skull isqueleto){
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(skullX, skullY);
    printf("    ");
    skullX = isqueleto.skull_X;
    skullY = isqueleto.skull_Y;
    screenGotoxy(skullX, skullY);
    printf("💀");
}

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

void printRooms(int starIRoom, int finishIRoom, int startJRoom, int finishJRoom, int lastJ, int room)
{
    screenSetColor(CYAN, DARKGRAY);
    if ((playerX + 1 == starIRoom) && (room != 0))
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
    if (playerX >= startIHall - 2 && playerX < finishIHall)
    {
        screenGotoxy(playerX + 2, starJHall);
        printf("=");
        screenGotoxy(playerX + 2, finishJHall - 1);
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
    printPlayer(playerX, playerY);
    screenGotoxy(playerX, playerY - 5);
    skeleton.skull_X = skullX;
    skeleton.skull_Y = skullY;

    printf("🗡️");

    screenUpdate();

    printRooms(8, 27, 8, 16, 8, 0); //first room


    printRoom1();
    printSkull(skeleton);
    screenUpdate();

    int Skull_verify = 1;

    while (ch != 10)
    {
        if (keyhit())
        {
            ch = readch();
            printKey(ch);
            screenUpdate();
        }

        screenGotoxy(MINX + 1, MINY + 2);
        printf("%d %d", playerX, playerY);

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1)
        {

            int newX = playerX, newY = playerY;

            int collisionXRoom1 = newY > startJRoom1 - 1 && newY < finishJRoom1;
            int collisionYRoom1 = newX >= startIRoom1 && newX < finishIRoom1;

            int collisionYHall = newX >= finishIRoom1 - strlen("🐱") && newX <= finishIHall + 1;

            if (Skull_verify == 1)
            {
                printSkull(skeleton);
            }
            
            if (ch == 97)
            {
                // if ()
            
            // printSkull(skeleton);

                newX = playerX - incX;

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
                
                newX = playerX + incX;

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
                newY = playerY + incY;

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
                newY = playerY - incY;

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
            if (newX == skullX && newY == skullY){
                Skull_verify = 0;
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