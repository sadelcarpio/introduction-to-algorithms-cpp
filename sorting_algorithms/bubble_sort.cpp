#include <iostream>

class BubbleSort {
public:
    static void sort(int* A, int n);
};

void BubbleSort::sort(int* A, int n) {
    for (int i = 0; i < n; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (A[j] < A[j - 1])
            {
                int temp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = temp;
            }   
        }   
    }
}


int main(int argc, char const *argv[])
{
    int n = 6;
    int* A = new int[n]{5, 2, 4, 6, 1, 3};
    BubbleSort::sort(A, n);
    std::cout << "[";
    for (int i = 0; i < n; i++)
    {
        std::cout << " " << A[i] << " ";
    }
    std::cout << "]";
    delete[] A;
    return 0;
}
