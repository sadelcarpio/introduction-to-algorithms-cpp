#include <iostream>

class MergeSort
{
private:
    static int merge(int* A, int p, int q, int r);

public:
    static int count_inversions(int* A, int p, int r);
};

int MergeSort::count_inversions(int *A, int p, int r)
{
    int num_inversions = 0;
    if (p >= r) return num_inversions;
    int q = (p + r) / 2;
    num_inversions += count_inversions(A, p, q);
    num_inversions += count_inversions(A, q + 1, r);
    num_inversions += merge(A, p, q, r);
    return num_inversions;
}

int MergeSort::merge(int *A, int p, int q, int r)
{
    int num_inversions = 0;
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
            num_inversions += (n_l - i);
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
    return num_inversions;
}

int main(int argc, char const *argv[])
{
    int n = 6;
    int *A = new int[n]{6, 5, 9, 0, 1, 7};
    int num_inversions = MergeSort::count_inversions(A, 0, n - 1);
    std::cout << num_inversions;
    delete[] A;
    return 0;
}
