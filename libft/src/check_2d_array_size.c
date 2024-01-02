int check_2d_array_size(char *array[])
{
    int i;

    i = 0;
    while (array[i])
        i++;
    return (i);
}