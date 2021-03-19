#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "role.h"
#include "newSleep.h"
#include "stack.h"

void displayIntro( LinkedList *heroes, LinkedList *enemies )
{
    LinkedListNode *displayNd = NULL;
    Hero *hero = NULL;
    Enemy *enemy = NULL;

    printf("Hero: \n");
    displayNd = heroes->head;
    while( displayNd != NULL )
    {
        hero = (Hero *)displayNd->data;
        printf("%s\t\tHP:%d\tATK:%d\tDEF:%d\tMED:%d\n", hero->name, hero->hp, 
                hero->atk, hero->def, hero->med );
        displayNd = displayNd->next;
    }

    printf("\nEnemy: \n");
    displayNd = enemies->head;
    while( displayNd != NULL )
    {
        enemy = (Enemy *)displayNd->data;
        printf("%s\t\tHP:%d\tATK:%d\tDEF:%d\n", enemy->name, enemy->hp, 
                                                enemy->atk, enemy->def);
        displayNd = displayNd->next;
    }
}

void displayHeroAttribute( LinkedList *heroes )
{
    LinkedListNode *heroNd = NULL;
    Hero *hero = NULL;

    heroNd = heroes->head;
    hero = (Hero *)heroNd->data;
    printf("%s\nHP:%d\nATK:%d\nDEF:%d\nMED:%d\n\n", hero->name, hero->hp, 
            hero->atk, hero->def, hero->med);
}

void displayEnemyAttribute( LinkedList *enemies )
{
    LinkedListNode *enemyNd = NULL;
    Enemy *enemy = NULL;

    enemyNd = enemies->head;
    enemy = (Enemy *)enemyNd->data;
    printf("\t%s\n\tHP:%d\n\tATK:%d\n\tDEF:%d\n\n", enemy->name, enemy->hp, 
            enemy->atk, enemy->def);
}

int displayAttack( LinkedList *heroes, LinkedList *enemies, float sleep )
{
    LinkedListNode *heroNd = NULL, *enemyNd = NULL;
    Hero *hero = NULL;
    Enemy *enemy = NULL, *defEnemy = NULL;
    int stop = FALSE;
    int heroTurn = TRUE;
    int heroAtk = 0, heroDef = 0, heroDmg = 0, initialHp = 0;
    int enemyAtk = 0, enemyDef = 0, enemyDmg = 0;
    int oldAtk = 0;
    int item = 0;
    int win = 0;

    heroNd = heroes->head;
    initialHp = ((Hero *)heroNd->data)->hp;
    enemyNd = enemies->head;

    /* ASSERTION: Stops when no more enemies left, or hero dies */
    while( !stop )
    {
        hero = (Hero *)heroNd->data;
        enemy = (Enemy *)enemyNd->data;
        heroDef = hero->def;
        enemyDef = enemy->def;

        displayHeroAttribute( heroes );
        if( heroTurn == TRUE )
        {
            if( (hero->atk * 2) < enemyDef )
            { 
                printf("%s is too weak to fight!\n", hero->name);
                stop = TRUE;
                win = 0;
            }
            else
            {
                oldAtk = hero->atk;
                heroAtk = getCritical(hero->atk);

                enemyDef = enemy->def;
                heroDmg = getDamage(heroAtk, enemyDef);

                if( heroAtk > oldAtk )
                {
                    printf("%s attacks %s, Critical Hit!! dealing %d damage!\n",
                            hero->name, enemy->name, heroDmg );
                }
                else if( heroAtk == 0 )
                    printf("%s missed the attack...\n", hero->name);
                else
                {
                    printf("%s attacks %s, dealing %d damage!\n", hero->name, 
                            enemy->name, heroDmg); 
                }

                enemy->hp = (enemy->hp - heroDmg);
            }
            heroTurn = !heroTurn;
        }
        else /* enemy turn */
        {
            if( (enemy->atk * 2) < heroDef )
            {
                if( enemies->count == 0 ) 
                {
                    printf("Enemy is too weak to fight!\n");
                    stop = TRUE;
                    win = 1;
                }
                else
                {
                    printf("%s is too weak to fight!\n", enemy->name);
                    enemy->hp = 0;
                }
            }
            else
            {
                oldAtk = enemy->atk;
                enemyAtk = getCritical(enemy->atk);

                heroDef = hero->def;
                enemyDmg = getDamage(enemyAtk, heroDef);

                if( enemyAtk > oldAtk )
                {
                    printf("\t%s attacks %s, Critical Hit!! dealing %d damage!\n",
                            enemy->name, hero->name, enemyDmg );
                }
                else if( enemyAtk == 0 )
                    printf("\t%s missed the attack...\n", enemy->name); 
                else
                {
                    printf("\t%s attacks %s, dealing %d damage!\n", enemy->name, 
                            hero->name, enemyDmg); 
                }

                hero->hp = (hero->hp - enemyDmg);

                if( (criticalHp(hero, initialHp) == TRUE) && (hero->med != 0) )
                {
                    printf("\t%s is badly injured.. eating 1 medicine, HP is restored!\n", hero->name);
                    hero->med = hero->med - 1;
                    hero->hp = initialHp;
                }
            }
            heroTurn = !heroTurn;
        }
        printf("\n");
        displayEnemyAttribute( enemies );
        printf("\n");

        if( enemy->hp <= 0 )
        {
            printf("%s is defeated!\n", enemy->name);
            defEnemy = (Enemy *)pop(enemies);
            free(defEnemy);
            defEnemy = NULL;
            enemyNd = enemies->head;
            if( enemies->count != 0 )
            {
                newSleep(sleep);
                system("clear");

                item = itemDrop();
                if( item == 1 )
                {
                    hero->atk = (hero->atk) + ((hero->atk) / 2);
                    printf("%s got better sword! ATK is now %d\n", 
                            hero->name, hero->atk);
                }
                else if( item == 2 )
                {
                    hero->def = (hero->def) + ((hero->def) / 2);
                    printf("%s got better armored! DEF is now %d\n", 
                            hero->name, hero->def);
                }
                else if( item == 3 )
                {
                    hero->med = hero->med + 1;
                    printf("%s got a new MED!\n", hero->name);
                }
            }
            else
            {
                stop = TRUE;
                win = 1;
            }
        }

        if( hero->hp <= 0 )
        {
            printf("Game over! Hero is defeated!\n");
            stop = TRUE;
        }

        newSleep(sleep);
        system("clear");
    }
    return win;
}

int getCritical( int atk )
{
    int random = 0;
    int retAtk = 0;

    srand(time(NULL));
    random = rand() % 10;

    if( random >= 0 && random <= 6 )
        retAtk = atk;
    else if ( random == 7 || random == 8 )
        retAtk = atk << 1;

    return retAtk;
}
        

int getDamage( int atk, int def )
{
    int damage = 0;
    damage = atk - def;
    return damage;
}

int itemDrop()
{
    int random = 0;
    int item = 0;

    srand(time(NULL));
    random = rand() % 10;

    if( random >= 0 && random <= 2 )
        item = 1; /* better sword */

    else if( random >= 4 && random <= 5 )
        item = 2; /* better armor */

    else
        item = 3; /* extra med */

    return item;
}

int criticalHp( Hero *hero, int initialHp )
{
    int low = FALSE;
    int criticalPoint = 0;

    criticalPoint = (int)((double)initialHp * 0.3);
    if( hero->hp <= criticalPoint )
        low = TRUE;

    return low;
}
    
