#include <iostream>

class SelectionSort
{
public:
    static void sort(int* A, int n);
};

void SelectionSort::sort(int* A, int n)
{
    int min, index;
    for (int i = 0; i < n; i++)
    {
        min = A[i];
        index = i;
        for (int j = i; j < n; j++)
        {
            if (A[j] < min)
            {
                min = A[j];
                index = j;
            }
        }
        A[index] = A[i];
        A[i] = min;
    }
}

int main(int argc, char const *argv[])
{
    int n = 6;
    int *A = new int[n]{5, 2, 4, 6, 1, 3};
    SelectionSort::sort(A, n);
    std::cout << "[";
    for (int i = 0; i < n; i++)
    {
        std::cout << " " << A[i] << " ";
    }
    std::cout << "]";
    delete[] A;
    return 0;
}
