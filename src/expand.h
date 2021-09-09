//The content in this headfile is taken from Web, for learning only.

//From: https://zhuanlan.zhihu.com/p/305328519
float determinant(float matrix[20][20], int order);
float laplace_expansion(float matrix[20][20], int r, int c, int order);

float determinant(float matrix[20][20], int order)
{
    int sign = 1, i;
    float result = 0, cofactor;
    if (order == 1)
        result = matrix[0][0];
    else
        for (i = 0; i < order; i++)
        {
            cofactor = laplace_expansion(matrix, i, 0, order);
            result += sign * matrix[i][0] * cofactor;
            sign *= -1;
        }

    return result;
}

float laplace_expansion(float matrix[20][20], int r, int c, int order)
{
    float result = 0, cofactor[20][20];
    int original_i, original_j, i, j;

    for (i = 0; i < order; i++)
        for (j = 0; j < order; j++)
        {
            original_i = i;
            original_j = j;
            if (i == r || j == c)
                ;
            else
            {
                if (i > r)
                    i--;
                if (j > c)
                    j--;
                cofactor[i][j] = matrix[original_i][original_j];
                i = original_i;
                j = original_j;
            }
        }
    if (order >= 2)
        result = determinant(cofactor, order - 1);

    return result;
}

//From: https://zhuanlan.zhihu.com/p/312177505
//#include <stdio.h>
//#include <math.h>
/* int rank(float matrix[20][20], int r, int c);
float standard_echelon(float matrix[20][20], int r, int c, int x, int y);
void show_standard_echelon(float matrix[20][20], int r, int c);

int main()
{
    float matrix[20][20];
    int i, j, r, c;

    printf("row:");
    scanf("%d", &r);
    printf("cloumn:");
    scanf("%d", &c);
    printf("matrix:\n");
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            scanf("%f", &matrix[i][j]);

    printf("rank = %d.\n", rank(matrix, r, c));
    printf("fuck:\n");
    show_standard_echelon(matrix, r, c);

    return 0;
}

int rank(float matrix[20][20], int r, int c)
{
    float echelon_matrix[20][20];
    int i, j, none_zero = 0, result = 0;

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            echelon_matrix[i][j] = standard_echelon(matrix, r, c, i, j);

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
            if (echelon_matrix[i][j] != 0)
            {
                none_zero = 1;
                break;
            }
        if (none_zero == 1)
            result++;
        none_zero = 0;
    }
    return result;
}

float standard_echelon(float matrix[20][20], int r, int c, int x, int y)
{
    int i, j, k, l, total[20] = {0};
    float times, temp, result = 0, original_matrix[20][20];

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            original_matrix[i][j] = matrix[i][j];
    for (i = 0; i < r - 1; i++)
        for (k = i + 1; k < r; k++)
        {
            j = 0;
            while (matrix[i][j] == 0)
                j++;
            if (matrix[i][j] != 0)
            {
                times = matrix[k][j] / matrix[i][j];
                for (j = 0; j < c; j++)
                    matrix[k][j] -= matrix[i][j] * times;
            }
        }
    for (i = 0; i < r; i++)
    {
        j = 0;
        while (matrix[i][j] == 0)
            j++;
        if (matrix[i][j] != 0)
        {
            times = matrix[i][j];
            for (j = 0; j < c; j++)
                matrix[i][j] /= times;
        }
    }
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            if (matrix[i][j] == 0)
                total[i]++;
            else
                break;
    for (l = r - 1; l > 0; l--)
        for (i = 0; i < l; i++)
            if (total[l] < total[i])
                for (j = 0; j < c; j++)
                {
                    temp = matrix[l][j];
                    matrix[l][j] = matrix[i][j];
                    matrix[i][j] = temp;
                }
    for (i = 0; i < r; i++)
    {
        j = 0;
        while (matrix[i][j] == 0)
            j++;
        if (matrix[i][j] != 0)
            for (k = 0; k < i; k++)
            {
                times = matrix[k][j] / matrix[i][j];
                for (l = 0; l < c; l++)
                    matrix[k][l] -= times * matrix[i][l];
            }
    }
    result = matrix[x][y];
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            matrix[i][j] = original_matrix[i][j];
    if (fabs(result) <= 0.0005)
        result = 0;

    return result;
}

void show_standard_echelon(float matrix[20][20], int r, int c)
{
    float echelon_matrix[20][20];
    int i, j;

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            echelon_matrix[i][j] = standard_echelon(matrix, r, c, i, j);

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (fabs(echelon_matrix[i][j]) < 0.0005)
                echelon_matrix[i][j] = fabs(echelon_matrix[i][j]);
            printf("%.3f\t", echelon_matrix[i][j]);
        }
        printf("\n");
    }
} */