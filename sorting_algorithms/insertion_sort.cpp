#include <iostream>

class InsertionSort
{
public:
    static void sort(int *A, int n);
};

void InsertionSort::sort(int *A, int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

int main(int argc, char const *argv[])
{
    int n = 6;
    int *A = new int[n]{5, 2, 4, 6, 1, 3};
    InsertionSort::sort(A, n);
    std::cout << "[";
    for (int i = 0; i < n; i++)
    {
        std::cout << " " << A[i] << " ";
    }
    std::cout << "]";
    delete[] A;
    return 0;
}
