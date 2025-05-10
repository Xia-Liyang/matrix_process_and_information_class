#ifndef __MATRIX_PROCESSH__
#define __MATRIX_PROCESSH__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// 定义一个结构体，用于存储矩阵的行和列
typedef struct
{
    int row;
    int col;
} matrix;
#define GET4BYTE(pos) (((pos)[3] << 24) | ((pos)[2] << 16) | ((pos)[1] << 8) | ((pos)[0]));
void print_matrix(int** arr, matrix* input_indx);
int** ask_2d(matrix* input_indx);
void free_2d(int** arr, int rows);
void matrix_x(float* input[], int len, int wid, int len2, float** input2, float* output[]);
void matrix_conv(int** input, matrix* input_inx, int** kernel, int kernel_size,
    int padding, int stride, int** output, matrix* output_indx, bool is_init);
void Bilinear(int** input, matrix* input_indx, int** output, matrix* output_indx);
int max_int(int a, int b);
int min_int(int a, int b);
float max_f(float a, float b);
int** read_y(FILE* fp, matrix* img_indx);
matrix* caculate_output_size(matrix* input_inx, int kernal_size, int padding, int stride);
float caculator_PSNR(int** source_img, int** result_img, matrix* img_indx);
#endif // !__MATRIX_PROCESSH__
