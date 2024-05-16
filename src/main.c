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
#include <unistd.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define STARTIROOM1 8
#define FINISHIROOM1 27
#define STARTJROOM1 8
#define FINISHJROOM1 16

#define STARTIROOM2 34
#define FINISHIROOM2 44
#define STARTJROOM2 8
#define FINISHJROOM2 20

#define STARTIHALL1 27
#define FINISHIHALL1 32
#define STARTJHALL1 11
#define FINISHJHALL1 14

#define STARTIHALL2 44
#define FINISHIHALL2 48
#define STARTJHALL2 16
#define FINISHJHALL2 19

#define DOORI1 26
#define DOORJ1 12

char *enemies[] = {"💀", "👿", "👹", "👻"};

int incX = 1, incY = 1;

int player_x = 16, player_y = 14;

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
};

void print_enemy(struct enemy_obj enemy, int new_enemy_x, int new_enemy_y)
{
    srand(time(NULL));
    int rand_emoji = (rand()%4);
    screenGotoxy(enemy.x, enemy.y);
    printf(" ");
    enemy.x = new_enemy_x;
    enemy.y = new_enemy_y;
    screenGotoxy(enemy.x, enemy.y);
    printf("%s", enemies[rand_emoji]);
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

void print_sword(int pos_X ,int pos_Y)
{
    int cont = 8;
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
        
        usleep(5000); // AQUI ANA CLAUDIA

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
                if (i == DOORI1 && j == DOORJ1)
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
                if (i == DOORI1 && j == DOORJ1)
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
void printHp(int health){
    screenGotoxy(MINX + 1, MINY + 1);
        printf("      ");
        for (int h = 1; h<health+1; h++){
            screenGotoxy(MINX + h + h, MINY + 1);
            screenSetColor(RED, DARKGRAY);
            printf("♥");
            screenSetColor(CYAN, DARKGRAY);
        }
        if (health == 0){
            
            printf("voce morreu");
        }
    
}

int main()
{
    static int ch = 0;
    struct player player;
    struct enemy_obj skeleton;
    struct enemy_obj enemy_room_2;

    skeleton.x = 22;
    skeleton.y = 10;

    enemy_room_2.x = 36;
    enemy_room_2.y = 10;
    enemy_room_2.inc_x = 1;
    enemy_room_2.is_dead = 1;

    player.sword = 0;
    player.shield = 0;
    player.steps = 0;
    player.score = 0;
    player.hp = 3;
    screenInit(1);
    keyboardInit();
    timerInit(150);

    screenGotoxy(MINX + 1, MINY + 1);
    
    printHp(player.hp);
    //printf("🐱🐱🐱");

    printf("\t┃ Iventory ┃");
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
    printf("🗡️");

    printRooms(STARTIROOM1, FINISHIROOM1, STARTJROOM1, FINISHJROOM1, 0); // first room

    print_enemy(skeleton, skeleton.x, skeleton.y);
    print_enemy(enemy_room_2, enemy_room_2.x, enemy_room_2.y);
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

            int collisionYHall = newX >= FINISHIROOM1 - strlen("🐱") && newX <= FINISHIHALL1 + 1;

            if (enemy_room_2.x >= FINISHIROOM2 - strlen("    ") || enemy_room_2.x - 2 < STARTIROOM2)
            {
                enemy_room_2.inc_x = -enemy_room_2.inc_x;
            }

            if (ch == 97)
            {
                newX = player_x - incX;

                
                

                // Colisão room 0
                if ((newX == FINISHIROOM1 - 1 && collisionXRoom1))
                {
                    newX += 1;
                }
                else if (newY != 12 && (newX == STARTIROOM1 && collisionXRoom1))
                {
                    newX += 1;
                }

                // Colisão room 2
                if (newY != 12 && (newX == FINISHIROOM2 - 1 && collisionXRoom2))
                {
                    newX += 1;
                }
                else if (newX == STARTIROOM2 && collisionXRoom2)
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
                if (newY != 12 && (newX == FINISHIROOM1 - 4 && collisionXRoom1))
                {
                    newX -= 1;
                }
                else if (newX == STARTIROOM1 - 1 && collisionXRoom1)
                {
                    newX -= 1;
                }

                if (newX == FINISHIROOM2 - 4 && collisionXRoom2)
                {
                    newX -= 1;
                }
                else if (newY != 12 && (newX == STARTIROOM2 - 1 && collisionXRoom2))
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

                if (newY == STARTJROOM1 && collisionYRoom1)
                {
                    newY -= 1;
                }
                else if (newY == FINISHJROOM1 - 1 && collisionYRoom1)
                {
                    newY -= 1;
                }

                if (newY == STARTJROOM2 && collisionYRoom2)
                {
                    newY -= 1;
                }
                else if (newY == FINISHJROOM2 - 1 && collisionYRoom2)
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

                if (newY == STARTJROOM1 && collisionYRoom1)
                {
                    newY += 1;
                }
                else if (newY == FINISHJROOM1 && collisionYRoom1)
                {
                    newY += 1;
                }

                if (newY == STARTJROOM2 && collisionYRoom2)
                {
                    newY += 1;
                }
                else if (newY == FINISHJROOM2 && collisionYRoom2)
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

            if (ch == 32 && player.sword == 1) 
            {
                print_sword(newX, newY);
                ch = 0;
                
                
            }

            printHorizontalHall(STARTIHALL1, FINISHIHALL1, STARTJHALL1, FINISHJHALL1);
            printHorizontalHall(STARTIHALL2, FINISHIHALL2, STARTJHALL2, FINISHJHALL2);

            printRooms(STARTIROOM2, FINISHIROOM2, STARTJROOM2, FINISHJROOM2, 2);
            print_player(newX, newY);

            if (enemy_room_2.x == newX && enemy_room_2.y == newY){
                player.hp--; // mudar
                printHp(player.hp);
            }
            print_enemy(enemy_room_2, enemy_room_2.x, enemy_room_2.y);
            

            if ((newX == 16 || newX == 15) && newY == 9)
            {
                player.sword = 1;
            }

            if (player.sword == 1)
            {   
                screenSetColor(WHITE, DARKGRAY);
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