int check_2d_array_size(char *array[])
{
    int i;

    while (array[i])
        i++;
    return (i);
}