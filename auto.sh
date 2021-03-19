#!/bin/bash

file=rpg
herofile=hero.txt
enemyfile=enemies.txt
delay=5.0

if ! [ -e $file ]; then
    make
fi

./$file $herofile $enemyfile $delay
