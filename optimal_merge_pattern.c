#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 

typedef struct
{
    int *arr;
    int size;
    bool merged;
} array;

int first_arr[] = {1, 2, 4, 5, 6, 7};
int sec_arr[] = {1, 2, 4, 5, 6};
int trd_arr[] = {1, 2, 4, 5};
int frt_arr[] = {1, 2, 4};

int main()
{
    array first = {first_arr, 6, false};
    array second = {sec_arr, 5, false};
    array third = {trd_arr, 4, false};
    array fourth = {frt_arr, 3, false};
    return 0;
}