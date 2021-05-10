#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Obj_det
{
    int profit;
    int weight;
    Obj_det(int p = 0, int w = 0)
    {
        profit = p;
        weight = w;
    }
};

void display_info(const vector<vector<int>> &info, const vector<Obj_det> &details)
{
    size_t i = info.size() - 1, j = info[0].size() - 1;
    while (i > 0 && j > 0)
    {
        if (info[i][j] == info[i - 1][j])
        {
            cout << i << " = 0" << endl;
            i--;
        }
        else
        {
            cout << i << " = 1" << endl;
            i--;
            j -= details[i].weight;
        }
    }
}

void find_solution(const vector<Obj_det> &details, int bag_capacity)
{
    size_t n = details.size();
    if (n == 0 || bag_capacity == 0) {
        cout << "Incorect Arguments!" << endl;
        return;
    }
    vector<vector<int>> info(n, vector<int>(bag_capacity + 1));

    for (size_t i = 0; i < n; i++)
    {
        for (size_t w = 0; w <= bag_capacity; w++)
        {
            if (i == 0 || w == 0)
                info[i][w] = 0;
            else if (details[i].weight <= w)
                info[i][w] = max(details[i].profit + info[i - 1][w - details[i].weight],\
                                info[i - 1][w]);
            else
                info[i][w] = info[i - 1][w];
        }
    }
    display_info(info, details);
}

int main()
{
    vector<Obj_det> details = {{0, 0}, {1, 2}, {2, 3}, {5, 4}, {6, 5}};
    find_solution(details, 8);
}