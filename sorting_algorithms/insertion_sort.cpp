#include <iostream>

class InsertionSort
{
private:
    static int binary_insert(int *A, int key, int p, int r);

public:
    static void sort(int *A, int n);
    static void recursive_sort(int *A, int n);
    static void sort_with_binary_search(int *A, int n);
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

void InsertionSort::recursive_sort(int *A, int n)
{
    if (n == 1) return;
    recursive_sort(A, n - 1);
    int key = A[n - 1];
    int i = n - 2;
    while (i >= 0 && key < A[i])
    {
        A[i + 1] = A[i];
        A[i] = key;
        i--;
    }
}

void InsertionSort::sort_with_binary_search(int *A, int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = A[i];
        int index = binary_insert(A, key, 0, i);
        int j = i - 1;
        while (j >= index)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

int InsertionSort::binary_insert(int *A, int key, int p, int r)
{
    int q = (p + r) / 2;
    if (p >= r) return p;
    if (key == A[q]) return q;
    if (key < A[q]) return binary_insert(A, key, p, q);
    return binary_insert(A, key, q + 1, r);
}

int main(int argc, char const *argv[])
{
    int n = 6;
    int *A = new int[n]{5, 2, 4, 6, 1, 3};
    InsertionSort::sort_with_binary_search(A, n);
    std::cout << "[";
    for (int i = 0; i < n; i++)
    {
        std::cout << " " << A[i] << " ";
    }
    std::cout << "]";
    delete[] A;
    return 0;
}
