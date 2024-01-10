make -C /Users/lsoto-do/core04/Cub3d/ &&  cc ./main.c ./unity.c  && ./a.out

#With leaks

#cc ./main.c ./unity.c ../*.c ../../aux/*.c  ../../../libft/libft.a  -I../../../includes -I./ -I../ && leaks -at -- ./a.out