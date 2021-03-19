#include <stdio.h>
#include <stdlib.h>
#include "newSleep.h"
#include "LinkedList.h"
#include "file.h"
#include "role.h"
#include "display.h"

int main(int argc, char *argv[])
{
    LinkedList *heroes = NULL, *enemies = NULL;
    LinkedListNode *heroNd = NULL;
    Hero *hero = NULL;
    int win = 0;
    float sec = 0.0;

    if( argc != 4 )
        printf("Usage: ./rpg hero.txt enemies.txt <sleep time in real number>\n");
    else
    {
        heroes = readHero(argv[1]);
        enemies = readEnemy(argv[2]);
        if( heroes != NULL && enemies != NULL )
        {
            system("clear");
            printf("Welcome to auto RPG!\n");

            sec = atof(argv[3]);
            newSleep(sec);
            system("clear");

            if( heroes != NULL && enemies != NULL )
            {
                displayIntro( heroes, enemies );
                newSleep(sec);
                system("clear");
                win = displayAttack(heroes, enemies, sec);

                heroNd = heroes->head;
                hero = (Hero *)heroNd->data;
                if( win == 1 )
                {
                    printf("%s defeats all enemies! The world is saved\n", hero->name);
                }
                else
                    printf("%s loses the battle! The world is doomed\n", hero->name);
                freeLinkedList(heroes);
                freeLinkedList(enemies);
            }
        }
    }
    return 0;
}
