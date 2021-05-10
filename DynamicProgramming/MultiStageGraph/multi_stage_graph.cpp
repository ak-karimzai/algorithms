#include <iostream>
#include <vector>
#include <fmt/format.h>
#include <string>
using namespace std;
#define MinValue 32767

const int const_mat[][8] = { { 0, 2, 1, 3, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 2, 3, 0, 0 },
                             { 0, 0, 0, 0, 6, 7, 0, 0 },
                             { 0, 0, 0, 0, 6, 8, 9, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 6 },
                             { 0, 0, 0, 0, 0, 0, 0, 4 },
                             { 0, 0, 0, 0, 0, 0, 0, 5 } };

struct Vertex_info
{
    int cost;
    int direct;
    int path;
};

void find_path(const vector<vector<int>> &adj_mat, vector<int> &res, int stages)
{
    size_t n = adj_mat.size() > 0 ? adj_mat.size() - 1 : 0;
    vector<Vertex_info> info(n + 1);

    if (stages > n)
    {
        throw runtime_error("stage != adjacency matrix size");
    }
    int min;
    info[n].cost = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        min = MinValue;
        for (int k = i + 1; k <= n; k++)
        {
            if (adj_mat[i][k] != 0 && adj_mat[i][k] + info[k].cost < min)
            {
                min = adj_mat[i][k] + info[k].cost;
                info[i].direct = k + 1;
            }
        }
        info[i].cost = min;
    }
    info[1].path = 1;
    info[stages].path = n + 1;
    for (int i = 2; i < stages; i++)
        info[i].path = info[info[i - 2].path].direct;
    for (int i = 1; i <= stages; i++)
        res[i - 1] = info[i].path;
    res.resize(stages);
}

int main()
{
    vector<vector<int>> adj_mat(8, vector<int>(8));
    for (size_t i = 0; i < 8; i++)
        for (size_t j = 0; j < 8; j++)
            adj_mat[i][j] = const_mat[i][j];
    vector<int> res(8, 0);
    find_path(adj_mat, res, 4);
    for (auto x : res)
        cout << x << " ";
    cout << endl;
    return 0;
}