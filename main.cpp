#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int row;
    int col;
} matrix;
int **read_y(FILE *fp, matrix *img_indx);
#define GET4BYTE(pos) (((pos)[3] << 24) | ((pos)[2] << 16) | ((pos)[1] << 8) | ((pos)[0]))

int main()
{
    // unsigned char ucBuf[32];
    // int iSize, iWidth, iHeight;
    FILE *fp = fopen("./YA1.y0a", "rb");
    if (fp == NULL)
    {
        printf("打开文件失败\n");
        return 1;
    }

    unsigned char ucBuf[32];
    int iSize, iWidth, iHeight;
    // fread(ucBuf, sizeof(unsigned char), 32, fp);
    // iSize = GET4BYTE(ucBuf + 4);
    iWidth = GET4BYTE(ucBuf + 8);
    iHeight = GET4BYTE(ucBuf + 12);

    matrix img_indx;
    img_indx.row = iHeight;
    img_indx.col = iWidth;
    int **img;
    img = read_y(fp, &img_indx);
    printf("row is %d,col is %d\n", img_indx.row, img_indx.col);
    // for (int i = 0; i < iHeight; i++)
    // {
    //     for (int j = 0; j < iWidth; j++)
    //     {
    //         printf("%d ", img[i][j]);
    //     }
    //     printf("\n");
    // }

    // 读取图像数据到二维数组中

    // unsigned char *img = (unsigned char *)malloc(iWidth * iHeight);
    // if (img == NULL)
    // {
    //     printf("内存分配失败\n");
    //     fclose(fp);
    //     return 1;
    // }

    // for (int i = 0; i < iHeight; i++)
    // {
    //     for (int j = 0; j < iWidth; j++)
    //     {
    //         fread(&img[i * iWidth + j], sizeof(unsigned char), 1, fp);
    //     }
    // }

    // fclose(fp); // 记得关闭文件

    // FILE *out = fopen("./out.txt", "w");
    // for (int i = 0; i < iHeight; i++)
    // {
    //     for (int j = 0; j < iWidth; j++)
    //     {
    //         fprintf(out, "%d ", img[i * iWidth + j]);
    //     }
    //     fprintf(out, "\n");
    // }
    // fclose(out);
    // free(img);

    return 0;
}

/**
 * @brief 读取y0a文件，并写入当前目录下，生成一个txt文件
 *
 * @param fp 读取文件的句柄
 * @param img_indx 返回图片大小数据
 * @return int** 返回一个二维数组，存放了数据
 */
int **read_y(FILE *fp, matrix *img_indx)
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
    int **img = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++)
    {
        img[i] = (int *)malloc(col * sizeof(int));
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
    FILE *out = fopen("./out.txt", "w");
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