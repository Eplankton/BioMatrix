//The extension content in this headfile is taken from Web, for learning only.

//From: https://zhuanlan.zhihu.com/p/305328519
double determinant(double matrix[20][20], int order);
double laplace_expansion(double matrix[20][20], int r, int c, int order);

double determinant(double matrix[20][20], int order)
{
    int sign = 1, i;
    double result = 0, cofactor;
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

double laplace_expansion(double matrix[20][20], int r, int c, int order)
{
    double result = 0, cofactor[20][20];
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
double standard_echelon(double matrix[20][20], int r, int c, int x, int y);

int rank(double matrix[20][20], int r, int c)
{
    double echelon_matrix[20][20];
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

double standard_echelon(double matrix[20][20], int r, int c, int x, int y)
{
    int i, j, k, l, total[20] = {0};
    double times, temp, result = 0, original_matrix[20][20];

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
