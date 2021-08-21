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