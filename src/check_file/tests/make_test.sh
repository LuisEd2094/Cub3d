#cc ./main.c ./unity.c ../*.c ../../aux/*.c  ../../../libft/libft.a  -I../../../includes -I./ -I../ && ./a.out

#With leaks

cc ./main.c ./unity.c ../*.c ../../aux/*.c  ../../../libft/libft.a  -I../../../includes -I./ -I../ && leaks -at -- ./a.out