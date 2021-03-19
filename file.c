#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "role.h"
#include "stack.h"

LinkedList* readHero( char *fileName )
{
    FILE *readPtr = NULL;
    LinkedList *heroes = NULL;
    Hero *hero = NULL;
    char inName[51] = "";
    int inHp, inAtk, inDef, inMed;

    readPtr = fopen(fileName, "r");

    if( readPtr == NULL )
        perror("Error while reading file");
    else
    {
        heroes = createLinkedList();
        inHp = inAtk = inDef = inMed = 0;
        while( fscanf(readPtr, "%d,%d,%d,%d,%[^\n]\n", 
                      &inHp, &inAtk, &inDef, &inMed, inName) != EOF )
        {
            hero = (Hero*)malloc(sizeof(Hero));

            hero->hp = inHp;
            hero->atk = inAtk;
            hero->def = inDef;
            hero->med = inMed;
            strcpy(hero->name, inName);

            insertLast(heroes, hero);
        }
        fclose(readPtr);
        readPtr = NULL;
    }
    return heroes;
}

LinkedList* readEnemy( char *fileName )
{
    FILE *readPtr = NULL;
    LinkedList *enemies = NULL;
    Enemy *enemy = NULL;
    char inName[51] = "";
    int inHp, inAtk, inDef;

    readPtr = fopen(fileName, "r");

    if( readPtr == NULL )
        perror("Error while reading file");
    else
    {
        enemies = createLinkedList();
        inHp = inAtk = inDef = 0;
        while( fscanf(readPtr, "%d,%d,%d,%[^\n]\n", 
                      &inHp, &inAtk, &inDef, inName) != EOF )
        {
            enemy = (Enemy*)malloc(sizeof(Enemy));

            enemy->hp = inHp;
            enemy->atk = inAtk;
            enemy->def = inDef;
            strcpy(enemy->name, inName);

            push(enemies, enemy);
        }
        fclose(readPtr);
        readPtr = NULL;
    }
    return enemies;
}
