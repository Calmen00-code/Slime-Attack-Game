#ifndef DISPLAY
#define DISPLAY

#define FALSE 0
#define TRUE !FALSE

#include "LinkedList.h"
#include "role.h"

void displayIntro( LinkedList *, LinkedList * );
void displayHeroAttribute( LinkedList * );
int displayAttack( LinkedList *, LinkedList *, float );
int getCritical( int );
int getDamage( int, int );
int itemDrop();
int criticalHp( Hero*, int );

#endif
