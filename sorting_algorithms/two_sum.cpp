#include <iostream>
#include <vector>
#include <algorithm>

class TwoSum
{
public:
    static bool search(std::vector<int> A, int n, int x);
};

bool TwoSum::search(std::vector<int> A, int n, int x)
{
    std::sort(A.begin(), A.end());
    for (int i = 0; i < n; i++)
    {
        if (std::binary_search(A.begin(), A.end(), x - A[i])) return true;
    }
    return false;
}

int main(int argc, char const *argv[])
{
    int n = 6, x = 10;
    std::vector<int> A{6, 5, 9, 0, 1, 3};
    std::cout << TwoSum::search(A, n, x);
    return 0;
}
