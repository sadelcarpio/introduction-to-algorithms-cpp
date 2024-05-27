#include <iostream>
#include <vector>

class MatMul
{
private:
    static void _recursive_multiply(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &, std::vector<std::vector<int>> &,
                                    int, int, int, int, int);
    static void matrix_sum(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &, std::vector<std::vector<int>> &,
                           int, int, int, int, int, int, int, bool);
    static std::vector<std::vector<int>> _strassen_multiply(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &,
                                                            int, int, int, int, int);
    static void c11(std::vector<std::vector<std::vector<int>>> &, std::vector<std::vector<int>> &, int);
    static void c12(std::vector<std::vector<std::vector<int>>> &, std::vector<std::vector<int>> &, int);
    static void c21(std::vector<std::vector<std::vector<int>>> &, std::vector<std::vector<int>> &, int);
    static void c22(std::vector<std::vector<std::vector<int>>> &, std::vector<std::vector<int>> &, int);

public:
    static std::vector<std::vector<int>> naive_multiply(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &);
    static std::vector<std::vector<int>> recursive_multiply(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &);
    static std::vector<std::vector<int>> strassen_multiply(std::vector<std::vector<int>> &, std::vector<std::vector<int>> &);
};

std::vector<std::vector<int>> MatMul::naive_multiply(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B)
{
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

std::vector<std::vector<int>> MatMul::recursive_multiply(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B)
{
    int n = A.size();
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));
    MatMul::_recursive_multiply(A, B, C, 0, 0, 0, 0, n);
    return C;
}

void MatMul::_recursive_multiply(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, std::vector<std::vector<int>> &C,
                                 int a_col, int a_row, int b_col, int b_row, int n)
{
    if (n == 1)
    {
        C[a_row][b_col] += A[a_row][a_col] * B[b_row][b_col];
        return;
    }
    int new_n = n / 2;
    MatMul::_recursive_multiply(A, B, C, a_col, a_row, b_col, b_row, new_n);
    MatMul::_recursive_multiply(A, B, C, a_col + new_n, a_row, b_col, b_row + new_n, new_n);
    MatMul::_recursive_multiply(A, B, C, a_col, a_row, b_col + new_n, b_row, new_n);
    MatMul::_recursive_multiply(A, B, C, a_col + new_n, a_row, b_col + new_n, b_row + new_n, new_n);
    MatMul::_recursive_multiply(A, B, C, a_col, a_row + new_n, b_col, b_row, new_n);
    MatMul::_recursive_multiply(A, B, C, a_col + new_n, a_row + new_n, b_col, b_row + new_n, new_n);
    MatMul::_recursive_multiply(A, B, C, a_col, a_row + new_n, b_col + new_n, b_row, new_n);
    MatMul::_recursive_multiply(A, B, C, a_col + new_n, a_row + new_n, b_col + new_n, b_row + new_n, new_n);
}

std::vector<std::vector<int>> MatMul::strassen_multiply(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B)
{
    int n = A.size();
    return MatMul::_strassen_multiply(A, B, 0, 0, 0, 0, n);
}

std::vector<std::vector<int>> MatMul::_strassen_multiply(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B,
                                                         int a_col, int a_row, int b_col, int b_row, int n)
{
    std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));
    if (n == 1)
        return {{A[a_row][a_col] * B[b_row][b_col]}};
    int new_n = n / 2;
    std::vector<std::vector<int>> S(2 * new_n, std::vector<int>(5 * new_n, 0));
    std::vector<std::vector<std::vector<int>>> P(7, std::vector<std::vector<int>>(n, std::vector<int>(n, 0)));
    MatMul::matrix_sum(B, B, S, b_col + new_n, b_row, b_col + new_n, b_row + new_n, 0, 0, new_n, true);  // b12 - b22
    MatMul::matrix_sum(A, A, S, a_col, a_row, a_col + new_n, a_row, new_n, 0, new_n, false);  // a11 + a12
    MatMul::matrix_sum(A, A, S, a_col, a_row + new_n, a_col + new_n, a_row + new_n, 2 * new_n, 0, new_n, false);  // a21 + a22
    MatMul::matrix_sum(B, B, S, b_col, b_row + new_n, b_col, b_row, 3 * new_n, 0, new_n, true);  // b21 - b11
    MatMul::matrix_sum(A, A, S, a_col, a_row, a_col + new_n, a_row + new_n, 4 * new_n, 0, new_n, false);  // a11 + a22
    MatMul::matrix_sum(B, B, S, b_col, b_row, b_col + new_n, b_row + new_n, 0, new_n, new_n, false);  // b11 + b22
    MatMul::matrix_sum(A, A, S, a_col + new_n, a_row, a_col + new_n, a_row + new_n, new_n, new_n, new_n, true);  // a12 - a22
    MatMul::matrix_sum(B, B, S, b_col, b_row + new_n, b_col + new_n, b_row + new_n, 2 * new_n, new_n, new_n, false);  // b21 + b22
    MatMul::matrix_sum(A, A, S, a_col, a_row, a_col, a_row + new_n, 3 * new_n, new_n, new_n, true);  // a11 - a21
    MatMul::matrix_sum(B, B, S, b_col, b_row, b_col + new_n, b_row, 4 * new_n, new_n, new_n, false);  // b11 + b12

    P[0] = MatMul::_strassen_multiply(A, S, a_col, a_row, 0, 0, new_n);
    P[1] = MatMul::_strassen_multiply(S, B, new_n, 0, b_col + new_n, b_row + new_n, new_n);
    P[2] = MatMul::_strassen_multiply(S, B, 2 * new_n, 0, b_col, b_row, new_n);
    P[3] = MatMul::_strassen_multiply(A, S, a_col + new_n, a_row + new_n, 3 * new_n, 0, new_n);
    P[4] = MatMul::_strassen_multiply(S, S, 4 * new_n, 0, 0, new_n, new_n);
    P[5] = MatMul::_strassen_multiply(S, S, new_n, new_n, 2 * new_n, new_n, new_n);
    P[6] = MatMul::_strassen_multiply(S, S, 3 * new_n, new_n, 4 * new_n, new_n, new_n);

    MatMul::c11(P, C, new_n);
    MatMul::c12(P, C, new_n);
    MatMul::c21(P, C, new_n);
    MatMul::c22(P, C, new_n);

    return C;
}

void MatMul::c11(std::vector<std::vector<std::vector<int>>> &P, std::vector<std::vector<int>> &C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] += P[4][i][j] + P[3][i][j] - P[1][i][j] + P[5][i][j];
        }
    }
}

void MatMul::c12(std::vector<std::vector<std::vector<int>>> &P, std::vector<std::vector<int>> &C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j + n] += P[0][i][j] + P[1][i][j];
        }
    }
}

void MatMul::c21(std::vector<std::vector<std::vector<int>>> &P, std::vector<std::vector<int>> &C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i + n][j] += P[2][i][j] + P[3][i][j];
        }
    }
}

void MatMul::c22(std::vector<std::vector<std::vector<int>>> &P, std::vector<std::vector<int>> &C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i + n][j + n] += P[4][i][j] + P[0][i][j] - P[2][i][j] - P[6][i][j];
        }
    }
}

void MatMul::matrix_sum(std::vector<std::vector<int>> &A, std::vector<std::vector<int>> &B, std::vector<std::vector<int>> &S,
                        int a_col, int a_row, int b_col, int b_row, int s_col, int s_row, int n, bool neg)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            S[s_row + i][s_col + j] = A[i + a_row][j + a_col] + (neg ? -B[i + b_row][j + b_col] : B[i + b_row][j + b_col]);
        }
    }
}

int main(int argc, char const *argv[])
{
    std::vector<std::vector<int>> A = {{1, 1}, {1, 1}};
    std::vector<std::vector<int>> B = {{2, 2}, {2, 2}};
    std::vector<std::vector<int>> C = MatMul::strassen_multiply(A, B);
    for (int i = 0; i < C.size(); i++)
    {
        for (int j = 0; j < C[0].size(); j++)
        {
            std::cout << " " << C[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
