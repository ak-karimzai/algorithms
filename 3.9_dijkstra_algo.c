#include <stdio.h>
#include <stdlib.h>

/*
* credit to Abdul Bary Youtube Channel https://www.youtube.com/channel/UCZCFT11CWBi3MHNlGf019nw
* This algorithm not working in negative path in a weighted graph!
* Greedy method Finding the minimum cost of a problem
*/

#define INF 1000000

typedef struct 
{
    int dim;
    int **mat;
    int *path_arr;
} adj_matrix;

enum error_code
{
    ok,
    error
};

int matrix_const[6][6] = {{0, 2, 4, 0, 0, 0},
                          {0, 0, 1, 7, 0, 0},
                          {0, 0, 0, 0, 3, 0},
                          {0, 0, 0, 0, 0, 1},
                          {0, 0, 0, 2, 0, 5},
                          {0, 0, 0, 0, 0, 0}};

adj_matrix *create_matrix(int dim)
{
    adj_matrix *temp = malloc(sizeof(adj_matrix));
    if (temp)
    {
        temp->dim = dim;
        temp->mat = malloc(sizeof(int *) * dim + dim * dim * sizeof(int));
        if (temp->mat)
        {
            temp->path_arr = malloc(sizeof(int) * dim);
            if (temp->path_arr)
            {
                for (int i = 0; i < temp->dim; i++)
                {
                    temp->mat[i] = (int *)((char *) temp->mat + dim * sizeof(int *) + dim * i * sizeof(int));
                    temp->path_arr[i] = INF;
                }
            }
            else
            {
                free(temp->mat);
                free(temp);
                temp = NULL;
            }
        }
        else
        {
            free(temp);
            temp = NULL;
        }
    }
    return temp;
}

void free_matrix(adj_matrix *matrix)
{
    free(matrix->path_arr);
    free(matrix->mat);
    free(matrix);
}

int read_matrix(adj_matrix *matrix)
{
    int rc = ok;
    for (int i = 0; i < matrix->dim && rc == ok; i++)
    {
        printf("vertice [%d]: \n", i + 1);
        for (int j = 0; j < matrix->dim; j++)
        {
            if (fscanf(stdin, "%d", &matrix->mat[i][j]) != 1)
            {
                rc = error;
                break;
            }
            else if (matrix->mat[i][j] == 0)
                matrix->mat[i][j] = INF;
        }
    }
    return rc;
}

int find_minimum_and_not_visited(adj_matrix *matrix, char *visited_arr)
{
    int min = INF, index = -10;
    for (int i = 0; i < matrix->dim; i++)
    {
        if (matrix->path_arr[i] < min && visited_arr[i] == 0)
        {
            min = matrix->path_arr[i];
            index = i;
        }
    }
    return index;
}

void print_shortet_path(adj_matrix *matrix)
{
    printf("\n\n");
    for (int i = 0; i < matrix->dim; i++)
        printf("%d ", matrix->path_arr[i]);
}

void find_shortest_path(adj_matrix *matrix, int start_vertic)
{
    start_vertic--;
    char *visited = calloc(matrix->dim, 1);
    visited[start_vertic] = 1;
    matrix->path_arr[start_vertic] = 0;
    for (int i = 0; i < matrix->dim; i++)
        if (matrix->mat[start_vertic][i] + matrix->path_arr[start_vertic] < matrix->path_arr[i])
            matrix->path_arr[i] = matrix->mat[start_vertic][i];
    int index = find_minimum_and_not_visited(matrix, visited);
    while (index >= 0)
    {
        visited[index] = 1;
        for (int i = 0; i < matrix->dim; i++)
        {
            if (matrix->path_arr[index] + matrix->mat[index][i] < matrix->path_arr[i])
                matrix->path_arr[i] = matrix->path_arr[index] + matrix->mat[index][i];
        }
        index = find_minimum_and_not_visited(matrix, visited);
    }
    free(visited);
}

int main()
{
    int dim, rc = ok;
    if (fscanf(stdin, "%d", &dim) == 1)
    {
        adj_matrix *matrix = create_matrix(dim);
        if (matrix)
        {
            if (read_matrix(matrix) == ok)
            {
                puts("Enter the vertice number in which you want to find path");
                if (fscanf(stdin, "%d", &dim) == 1 && dim > 0)
                {
                    find_shortest_path(matrix, dim);
                    print_shortet_path(matrix);
                }
            }
            free_matrix(matrix);
        }
        else
        {
            rc = error;
        }
    }
    return rc;
}