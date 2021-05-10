#include <iostream>
#include <vector>
#include <algorithm>
#include <ostream>
using namespace std;

#define MaxValue 32767

using Matrix = vector<vector<int>>;

const Matrix const_mat = {
                 {0, 6, 5, 5, 0, 0, 0},
                 {0, 0, 0, 0, -1, 0, 0},
                 {0, -2, 0, 0, 1, 0, 0},
                 {0, 0, -2, 0, 0, -1, 0},
                 {0, 0, 0, 0, 0, 0, 3},
                 {0, 0, 0, 0, 0, 0, 3},
                 {0, 0, 0, 0, 0, 0, 0},
                };

void find_destination(const Matrix &adj_mat, vector<int> &dest)
{
    int temp;
    for (size_t i = 0; i < adj_mat.size(); i++)
    {
        for (size_t j = 0; j < adj_mat.size(); j++)
        {
            if (adj_mat[i][j] != 0)
            {
                temp = dest[i] + adj_mat[i][j];
                if (temp < dest[j])
                    dest[j] = temp;
            }
        }
    }
}

vector<int> find_path(const Matrix &adj_mat)
{
    auto n = adj_mat.size();
    vector<int> destination(n, MaxValue);
    destination[0] = adj_mat[0][0];
    for (size_t i = 0; i + 1 < n; i++)
        find_destination(adj_mat, destination);
    return destination;
}

template<typename type>
ostream& operator<<(ostream &out, const vector<type> &vec)
{
    bool flag = false;
    cout << "{ ";
    for (auto &elem : vec)
    {
        if (flag)
            out << ", ";
        flag = true;
        out << elem;
    }
    out << " }";
    return out;
}

int main()
{
    cout << find_path(const_mat) << endl;
    return 0;
}