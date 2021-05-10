#include <iostream>
using namespace std;

int iterative_fib(int n)
{
    int arr[n + 1] = {0, 1};
    for (int i = 2; i <= n; i++)
        arr[i] = arr[i - 2] + arr[i - 1];
    return arr[n];
}

int main()
{
    for (int i = 0; i <= 10; i++)
        cout << iterative_fib(i) << " ";
    cout << endl;
    return 0;
}