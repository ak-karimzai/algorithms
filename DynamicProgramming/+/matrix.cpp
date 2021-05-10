#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

using Matrix = vector<vector<int>>;

Matrix create_matrix(size_t dimen)
{
    Matrix temp(dimen, vector<int>(dimen));

    for (int i = 0; i < dimen; i++)
    {
        for (int j = 0; j < dimen; j++)
            temp[i][j] = abs(i - j);
    }
    return temp;
}

void display_mat(const Matrix &mat)
{
    for (size_t i = 0; i < mat.size(); i++)
    {
        for (size_t j = 0; j < mat[i].size(); j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    auto dim = create_matrix(5);
    display_mat(dim);
    return 0;
}