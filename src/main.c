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
#include "var.h"

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
    int shield_active;
    int score;
    int steps;
    int hp;
};

struct enemy_obj
{
    int x;
    int y;
    int previous_x;
    int previous_y;
    int is_dead;
    int inc_x;
    int inc_y;
    char *sprite;
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

struct score
{
    int points;
    char *name;
    struct score *next;
};

void print_subroom(int start_i_room, int finish_i_room, int start_j_room, int finish_j_room, int *room_enemies)
{
    int last_j = start_j_room;
    if (*room_enemies)
    {
        for (int i = start_i_room; i < finish_i_room; i++)
        {
            for (int j = start_j_room; j < finish_j_room; j++)
            {
                if (j == start_j_room || j == finish_j_room - 1)
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

void print_trap(struct trap_obj trap, int new_trap_x, int new_trap_y, int direction)
{
    screenGotoxy(trap.previous_x, trap.previous_y);
    printf(" ");
    trap.x = new_trap_x;
    trap.y = new_trap_y;
    screenGotoxy(trap.x, trap.y);
    switch (direction)
    {
    case 1:
        printf("↑");
        break;
    case 2:
        printf("↓");
        break;

    case 3:
        printf("←");
        break;

    case 4:
        printf("→");
        break;
    }
}

int sum_score(int killed_enemies, int steps, int lifes, int itens_count)
{
    int total = (killed_enemies * 100) + (lifes * 500) + (itens_count * 250);
    if (steps > 150)
    {
        total = total - (steps / 30);
    }

    return total;
}

void print_enemy(struct enemy_obj enemy)
{
    screenGotoxy(enemy.previous_x, enemy.previous_y);
    printf(" ");
    screenGotoxy(enemy.x, enemy.y);
    printf("%s", enemy.sprite);
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

void print_shield(struct player *p) 
{
    int *point;
    point = &p->shield_active;

    screenGotoxy(MINX + 1, MINY + 2);
    printf("                   ");
    for (int s = 1; s < p->shield + 1; s++)
    {
        screenGotoxy(MINX + s + s, MINY + 2);
        screenSetColor(LIGHTGREEN, DARKGRAY);
        printf("🛡");
    }
    if ( p->shield  == 0)
    {
        screenGotoxy(MINX + 1, MINY + 2);
        printf(" Shield broken! ");
        *point = -1;
    }
}

void print_hp(int health)
{
    screenGotoxy(MINX + 2, MINY + 1);
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
        screenGotoxy(MINX + 2, MINY + 1);
        printf("☠️ You died! ☠️");
    }
}

void print_rooms(int start_i_room, int finish_i_room, int start_j_room, int finish_j_room, int room, int *room_enemies, int enter_door_i, int enter_door_j, int exit_door_i, int exit_door_j)
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

void print_horizontal_hall(int start_i_hall, int finish_i_hall, int start_j_hall, int finish_j_hall)
{
    if (player_x >= start_i_hall - 2 && player_x < finish_i_hall && player_y > start_j_hall && player_y < finish_j_hall)
    {
        screenGotoxy(player_x + 2, start_j_hall);
        printf("═");
        screenGotoxy(player_x + 2, finish_j_hall - 1);
        printf("═");
    }
}

void print_vertical_hall(int start_i_hall, int finish_i_hall, int start_j_hall, int finish_j_hall)
{
    if ((player_y >= start_j_hall) && (player_y < finish_j_hall))
    {
        screenGotoxy(start_i_hall, player_y);
        printf("║");
        screenGotoxy(finish_i_hall, player_y);
        printf("║");
    }
}

void print_key(int ch)
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

void print_steps(struct player p)
{
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(130, 2);
    printf("Steps:");

    screenGotoxy(129, 3);
    printf("    ");
    printf("%d", p.steps);
}

void ascii_print(char *path)
{
    FILE *file;
    char string[128];

    file = fopen(path, "r");

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

void add_score(struct score **head, int points, char *nome)
{
    struct score *node = *head;
    struct score *new = (struct score *)malloc(sizeof(struct score));
    // todo
    new->points = points;
    new->name = (char *)malloc((strlen(nome) + 1) * sizeof(char));
    new->next = NULL;

    strcpy(new->name, nome);

    if (*head == NULL)
    {
        *head = new;
    }

    else if ((*head)->points < points)
    {
        new->next = *head;
        *head = new;
    }

    else
    {
        while (node->next != NULL && node->next->points > points)
        {
            node = node->next;
        }

        new->next = node->next;
        node->next = new;
    }
}

void print_score(struct score *head)
{
    struct score *node = head;
    int cont = 1, y = 11;

    while (node != NULL)
    {
        screenGotoxy(60, y);
        printf("%d. %s - %d\n", cont, node->name, node->points);
        cont++;
        y++;
        node = node->next;

        if (cont == 11)
            break;
    }
}

void free_score(struct score *head)
{
    struct score *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->name);
        free(temp);
    }
}

int menu_cont = 0;
void menu()
{
    static int ch = 0;

    screenSetColor(LIGHTRED, DARKGRAY);
    ascii_print("src/files/menu.txt");

    screenSetColor(LIGHTGRAY, DARKGRAY);
    screenGotoxy(60, 19);
    printf("START GAME");
    screenGotoxy(62, 21);
    printf("SCORES");
    screenGotoxy(63, 23);
    printf("EXIT");

    screenSetColor(LIGHTRED, DARKGRAY);

    while (ch != 10)
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
}

int main()
{
    srand(time(NULL));
    int inc_values[] = {-1, 1};

    static int ch = 0;
    struct score *list = NULL;
    struct player player;

    // Room 1
    struct enemy_obj enemy_room_1;

    // Room 2
    struct enemy_obj enemy_room_2;

    // Room 3
    struct trap_obj traps_room_3[5];

    int traps_room_3_x_values[] = {40, 50, 60, 70, 80};
    int traps_room_3_y_values[] = {FINISHJROOM3 - 1, STARTJROOM3 + 1};

    // Room 4
    struct enemy_obj enemies_room_4[ENEMIES4LENGTH];
    struct trap_obj traps_room_4[TRAPS4LENGTH];

    int enemies_room_4_x_values[] = {FINISHIROOM4 - 4, STARTIROOM4 + 1};
    int enemies_room_4_y_values[] = {21, 17};

    int traps_room_4_x_values[] = {FINISHIROOM4 - 2, STARTIROOM4 + 1};
    int traps_room_4_y_values[] = {26, 24, 22, 20, 18, 16, 14};

    // Room 5
    struct enemy_obj enemies_room_5[ENEMIES5LENGTH];
    int enemies_room_5_x_values[] = {64, 58, 64, 69};
    int enemies_room_5_y_values[] = {15, 13, 11, 13};
    int enemies_room_5_inc_x_values[] = {-1, 0, 1, 0};
    int enemies_room_5_inc_y_values[] = {0, -1, 0, 1};

    // enemies cont
    int enemies_cont = 0;
    int cont1_1 = 0;
    int cont2_1 = 0;
    int cont4_1 = 0;
    int cont4_2 = 0;
    int cont5_1 = 0;
    int cont5_2 = 0;
    int cont5_3 = 0;
    int cont5_4 = 0;

    // Room 3 traps
    for (int i = 0; i < 5; i++)
    {
        traps_room_3[i].x = traps_room_3_x_values[i];
        traps_room_3[i].y = traps_room_3_y_values[i % 2];
        traps_room_3[i].previous_x = traps_room_3_x_values[i];
        traps_room_3[i].previous_y = traps_room_3_y_values[i % 2];
        traps_room_3[i].inc_y = inc_values[i % 2];
    }

    // Room 4 traps
    for (int i = 0; i < TRAPS4LENGTH; i++)
    {
        traps_room_4[i].x = traps_room_4_x_values[i % 2];
        traps_room_4[i].y = traps_room_4_y_values[i];
        traps_room_4[i].previous_x = traps_room_4_x_values[i % 2];
        traps_room_4[i].previous_y = traps_room_4_y_values[i];
        traps_room_4[i].inc_x = inc_values[i % 2];
    }

    // Room 4 enemies
    for (int i = 0; i < ENEMIES4LENGTH; i++)
    {
        enemies_room_4[i].x = enemies_room_4_x_values[i % 2];
        enemies_room_4[i].y = enemies_room_4_y_values[i];
        enemies_room_4[i].previous_x = enemies_room_4_x_values[i % 2];
        enemies_room_4[i].previous_y = enemies_room_4_y_values[i];
        enemies_room_4[i].inc_x = inc_values[i % 2];
        enemies_room_4[i].is_dead = 0;
        enemies_room_4[i].sprite = enemies[(rand() % 7)];
    }

    // Room 5 enemies
    for (int i = 0; i < ENEMIES5LENGTH; i++)
    {
        enemies_room_5[i].x = enemies_room_5_x_values[i];
        enemies_room_5[i].y = enemies_room_5_y_values[i];
        enemies_room_5[i].previous_x = enemies_room_5_x_values[i];
        enemies_room_5[i].previous_y = enemies_room_5_y_values[i];
        enemies_room_5[i].inc_x = enemies_room_5_inc_x_values[i];
        enemies_room_5[i].inc_y = enemies_room_5_inc_y_values[i];
        enemies_room_5[i].is_dead = 0;
        enemies_room_5[i].sprite = enemies[i + 1];
    }

    enemy_room_1.x = 22;
    enemy_room_1.y = 10;
    enemy_room_1.is_dead = 0;
    enemy_room_1.sprite = enemies[(rand() % 7)];

    enemy_room_2.x = 36;
    enemy_room_2.y = 17;
    enemy_room_2.inc_x = 1;
    enemy_room_2.is_dead = 0;
    enemy_room_2.sprite = enemies[(rand() % 7)];

    player.sword = 0;
    player.shield = 0;
    player.shield_active = 0;
    player.steps = 0;
    player.score = 0;
    player.hp = 3;

    // initial screen display
    screenInit(0);
    keyboardInit();
    menu();
    ch = 0;

    if (menu_cont == 2)
    {
        printf("\n");
        keyboardDestroy();
        screenDestroy();
        printf("fechou :D\n");
        return 0;
    }

    else if (menu_cont == 1)
    {
        screenDestroy();
        keyboardDestroy();

        screenInit(0);
        keyboardInit();

        char *token;
        FILE *file;
        file = fopen("src/files/score.txt", "r");

        if (file == NULL)
        {
            perror("File not found");
            return 1;
        }

        char readLine[128], name[6], points[10];

        while (fgets(readLine, sizeof(readLine), file) != NULL)
        {
            token = strtok(readLine, " ");
            strncpy(name, token, 5);
            name[5] = '\0';

            token = strtok(NULL, " ");
            strncpy(points, token, 9);
            points[9] = '\0';

            int int_points = atoi(points);
            add_score(&list, int_points, name);
        }

        fclose(file);

        screenSetColor(LIGHTRED, DARKGRAY);
        screenGotoxy(60, 3);
        ascii_print("src/files/topscores.txt");

        screenGotoxy(56, 22);
        printf(">");
        screenGotoxy(80, 22);
        printf("<");

        screenSetColor(LIGHTGRAY, DARKGRAY);

        screenGotoxy(58, 22);
        printf("PRESS [ENTER] TO EXIT");
        print_score(list);
        free_score(list);

        while (ch != 10)
        {
            if (keyhit())
            {
                ch = readch();
            }
        }
        ch = 0;

        printf("\n");
        keyboardDestroy();
        screenDestroy();
        printf("fechou :D\n");
        return 0;
    }

    else
    {
        screenSetColor(LIGHTGRAY, DARKGRAY);
        screenInit(1);
        timerInit(150);

        screenGotoxy(MINX + 1, MINY + 1);

        print_hp(player.hp);

        screenSetColor(WHITE, DARKGRAY);
        screenGotoxy(MINX + 35, MINY + 1);
        printf("┃ Inventory ┃");

        print_player(player_x, player_y);

        screenGotoxy(player_x, player_y - 5);
        printf("🗡️");

        print_rooms(STARTIROOM1, FINISHIROOM1, STARTJROOM1, FINISHJROOM1, 0, &enemies1, DOORI1, DOORJ1, DOORI1, DOORJ1); // first room

        screenUpdate();

        while (ch != 10)
        {
            if (keyhit())
            {
                ch = readch();
                print_key(ch);
                screenUpdate();
            }

            screenGotoxy(MINX + 1, MINY + 4);
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

                int collisionXRoom5 = newY > STARTJROOM5 - 1 && newY < FINISHJROOM5;
                int collisionYRoom5 = newX >= STARTIROOM5 && newX < FINISHIROOM5;

                int collisionYHall1 = newX >= FINISHIROOM1 - strlen("🐱") && newX <= FINISHIHALL1 + 1 && newY > STARTJHALL1 && newY < FINISHJHALL1;
                int collisionXHall2 = newY >= FINISHJROOM2 && newY <= FINISHJHALL2 + 1 && newX > STARTIHALL2 && newX < FINISHIHALL2;
                int collisionYHall3 = newX >= FINISHIROOM3 - strlen("🐱") && newX <= FINISHIHALL3 + 1 && newY > STARTJHALL3 && newY < FINISHJHALL3;
                int collisionYHall4 = newX < STARTIHALL4 + strlen("🐱") && newX >= FINISHIHALL4 - 1 && newY > STARTJHALL4 && newY < FINISHJHALL4;

                if (!enemy_room_1.is_dead)
                {
                    print_enemy(enemy_room_1);
                }
                if (enemy_room_1.is_dead && cont1_1 == 0)
                {
                    cont1_1++;
                    enemies_cont++;
                }
                if (enemy_room_2.x == newX && enemy_room_2.y == newY && !enemy_room_2.is_dead)
                {
                    if (player.shield_active == 1)
                    {
                        player.shield--;
                        print_shield(&player);
                    }
                    else if (player.shield_active == 0 || player.shield_active == -1)
                    {
                        player.hp--;
                        print_hp(player.hp);
                    }
                }

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
                        player.steps--;
                    }
                    else if (newY != DOORJ1 && newX == STARTIROOM1 && collisionXRoom1)
                    {
                        newX += 1;
                        player.steps--;
                    }

                    // Colisão room 2
                    if (newY != 12 && newX == FINISHIROOM2 - 1 && collisionXRoom2)
                    {
                        newX += 1;
                        player.steps--;
                    }
                    else if (newX == STARTIROOM2 && collisionXRoom2)
                    {
                        newX += 1;
                        player.steps--;
                    }

                    // Colisão room 3
                    if (newX == FINISHIROOM3 - 1 && collisionXRoom3)
                    {
                        newX += 1;
                        player.steps--;
                    }
                    else if (newX == STARTIROOM3 && collisionXRoom3)
                    {
                        newX += 1;
                        player.steps--;
                    }

                    // Colisão room 4
                    if (newX == FINISHIROOM4 - 1 && collisionXRoom4)
                    {
                        newX += 1;
                        player.steps--;
                    }
                    else if (newY != EXITDOORJ4 && newX == STARTIROOM4 && collisionXRoom4)
                    {
                        newX += 1;
                        player.steps--;
                    }

                    // Colisão room 5
                    if (newY != ENTERDOORJ5 && newX == FINISHIROOM5 - 1 && collisionXRoom5)
                    {
                        newX += 1;
                        player.steps--;
                    }
                    else if (newX == STARTIROOM5 && collisionXRoom5)
                    {
                        newX += 1;
                        player.steps--;
                    }

                    if (collisionXHall2)
                    {
                        newX += 1;
                        player.steps--;
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

                    // ROOM 1
                    if (newY != DOORJ1 && (newX == FINISHIROOM1 - 2 && collisionXRoom1))
                    {
                        newX -= 1;
                        player.steps--;
                    }
                    else if (newX == STARTIROOM1 - 1 && collisionXRoom1)
                    {
                        newX -= 1;
                        player.steps--;
                    }

                    // ROOM 2
                    if (newX == FINISHIROOM2 - 2 && collisionXRoom2)
                    {
                        newX -= 1;
                        player.steps--;
                    }
                    else if (newY != 12 && (newX == STARTIROOM2 - 1 && collisionXRoom2))
                    {
                        newX -= 1;
                        player.steps--;
                    }

                    // ROOM 3
                    if (newY != EXITDOORJ3 && newX == FINISHIROOM3 - 2 && collisionXRoom3)
                    {
                        newX -= 1;
                        player.steps--;
                    }
                    else if (newX == STARTIROOM3 - 1 && collisionXRoom3)
                    {
                        newX -= 1;
                        player.steps--;
                    }

                    // ROOM 4
                    if (newX == FINISHIROOM4 - 2 && collisionXRoom4)
                    {
                        newX -= 1;
                        player.steps--;
                    }
                    else if (newY != ENTERDOORJ4 && newX == STARTIROOM4 - 1 && collisionXRoom4)
                    {
                        newX -= 1;
                        player.steps--;
                    }

                    // ROOM 5
                    if (newX == FINISHIROOM5 - 2 && collisionXRoom5)
                    {
                        newX -= 1;
                        player.steps--;
                    }
                    else if (newY != ENTERDOORJ5 && newX == STARTIROOM5 - 1 && collisionXRoom5)
                    {
                        newX -= 1;
                        player.steps--;
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
                        player.steps--;
                    }
                    else if (newY == FINISHJROOM1 - 1 && collisionYRoom1)
                    {
                        newY -= 1;
                        player.steps--;
                    }

                    // Colisão room 2
                    if (newY == STARTJROOM2 && collisionYRoom2)
                    {
                        newY -= 1;
                        player.steps--;
                    }
                    else if (newX != EXITDOORI2 && newY == FINISHJROOM2 - 1 && collisionYRoom2)
                    {
                        newY -= 1;
                        player.steps--;
                    }

                    // Colisão room 3
                    if (newY != ENTERDOORJ3 && newY == STARTJROOM3 && collisionYRoom3)
                    {
                        newY -= 1;
                        player.steps--;
                    }
                    else if (newY == FINISHJROOM3 - 1 && collisionYRoom3)
                    {
                        newY -= 1;
                        player.steps--;
                    }

                    // Colisão room 4
                    if (newY != ENTERDOORJ4 && newY == STARTJROOM4 && collisionYRoom4)
                    {
                        newY -= 1;
                        player.steps--;
                    }
                    else if (newY == FINISHJROOM4 - 1 && collisionYRoom4)
                    {
                        newY -= 1;
                        player.steps--;
                    }

                    // Colisão room 5
                    if (newY != ENTERDOORJ5 && newY == STARTJROOM5 && collisionYRoom5)
                    {
                        newY -= 1;
                        player.steps--;
                    }
                    else if (newY == FINISHJROOM5 - 1 && collisionYRoom5)
                    {
                        newY -= 1;
                        player.steps--;
                    }

                    if (collisionYHall1 || collisionYHall3 || collisionYHall4)
                    {
                        newY -= 1;
                        player.steps--;
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
                        player.steps--;
                    }
                    else if (newY == FINISHJROOM1 && collisionYRoom1)
                    {
                        newY += 1;
                        player.steps--;
                    }

                    // Colisão room 2
                    if (newY == STARTJROOM2 && collisionYRoom2)
                    {
                        newY += 1;
                        player.steps--;
                    }
                    else if (newY == FINISHJROOM2 && collisionYRoom2)
                    {
                        newY += 1;
                        player.steps--;
                    }

                    // Colisão room 3
                    if (newY == STARTJROOM3 && collisionYRoom3)
                    {
                        newY += 1;
                        player.steps--;
                    }
                    else if (newY == FINISHJROOM3 && collisionYRoom3)
                    {
                        newY += 1;
                        player.steps--;
                    }

                    // Colisão room 4
                    if (newY == STARTJROOM4 && collisionYRoom4)
                    {
                        newY += 1;
                        player.steps--;
                    }
                    else if (newY == FINISHJROOM4 && collisionYRoom4)
                    {
                        newY += 1;
                        player.steps--;
                    }

                    // Colisão room 5
                    if (newY == STARTJROOM5 && collisionYRoom5)
                    {
                        newY += 1;
                        player.steps--;
                    }
                    else if (newY == FINISHJROOM5 && collisionYRoom5)
                    {
                        newY += 1;
                        player.steps--;
                    }

                    if (collisionYHall1 || collisionYHall3 || collisionYHall4)
                    {
                        newY += 1;
                        player.steps--;
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

                if (((ch == 106) || (ch == 74)) && (player.sword == 1)) // sword
                {
                    print_sword(newX, newY);
                    if (sqrt(pow((newX - enemy_room_2.x), 2) + pow((newY - enemy_room_2.y), 2)) <= 2)
                    {
                        enemy_room_2.is_dead = 1;
                    }
                    if (sqrt(pow((newX - enemy_room_1.x), 2) + pow((newY - enemy_room_1.y), 2)) <= 2)
                    {
                        enemy_room_1.is_dead = 1;
                    }

                    for (int i = 0; i < ENEMIES4LENGTH; i++)
                    {
                        float distance = sqrt(pow((newX - enemies_room_4[i].x), 2) + pow((newY - enemies_room_4[i].y), 2));
                        if (distance <= 2)
                        {
                            enemies_room_4[i].is_dead = 1;
                        }
                    }

                    for (int i = 0; i < ENEMIES5LENGTH; i++)
                    {
                        float distance = sqrt(pow((newX - enemies_room_5[i].x), 2) + pow((newY - enemies_room_5[i].y), 2));
                        if (distance <= 2)
                        {
                            enemies_room_5[i].is_dead = 1;
                        }
                    }

                    ch = 0;
                }

                if (((ch == 107) || (ch == 75)) && (player.shield != 0 && player.shield <= 5)) // shield
                {
                    if (!player.shield_active)
                    {
                        player.shield_active = 1;
                    }
                    else
                    {
                        player.shield_active = 0;
                    }

                    ch = 0;
                }

                print_horizontal_hall(STARTIHALL1, FINISHIHALL1, STARTJHALL1, FINISHJHALL1);
                print_horizontal_hall(STARTIHALL3, FINISHIHALL3, STARTJHALL3, FINISHJHALL3);
                print_horizontal_hall(FINISHIHALL4, STARTIHALL4, STARTJHALL4, FINISHJHALL4);
                print_vertical_hall(STARTIHALL2, FINISHIHALL2, STARTJHALL2, FINISHJHALL2);

                print_rooms(STARTIROOM2, FINISHIROOM2, STARTJROOM2, FINISHJROOM2, 2, &enemies2, ENTERDOORI2, ENTERDOORJ2, EXITDOORI2, EXITDOORJ2);
                print_rooms(STARTIROOM3, FINISHIROOM3, STARTJROOM3, FINISHJROOM3, 3, &enemies3, ENTERDOORI3, ENTERDOORJ3, EXITDOORI3, EXITDOORJ3);
                print_rooms(STARTIROOM4, FINISHIROOM4, STARTJROOM4, FINISHJROOM4, 4, &enemies4, ENTERDOORI4, ENTERDOORJ4, EXITDOORI4, EXITDOORJ4);
                print_rooms(STARTIROOM5, FINISHIROOM5, STARTJROOM5, FINISHJROOM5, 5, &enemies5, ENTERDOORI5, ENTERDOORJ5, EXITDOORI5, EXITDOORJ5);
                print_subroom(STARTITRAPDOOR5, FINISHITRAPDOOR5, STARTJTRAPDOOR5, FINISHJTRAPDOOR5, &enemies5);

                print_player(newX, newY);
                print_steps(player);

                if (enemy_room_1.x == newX && enemy_room_1.y == newY && !enemy_room_1.is_dead)
                {
                    if (player.shield_active == 1)
                    {
                        player.shield--;
                        print_shield(&player);
                    }
                    else if (player.shield_active == 0 || player.shield_active == -1)
                    {
                        player.hp--;
                        print_hp(player.hp);
                    }
                }

                if (enemy_room_2.x == newX && enemy_room_2.y == newY && !enemy_room_2.is_dead)
                {
                    if (player.shield_active)
                    {
                        player.shield--;
                        print_shield(&player);
                    }
                    else if (player.shield_active == -1)
                    {
                        player.hp--;
                        print_hp(player.hp);
                    }
                    else
                    {
                        player.hp--;
                        print_hp(player.hp);
                    }
                }

                if (enemies2 == 1 && !enemy_room_2.is_dead)
                {
                    print_enemy(enemy_room_2);
                }

                if (enemy_room_2.is_dead && cont2_1 == 0)
                {
                    cont2_1++;
                    enemies_cont++;
                }

                if (enemies3)
                {
                    if (!player.shield && player.shield_active != -1)
                    {
                        screenGotoxy(30, 29);
                        printf("🛡️");
                    }

                    for (int i = 0; i < 5; i++)
                    {
                        traps_room_3[i].previous_y = traps_room_3[i].y;
                        traps_room_3[i].y = traps_room_3[i].y + traps_room_3[i].inc_y;
                    }

                    if (traps_room_3[0].y == STARTJROOM3 || traps_room_3[2].y == STARTJROOM3 || traps_room_3[4].y == STARTJROOM3)
                    {
                        traps_room_3[0].y = FINISHJROOM3 - 2;
                        traps_room_3[2].y = FINISHJROOM3 - 2;
                        traps_room_3[4].y = FINISHJROOM3 - 2;
                    }

                    if (traps_room_3[1].y == FINISHJROOM3 - 1 || traps_room_3[3].y == FINISHJROOM3 - 1)
                    {
                        traps_room_3[1].y = STARTJROOM3 + 1;
                        traps_room_3[3].y = STARTJROOM3 + 1;
                    }

                    for (int i = 0; i < 5; i++)
                    {
                        if (i % 2 == 0)
                        {
                            print_trap(traps_room_3[i], traps_room_3[i].x, traps_room_3[i].y, 1);
                        }
                        else
                        {
                            print_trap(traps_room_3[i], traps_room_3[i].x, traps_room_3[i].y, 2);
                        }

                        if ((player_x == traps_room_3[i].x && player_y == traps_room_3[i].y) || (player_x + 1 == traps_room_3[i].x && player_y == traps_room_3[i].y))
                        {
                            if (player.shield == 0)
                            {
                                player.shield_active = 0;
                            }

                            if (player.shield_active == 1)
                            {
                                player.shield--;
                                print_shield(&player);
                            }
                            else
                            {
                                player.hp--;
                                print_hp(player.hp);
                            }
                        }
                    }
                }

                if (enemies4) // TODO
                {
                    for (int i = 0; i < ENEMIES4LENGTH; i++)
                    {
                        enemies_room_4[i].previous_x = enemies_room_4[i].x;
                        enemies_room_4[i].x = enemies_room_4[i].x + enemies_room_4[i].inc_x;
                    }

                    for (int i = 0; i < ENEMIES4LENGTH; i++)
                    {
                        if (enemies_room_4[i].x == STARTIROOM4 + 1 || enemies_room_4[i].x == FINISHIROOM4 - 4)
                        {
                            enemies_room_4[i].inc_x = -enemies_room_4[i].inc_x;
                        }
                    }

                    for (int i = 0; i < ENEMIES4LENGTH; i++)
                    {
                        if (!enemies_room_4[i].is_dead)
                        {
                            print_enemy(enemies_room_4[i]);
                        }
                    }

                    for (int i = 0; i < TRAPS4LENGTH; i++)
                    {
                        traps_room_4[i].previous_x = traps_room_4[i].x;
                        traps_room_4[i].x = traps_room_4[i].x + traps_room_4[i].inc_x;
                    }

                    for (int i = 0; i < TRAPS4LENGTH; i++)
                    {
                        if (i % 2 == 0)
                        {
                            if (traps_room_4[i].x == STARTIROOM4 + 1)
                            {
                                traps_room_4[i].x = FINISHIROOM4 - 2;
                            }
                        }
                        else
                        {
                            if (traps_room_4[i].x == FINISHIROOM4 - 1)
                            {
                                traps_room_4[i].x = STARTIROOM4 + 2;
                            }
                        }
                    }

                    for (int i = 0; i < TRAPS4LENGTH; i++)
                    {
                        if (i % 2 == 0)
                        {
                            print_trap(traps_room_4[i], traps_room_4[i].x, traps_room_4[i].y, 3);
                        }
                        else
                        {
                            print_trap(traps_room_4[i], traps_room_4[i].x, traps_room_4[i].y, 4);
                        }

                        if ((player_x == traps_room_4[i].x && player_y == traps_room_4[i].y) || (player_x + 1 == traps_room_4[i].x && player_y == traps_room_4[i].y))
                        {
                            if (player.shield_active == 1)
                            {
                                player.shield--;
                                print_shield(&player);
                            }
                            else if (player.shield_active == 0 || player.shield_active == -1)
                            {
                                player.hp--;
                                print_hp(player.hp);
                            }
                        }
                    }
                    for (int i = 0; i < ENEMIES4LENGTH; i++)
                    {
                        if (enemies_room_4[i].x == newX && enemies_room_4[i].y == newY && !enemies_room_4[i].is_dead)
                        {
                            if (player.shield_active == 1)
                            {
                                player.shield--;
                                print_shield(&player);
                            }
                            else if (player.shield_active == 0 || player.shield_active == -1)
                            {
                                player.hp--;
                                print_hp(player.hp);
                            }
                        }
                    }
                    if (enemies_room_4[0].is_dead && cont4_1 == 0)
                    {
                        cont4_1++;
                        enemies_cont++;
                    }
                    if (enemies_room_4[1].is_dead && cont4_2 == 0)
                    {
                        cont4_2++;
                        enemies_cont++;
                    }
                }

                if (enemies5)
                {
                    for (int i = 0; i < ENEMIES5LENGTH; i++)
                    {
                        enemies_room_5[i].x = enemies_room_5[i].previous_x + enemies_room_5[i].inc_x;
                        enemies_room_5[i].y = enemies_room_5[i].previous_y + enemies_room_5[i].inc_y;

                        if (enemies_room_5[i].inc_x == -1 && enemies_room_5[i].inc_y == 0 && enemies_room_5[i].x == 58)
                        {
                            enemies_room_5[i].inc_x = 0;
                            enemies_room_5[i].inc_y = -1;
                        }
                        else if (enemies_room_5[i].inc_x == 0 && enemies_room_5[i].inc_y == -1 && enemies_room_5[i].y == 11)
                        {
                            enemies_room_5[i].inc_x = 1;
                            enemies_room_5[i].inc_y = 0;
                        }
                        else if (enemies_room_5[i].inc_x == 1 && enemies_room_5[i].inc_y == 0 && enemies_room_5[i].x == 69)
                        {
                            enemies_room_5[i].inc_x = 0;
                            enemies_room_5[i].inc_y = 1;
                        }
                        else if (enemies_room_5[i].inc_x == 0 && enemies_room_5[i].inc_y == 1 && enemies_room_5[i].y == 15)
                        {
                            enemies_room_5[i].inc_x = -1;
                            enemies_room_5[i].inc_y = 0;
                        }
                        if (!enemies_room_5[i].is_dead)
                        {
                            print_enemy(enemies_room_5[i]);
                        }

                        if (enemies_room_5[i].x == newX && enemies_room_5[i].y == newY && !enemies_room_5[i].is_dead)
                        {
                            if (player.shield_active == 1)
                            {
                                player.shield--;
                                print_shield(&player);
                            }
                            else if (player.shield_active == 0 || player.shield_active == -1)
                            {
                                player.hp--;
                                print_hp(player.hp);
                            }
                        }

                        enemies_room_5[i].previous_x = enemies_room_5[i].x;
                        enemies_room_5[i].previous_y = enemies_room_5[i].y;
                    }
                    if (enemies_room_5[0].is_dead && cont5_1 == 0)
                    {
                        cont5_1++;
                        enemies_cont++;
                    }
                    if (enemies_room_5[1].is_dead && cont5_2 == 0)
                    {
                        cont5_2++;
                        enemies_cont++;
                    }
                    if (enemies_room_5[2].is_dead && cont5_3 == 0)
                    {
                        cont5_3++;
                        enemies_cont++;
                    }
                    if (enemies_room_5[3].is_dead && cont5_4 == 0)
                    {
                        cont5_4++;
                        enemies_cont++;
                    }
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

                if ((newX == 30 || newX == 31) && newY == 29)
                {
                    player.shield = 3;
                }

                if (player.shield)
                {
                    print_shield(&player);

                    if (player.shield_active)
                    {
                        screenSetColor(GREEN, DARKGRAY);
                    }
                    else
                    {
                        screenSetColor(WHITE, DARKGRAY);
                    }

                    screenGotoxy(MINX + 42, MINY + 2);
                    printf("┏━━━┓");
                    screenGotoxy(MINX + 42, MINY + 3);
                    printf("┃🛡️  ┃");
                    screenGotoxy(MINX + 42, MINY + 4);
                    printf("┗━━━┛");
                }
                
                else
                {
                    screenGotoxy(MINX + 42, MINY + 2);
                    printf("      ");
                    screenGotoxy(MINX + 42, MINY + 3);
                    printf("      ");
                    screenGotoxy(MINX + 42, MINY + 4);
                    printf("      ");
                }

                // Updating screen
                print_key(ch);
                screenUpdate();
            }
        }

        keyboardDestroy();
        screenDestroy();
        timerDestroy();

        char *token;
        FILE *file;
        file = fopen("src/files/score.txt", "r+");

        if (file == NULL)
        {
            perror("File not found");
            return 1;
        }

        char readLine[128], name[6], points[10];

        while (fgets(readLine, sizeof(readLine), file) != NULL)
        {
            token = strtok(readLine, " ");
            strncpy(name, token, 5);
            name[5] = '\0';

            token = strtok(NULL, " ");
            strncpy(points, token, 9);
            points[9] = '\0';

            int int_points = atoi(points);
            add_score(&list, int_points, name);
        }

        // contando pontos
        int itens = 0;
        if (player.sword)
        {
            itens += 1;
        }
        if (player.shield)
        {
            itens += 1;
        }

        char nome[6];
        printf("Digite seu nome [5]: ");
        scanf(" %5s", nome);

        int int_points = sum_score(enemies_cont, player.steps, player.hp, itens);
        sprintf(points, "%d", int_points);
        fprintf(file, "%s ", nome);
        fprintf(file, "%s\n", points);

        add_score(&list, int_points, nome);

        fclose(file);

        screenInit(0);
        keyboardInit();

        screenSetColor(MAGENTA, DARKGRAY);
        screenGotoxy(60, 3);
        ascii_print("src/files/topscores.txt");

        screenGotoxy(56, 22);
        printf(">");
        screenGotoxy(80, 22);
        printf("<");

        screenSetColor(LIGHTGRAY, DARKGRAY);

        screenGotoxy(58, 22);
        printf("PRESS [ENTER] TO EXIT");
        print_score(list);
        free_score(list);

        ch = 0;
        while (ch != 10)
        {
            if (keyhit())
            {
                ch = readch();
            }
        }

        printf("\n");
        keyboardDestroy();
        screenDestroy();
        printf("\t😼 🙀 😾\n");
        printf("  Thank you for playing\n\n");
        return 0;
    }

    return 0;
}