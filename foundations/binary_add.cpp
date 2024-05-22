#include <iostream>

int* add_binary_integers(int* a, int* b, int n);

int main(int argc, char const *argv[])
{
    int n;
    std::cin >> n;
    int* a = new int[n];
    int* b = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        std::cin >> b[i];
    }
    int* c = add_binary_integers(a, b, n);
    
    std::cout << "[";
    for (int i = 0; i < n + 1; i++)
    {
        std::cout << " " << c[i] << " ";
    }
    std::cout << "]";
    delete[] c;
    delete[] a;
    delete[] b;
    return 0;
}

int* add_binary_integers(int* a, int* b, int n) {
    int* c = new int[n + 1];
    int carry = 0;
    int sum;
    for (int i = n - 1; i >= 0; i--)
    {
        sum = (a[i] + b[i] + carry);
        c[i + 1] = sum % 2;
        c[i] = carry;
        carry = sum / 2;
    }
    return c;
}
