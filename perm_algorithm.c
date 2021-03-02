#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    size_t vertices;
    int **weight_mat;
    int **used;
} graph_t;

enum error
{
    ok,
    error
};

int **create_mat(size_t row, size_t col)
{
    int **temp = malloc(row * sizeof(int *) + col * sizeof(int));
    if (temp)
    {
        for (size_t i = 0; i < row; i++)
            temp[i] = (int *)((char *)temp + row * sizeof(int) + i * col * sizeof(int));
    }
    return temp;
}

graph_t *create_graph(size_t n)
{
    graph_t *temp = calloc(1, sizeof(graph_t));
    if (temp)
    {
        temp->weight_mat = create_mat(n, n);
        temp->used = create_mat(n, n);
        if (temp->weight_mat == NULL || temp->used == NULL)
        {
            free(temp->weight_mat);
            free(temp->used);
            free(temp);
            temp = NULL;
        }
    }
    return temp;
}

void assign_mat_with_value(graph_t *graph, int value)
{
    for (size_t i = 0; i < graph->vertices; i++)
    {
        for (size_t j = 0; j < graph->vertices; j++)
            graph->weight_mat[i][j] = value;
    }
}

void input_graph_weight(graph_t *graph)
{
    assign_inf_graph_weight(graph, __INT_MAX__);
    int m, n, weight;
    while (fscanf(stdin, "%d %d %d", &m, &n, &weight) == 3 && m > 0 && n > 0 && weight > 0)
    {
        graph->weight_mat[m - 1][n - 1] = weight;
    }
}

int main()
{
    int n, rc = ok;
    puts("Enter The size of vertices:");
    if (fscanf(stdin, "%d", &n) == 1 && n > 0)
    {
        graph_t *graph = create_graph(n);
        if (graph)
        {
            input_graph_weight(graph);

        }
        else
        {
            puts("m-alloc error!");
            rc = error;
        }
    }
    else
    {
        puts("Incorect Input: try again!");
        rc = error;
    }
}