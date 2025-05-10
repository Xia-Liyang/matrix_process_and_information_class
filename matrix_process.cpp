#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pch.h"
#include "framework.h"
#include "MFC_matrix_process.h"
#include "MFC_matrix_processDlg.h"
#include "afxdialogex.h"
#define _CRT_SECURE_NO_WARNINGS


/**
 * @brief 进行矩阵的乘法,支持任意维度
 * 请保证输入矩阵的行数相同，不然将返回不正确的值
 * @param input 输入矩阵1
 * @param len 输入矩阵的行数
 * @param wid 输入矩阵的列数
 * @param len2 输出矩阵的列数
 * @param input2 输入矩阵2
 * @param output 输出矩阵
 */
void matrix_x(float* input[], int len, int wid, int len2, float** input2, float* output[])
{
    for (int i = 0; i < len2; i++) // 遍历输入矩阵2的所有行
    {
        for (int j = 0; j < len; j++) // 遍历输入矩阵1的所有行
        {
            for (int k = 0; k < wid; k++) // 遍历矩阵的所有列
            {
                output[j][i] += input[j][k] * input2[k][i];
            }
        }
    }
}

/**
 * @brief 打印二维动态数组
 *
 * @param arr   二维动态数组的指针
 * @param input_indx 输入图像的参数结构体，反映尺寸
 */
void print_matrix(int** arr, matrix* input_indx)
{
    for (int i = 0; i < input_indx->row; i++)
    {
        for (int j = 0; j < input_indx->col; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief 申请二维动态数组，并初始化为0
 *
 * @param input_indx 输入图像的参数结构体，反映尺寸
 * @return 返回值为二维数组的指针
 */
int** ask_2d(matrix* input_indx)
{
    int rows = input_indx->row;
    int cols = input_indx->col;
    int** arr = (int**)malloc(rows * sizeof(int*));
    {
        for (int i = 0; i < rows; i++)
        {
            arr[i] = (int*)malloc(cols * sizeof(int));
            for (int j = 0; j < cols; j++)
            {
                arr[i][j] = 0;
            }
        }
    }
    return arr;
}

/**
 * @brief 释放二维动态数组
 *
 * @param arr   二维动态数组的指针
 * @param rows  行数
 */
void free_2d(int** arr, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

/**
 * @brief 进行图像卷积
 *
 * @param input 输入图像
 * @param input_inx 输入图像的参数结构体，反映尺寸
 * @param kernel    输入卷积核
 * @param kernel_size   卷积核尺寸，为整数
 * @param padding   填充，在本次实验中默认为2
 * @param stride    卷积步长
 * @param output    输出图像
 * @param is_init   是否需要归一化
 * @note 该函数支持对输入图像进行padding操作，padding的方式为对称填充
 */
void matrix_conv(int** input, matrix* input_inx, int** kernel, int kernel_size,
    int padding, int stride, int** output,matrix* output_indx, bool is_init)
{
    int padded_row = input_inx->row + 2 * padding;
    int padded_col = input_inx->col + 2 * padding;

    int out_row = (padded_row - kernel_size) / stride + 1;
    int out_col = (padded_col - kernel_size) / stride + 1;

    int** input_padding = NULL;
    int sum_ker = 0;
    for (int i = 0; i < kernel_size; i++)
    {
        for (int j = 0; j < kernel_size; j++)
        {
            sum_ker += kernel[i][j];
        }
    }

    if (padding > 0)
    {
        // 申请带padding的新输入
        input_padding = (int**)malloc(padded_row * sizeof(int*));
        for (int i = 0; i < padded_row; i++)
        {
            input_padding[i] = (int*)malloc(padded_col * sizeof(int));
        }

        // 镜像填充
        for (int i = 0; i < padded_row; i++)
        {
            for (int j = 0; j < padded_col; j++)
            {
                int orig_i = i - padding;
                int orig_j = j - padding;

                if (orig_i < 0)
                    orig_i = -orig_i - 1;
                else if (orig_i >= input_inx->row)
                    orig_i = 2 * input_inx->row - orig_i - 1;

                if (orig_j < 0)
                    orig_j = -orig_j - 1;
                else if (orig_j >= input_inx->col)
                    orig_j = 2 * input_inx->col - orig_j - 1;

                // Clamp 以防万一
                orig_i = max_int(0, min_int(orig_i, input_inx->row - 1));
                orig_j = max_int(0, min_int(orig_j, input_inx->col - 1));

                input_padding[i][j] = input[orig_i][orig_j];
            }
        }

        // 打印 padded 输入（仅当 padding > 0）
        // printf("Padded Input Matrix:\n");
        // for (int i = 0; i < padded_row; i++)
        // {
        //     for (int j = 0; j < padded_col; j++)
        //     {
        //         printf("%4d ", input_padding[i][j]);
        //     }
        //     printf("\n");
        // }
    }

    int** effective_input = (padding > 0) ? input_padding : input;

    // 卷积操作
    for (int i = 0, out_i = 0; i <= padded_row - kernel_size; i += stride, out_i++)
    {
        for (int j = 0, out_j = 0; j <= padded_col - kernel_size; j += stride, out_j++)
        {
            int sum = 0;
            for (int ki = 0; ki < kernel_size; ki++)
            {
                for (int kj = 0; kj < kernel_size; kj++)
                {
                    sum += kernel[ki][kj] * effective_input[i + ki][j + kj];
                }
            }

            if (is_init)
            {
                if (sum_ker==0)
                {
                    output[out_i][out_j] = sum/(kernel_size*kernel_size);
                }
                else
                {
                    output[out_i][out_j] = sum / sum_ker;
                }
                
            }
            else
            {
                output[out_i][out_j] = sum;
            }
        }
    }

    if (padding > 0)
    {
        free_2d(input_padding, padded_row);
    }
    //// 归一化到 0–255
    //int max_val = output[0][0];
    //int min_val = output[0][0];
    //for (int i = 0; i < out_row; i++)
    //{
    //    for (int j = 0; j < out_col; j++)
    //    {
    //        if (output[i][j] > max_val)
    //            max_val = output[i][j];
    //        if (output[i][j] < min_val)
    //            min_val = output[i][j];
    //    }
    //}

    //// 防止除0
    //if (max_val != min_val)
    //{
    //    for (int i = 0; i < out_row; i++)
    //    {
    //        for (int j = 0; j < out_col; j++)
    //        {
    //            output[i][j] = (output[i][j] - min_val) * 255 / (max_val - min_val);
    //        }
    //    }
    //}
    //else
    //{
    //    // 如果全是同一个值，直接设为0或255（这里用0）
    //    for (int i = 0; i < out_row; i++)
    //    {
    //        for (int j = 0; j < out_col; j++)
    //        {
    //            output[i][j] = 0;
    //        }
    //    }
    //}
}

/**
 * @brief 计算输出图像的尺寸
 *
 * @param input_inx     输入图像的尺寸
 * @param kernal_size       卷积核的尺寸
 * @param padding   填充的大小
 * @param stride    卷积的步长
 * @return matrix*  输出图像的尺寸的结构体指针
 * @note 该函数用于计算卷积操作后输出图像的尺寸
 */
matrix* caculate_output_size(matrix* input_inx, int kernal_size, int padding, int stride)
{
    matrix* output_size = (matrix*)malloc(sizeof(matrix));
    output_size->row = (input_inx->row - kernal_size + 2 * padding) / stride + 1;
    output_size->col = (input_inx->col - kernal_size + 2 * padding) / stride + 1;
    return output_size;
}
int min_int(int a, int b)
{
    return (a < b) ? a : b;
}

int max_int(int a, int b)
{
    return (a > b) ? a : b;
}

float max_f(float a, float b)
{
    return (a > b) ? a : b;
}

/**
 * @brief 进行双线性插值
 *
 * @param input 输入图像（二维 int 数组，按 [row][col]）
 * @param input_indx 输入图像的尺寸
 * @param output 输出图像（二维 int 数组，按 [row][col]）
 * @param output_indx 输出图像的尺寸
 */
void Bilinear(int** input, matrix* input_indx, int** output, matrix* output_indx)
{
    int input_row = input_indx->row;
    int input_col = input_indx->col;
    int output_row = output_indx->row;
    int output_col = output_indx->col;

    float scale_x = (float)input_col / output_col;
    float scale_y = (float)input_row / output_row;

    for (int i = 0; i < output_row; i++)
    {
        for (int j = 0; j < output_col; j++)
        {
            // 计算原图中对应的浮点坐标
            float src_y = (i + 0.5f) * scale_y - 0.5f;
            float src_x = (j + 0.5f) * scale_x - 0.5f;
            src_x = max(0.0f, (j + 0.5f) * scale_x - 0.5f);
            src_y = max(0.0f, (i + 0.5f) * scale_y - 0.5f);

            int y0 = max_int(0, (int)floorf(src_y));
            int x0 = max_int(0, (int)floorf(src_x));
            int y1 = min_int(y0 + 1, input_row - 1);
            int x1 = min_int(x0 + 1, input_col - 1);

            float dy = src_y - y0;
            float dx = src_x - x0;

            // 双线性插值
            float top = (1 - dx) * input[y0][x0] + dx * input[y0][x1];
            float bottom = (1 - dx) * input[y1][x0] + dx * input[y1][x1];
            float interpolated = (1 - dy) * top + dy * bottom;

            output[i][j] = (int)(interpolated + 0.5f); // 四舍五入
        }
    }
}

/**
 * @brief 读取y0a文件，并写入当前目录下，生成一个txt文件
 *
 * @param fp 读取文件的句柄
 * @param img_indx 返回图片大小数据
 * @return int** 返回一个二维数组，存放了数据
 */
int** read_y(FILE* fp, matrix* img_indx)
{
    int row;
    int col;
    unsigned char Y0A_indx[32];
    if (fp == NULL)
    {
        printf("打开文件失败\n");
    }
    fread(Y0A_indx, sizeof(unsigned char), 32, fp);
    row = GET4BYTE(Y0A_indx + 12);
    col = GET4BYTE(Y0A_indx + 8);
    img_indx->col = col;
    img_indx->row = row;
    printf("row is %d,col is %d\n", row, col);
    unsigned char temp;
    int** img = (int**)malloc(row * sizeof(int*));
    for (int i = 0; i < row; i++)
    {
        img[i] = (int*)malloc(col * sizeof(int));
        for (int j = 0; j < col; j++)
        {
            img[i][j] = 0;
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fread(&temp, sizeof(unsigned char), 1, fp);
            img[i][j] = (int)temp;
            // printf("%d ", img[i][j]);
        }
    }
    FILE* out = fopen("./out.txt", "w");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fprintf(out, "%d ", img[i][j]);
        }
        fprintf(out, "\n");
    }
    return img;
}

/**
 * @brief 计算PSNR
 *
 * @param source_img    源图像二维矩阵
 * @param result_img    处理完之后的图像的二维矩阵
 * @param img_indx  矩阵大小
 * @return float 返回值为float，PSNR的值
 */
float caculator_PSNR(int** source_img, int** result_img, matrix* img_indx)
{
    int row = img_indx->row;
    int col = img_indx->col;
    float sum = 0.0f;

    for (int i = 0; i < row; i++)
    {
        for (int k = 0; k < col; k++)
        {
            // 归一化到 [0,1]
            float src = (float)source_img[i][k] / 255.0f;
            float res = (float)result_img[i][k] / 255.0f;

            float diff = src - res;
            sum += diff * diff;
        }
    }

    sum = sum / (float)(row * col);

    if (sum == 0.0f)
        return INFINITY; // 或者 return FLT_MAX;

    // 因为归一化到 [0,1]，所以最大值是 1
    return 10.0f * log10f(1.0f / sum);
}
