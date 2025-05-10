#include <stdio.h>

// 双线性插值函数
float bilinear_interpolate(float x1, float y1, float x2, float y2, float x, float y)
{
    float value = (x2 - x) * (y2 - y) * x1 + (x - x1) * (y2 - y) * x2 + (x2 - x) * (y - y1) * y1 + (x - x1) * (y - y1) * y2;
    return value;
}

// 将3x3矩阵扩展为4x4矩阵
void expand_matrix(float input[3][3], float output[4][4])
{
    // 双线性插值扩展
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // 计算插值的坐标
            float x = (i) / 3.0 * 2; // 横坐标（0~2范围）
            float y = (j) / 3.0 * 2; // 纵坐标（0~2范围）

            // 四个邻近点的坐标
            int x1 = (int)x;
            int y1 = (int)y;
            int x2 = (x1 + 1 < 3) ? x1 + 1 : x1;
            int y2 = (y1 + 1 < 3) ? y1 + 1 : y1;

            // 计算插值
            output[i][j] = bilinear_interpolate(input[x1][y1], input[x2][y1], input[x1][y2], input[x2][y2], x, y);
        }
    }
}

// 打印矩阵
void print_matrix(float matrix[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    // 输入3x3矩阵
    float input[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    // 输出4x4矩阵
    float output[4][4];

    // 扩展矩阵
    expand_matrix(input, output);

    // 打印扩展后的矩阵
    printf("Expanded 4x4 matrix:\n");
    print_matrix(output);

    return 0;
}

/*void CMFCmatrixprocessDlg::OnBnClickedButtonnew()
{

    // TODO: 在此添加控件通知处理程序代码
} */