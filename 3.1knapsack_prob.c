#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    double profit;
    double weight;
    double profits_by_weight;
    double included_part;
} obj;

typedef struct
{
    int numb_of_obs;
    double capacity;
    obj *arr;
} products;

enum error
{
    ok,
    error
};

void input_data(products *prod)
{
    puts("Enter The profit and weight of every object pallely!");
    for (int i = 0; i < prod->numb_of_obs; i++)
    {
        printf("obj no: [%d]\n", i);
        if (fscanf(stdin, "%lf %lf", &prod->arr[i].profit, &prod->arr[i].weight) != 2)
        {
            i--;
            puts("Incorect Input: Try again!");
        }
    }
}

void claculate_prof(products *prod)
{
    for (int i = 0; i < prod->numb_of_obs; i++)
        prod->arr[i].profits_by_weight = prod->arr[i].profit / prod->arr[i].weight;
}

double find_max(products *prod, int *index)
{
    double max = 0.0;
    *index = -1;
    for (int i = 0; i < prod->numb_of_obs; i++)
        if (prod->arr[i].profits_by_weight > max && prod->arr[i].included_part == 0.0)
        {
            max = prod->arr[i].profits_by_weight;
            *index = i;
        }
    return max;
}

void calculate_included_part(products *prod)
{
    double max = 0.0;
    int index;
    for (int i = 0; i < prod->numb_of_obs; i++)
    {
        max = find_max(prod, &index);
        if (index >= 0)
        {
            if (prod->arr[index].weight <= prod->capacity)
            {
                prod->capacity -= prod->arr[index].weight;
                prod->arr[index].included_part = 1.0;
            }
            else if (prod->capacity)
            {
                prod->arr[index].included_part = prod->capacity / prod->arr[index].weight;
                prod->capacity = 0;
            }
        }
    }
}

void print_profit_and_weight(products *prod)
{
    double weight, prof;
    weight = prof = 0.0;
    for (int i = 0; i < prod->numb_of_obs; i++)
    {
        printf("%0.2lf ", prod->arr[i].included_part);
        weight += prod->arr[i].included_part * prod->arr[i].weight;
        prof += prod->arr[i].included_part * prod->arr[i].profit;
    }
    printf("\nWeight%.2lf\tprofit: %.2lf\n", weight, prof);
}

int main()
{
    int n, rc;
    double capacity;
    puts("Enter The number of objs");
    if (fscanf(stdin, "%d %lf", &n, &capacity) == 2 && n > 0 && capacity > 0)
    {
        products *prod = malloc(sizeof(products));
        if (prod)
        {
            prod->numb_of_obs = n;
            prod->capacity = capacity;
            prod->arr = calloc(n, sizeof(obj));
            if (prod->arr)
            {
                input_data(prod);
                claculate_prof(prod);
                calculate_included_part(prod);
                print_profit_and_weight(prod);
                free(prod->arr);
            }
            else
            {
                puts("m-alloc Error");
                rc = error;
            }
            free(prod);
        }
        else
        {
            puts("m-alloc Error");
            rc = error;
        }
    }
    else
    {
        puts("incorrect Input");
        rc = error;
    }
    return rc;
}