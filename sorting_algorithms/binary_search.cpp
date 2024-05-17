#include <iostream>
#include <algorithm>
#include <vector>

int binary_search(std::vector<int> &a, int val, int p, int r) {
    if (p >= r) return -1;
    int q = (p + r) / 2;
    if (val == a[q]) return q;
    if (val < a[q]) {
        return binary_search(a, val, p, q);
    }
    return binary_search(a, val, q + 1, r);
    
}

int main(int argc, char const *argv[])
{
    int n = 6;
    std::vector<int> arr{6, 5, 7, 3, 2, 1};
    std::sort(arr.begin(), arr.end());
    std::cout << "[";
    for (int elem: arr)
    {
        std::cout << " " << elem << " ";
    }
    std::cout << "]\n";
    int index = binary_search(arr, 4, 0, 6);
    std::cout << index;
    return 0;
}
