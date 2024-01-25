#!/bin/bash

if [ "$1" == "bonus" ]; then
    make -C /home/luised94/Cub3d/ bonus && cc ./main.c ./unity.c -D BONUS=1 && ./a.out
else
    make -C /home/luised94/Cub3d/ && cc ./main.c ./unity.c && ./a.out
fi