#include <iostream>
#include <vector>
#include <algorithm>
#include <ostream>
using namespace std;

#define MaxValue 32676

using Matrix = vector<vector<int>>;

const Matrix exmp = {{0, 3, MaxValue, 7},
                     {8, 0, 2, MaxValue},
                     {5, MaxValue, 0, 1},
                     {2, MaxValue, MaxValue, 0}};

Matrix find_next_matrix(int prev_mat_ind, const Matrix &prev_mat)
{
    size_t n = prev_mat.size();
    Matrix temp(n, vector<int>(n));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            temp[i][j] = min(prev_mat[i][j], prev_mat[i][prev_mat_ind] + 
                                             prev_mat[prev_mat_ind][j]);
        }
    }
    return temp;
}

auto find_all_pairs(const Matrix &start_mat)
{
    vector<Matrix> matrices(exmp.size() + 1);
    matrices[0] = start_mat;
    for (size_t i = 0, k; i < matrices[0].size(); i++)
    {
        k = i + 1;
        matrices[k] = find_next_matrix(i, matrices[i]);
    }
    return matrices;
}

template <typename T>
ostream& operator<<(ostream& out, const vector<T> &vec)
{
    bool flag = false;
    out << "{ ";
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (flag)
            out << ", ";
        flag = true;
        out << vec[i];
    }
    out << " }\n";
    return out;
}

int main()
{
    auto matrices = find_all_pairs(exmp);
    cout << matrices << endl;
    return 0;
}