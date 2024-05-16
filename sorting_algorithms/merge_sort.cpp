#include <iostream>

class MergeSort
{
private:
    static void merge(int* A, int p, int q, int r);

public:
    static void sort(int* A, int p, int r);
};

void MergeSort::sort(int *A, int p, int r)
{
    if (p >= r) return;
    int q = (p + r) / 2;
    sort(A, p, q);
    sort(A, q + 1, r);
    merge(A, p, q, r);
}

void MergeSort::merge(int *A, int p, int q, int r)
{
    int n_l = q - p + 1;
    int n_r = r - q;
    int* L = new int[n_l];
    int* R = new int[n_r];
    for (int i = 0; i < n_l; i++)
    {
        L[i] = A[p + i]; 
    }
    for (int j = 0; j < n_r; j++)
    {
        R[j] = A[q + j + 1];
    }
    int i = 0;
    int j = 0;
    int k = p;
    while (i < n_l && j < n_r)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j]; 
            j++;
        }
        k++;
    }
    while (i < n_l)
    {
        A[k] = L[i];
        i++;
        k++;
    }
    while (j < n_r)
    {
        A[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

int main(int argc, char const *argv[])
{
    int n = 8;
    int* A = new int[n]{12, 3, 7, 9, 14, 6, 11, 2};
    MergeSort::sort(A, 0, n - 1);
    std::cout << "[";
    for (int i = 0; i < n; i++)
    {
        std::cout << " " << A[i] << " ";
    }
    std::cout << "]";
    delete[] A;
    return 0;
}
