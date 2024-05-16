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

int start_I_Room0 = 8, finish_I_Room0 = 27;
int start_J_Room0 = 8, finish_J_Room0 = 16;
int door_I0 = 26, door_J0 = 12;

int start_I_Hall = 27, finish_I_Hall = 32;
int star_J_Hall = 11, finish_J_Hall = 14;

int start_I_Room2 = 34, finish_I_Room2 = 44;
int start_J_Room2 = 8, finish_J_Room2 = 20;

int incX = 1, incY = 1;


struct enemy_skull
{
    int skull_X;
    int skull_Y;
};

int skullX = 22;
int skullY = 10;

void print_Skull(struct enemy_skull isqueleto)
{
    screenGotoxy(skullX, skullY);
    printf(" ");
    skullX = isqueleto.skull_X;
    skullY = isqueleto.skull_Y;
    screenGotoxy(skullX, skullY);
    printf("💀");
}

void printPlayer(int nextX, int nextY)
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(playerX, playerY);
    printf(" ");
    playerX = nextX;
    playerY = nextY;
    screenGotoxy(playerX, playerY);
    printf("🐱");
}

void printRooms(int start_I_Room, int finish_I_Room, int start_J_Room, int finish_J_Room, int last_J, int room)
{
    screenSetColor(CYAN, DARKGRAY);
    if ((playerX + 1 == start_I_Room) && (room != 0))
    {
        for (int i = start_I_Room; i < finish_I_Room; i++)
        {
            for (int j = start_J_Room; j < finish_J_Room; j++)
            {
                if (i == door_I0 && j == door_J0)
                {
                    screenGotoxy(i, j);
                    printf("🚪");
                }
                else if (j == start_J_Room || j == finish_J_Room - 1)
                {
                    screenGotoxy(i, j);
                    printf("-");
                }
                else if (i == start_I_Room || i == finish_I_Room - 1)
                {
                    screenGotoxy(i, j);
                    printf("|");
                }

                last_J = j;
            }
            screenGotoxy(i, last_J);
            printf("\n");
        }

    }
    else if (room == 0)
    {
        for (int i = start_I_Room; i < finish_I_Room; i++)
        {
            for (int j = start_J_Room; j < finish_J_Room; j++)
            {
                if (i == door_I0 && j == door_J0)
                {
                    screenGotoxy(i, j);
                    printf("🚪");
                }
                else if (j == start_J_Room || j == finish_J_Room - 1)
                {
                    screenGotoxy(i, j);
                    printf("-");
                }
                else if (i == start_I_Room || i == finish_I_Room - 1)
                {
                    screenGotoxy(i, j);
                    printf("|");
                }

                last_J = j;
            }
            screenGotoxy(i, last_J);
            printf("\n");
        }
    }
}

void printHorizontalHall(int start_I_Hall, int finish_I_Hall, int star_J_Hall, int finish_J_Hall)
{
    if (playerX >= start_I_Hall - 2 && playerX < finish_I_Hall)
    {
        screenGotoxy(playerX + 2, star_J_Hall);
        printf("=");
        screenGotoxy(playerX + 2, finish_J_Hall - 1);
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

    
    printRooms(8, 27, 8, 16, 8, 0); //first room

    print_Skull(skeleton);

    int Skull_verify = 1;
    
    screenUpdate();

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

            int collisionXRoom0 = newY > start_J_Room0 - 1 && newY < finish_J_Room0;
            int collisionYRoom0 = newX >= start_I_Room0 && newX < finish_I_Room0;

            int collisionYHall = newX >= finish_I_Room0 - strlen("🐱") && newX <= finish_I_Hall + 1;

            if (Skull_verify == 1)
            {
                print_Skull(skeleton);
            }
            
            if (ch == 97)
            {
            
            // print_Skull(skeleton);

                newX = playerX - incX;

                if (newY != 12 && (newX == finish_I_Room0 - 1 && collisionXRoom0))
                {
                    newX += 1;
                }
                else if ((newX == start_I_Room0 && collisionXRoom0))
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

                if (newY != 12 && (newX == finish_I_Room0 - 4 && collisionXRoom0))
                {
                    newX -= 1;
                }
                else if (newX == start_I_Room0 - 1 && collisionXRoom0)
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
            
            // print_Skull(skeleton);
                newY = playerY + incY;

                if (newY == start_J_Room0 && collisionYRoom0)
                {
                    newY -= 1;
                }
                else if (newY == finish_J_Room0 - 1 && collisionYRoom0)
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
            
            
            // print_Skull(skeleton);
                newY = playerY - incY;

                if (newY == start_J_Room0 && collisionYRoom0)
                {
                    newY += 1;
                }
                else if (newY == finish_J_Room0 && collisionYRoom0)
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

            printRooms(34, 44, 8, 20, 8, 2);
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