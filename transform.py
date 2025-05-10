import numpy as np
import cv2

# 读取数据
volt_matrix = np.loadtxt("output.txt")
bli_matrix = np.loadtxt("./output_interpolation.txt")
suorce_matrix = np.loadtxt("./out.txt")
print(volt_matrix)
print(bli_matrix)
print(suorce_matrix)

# 打印矩阵信息
print("Matrix shape is", suorce_matrix.shape)
print("Matrix size is", suorce_matrix.size)


# 标准化数据到 0-255 范围
def normalize_and_convert(matrix):
    if matrix.dtype != np.uint8:
        # 归一化到 0-1
        normalized = (matrix - matrix.min()) / (matrix.max() - matrix.min())
        # 缩放到 0-255 并转换为 uint8
        matrix = (normalized * 255).astype(np.uint8)
    return matrix


volt_matrix = normalize_and_convert(volt_matrix)
bli_matrix = normalize_and_convert(bli_matrix)
suorce_matrix = normalize_and_convert(suorce_matrix)

# 显示图像
cv2.imshow("volt_matrix", volt_matrix)
cv2.imshow("bli_matrix", bli_matrix)
cv2.imshow("suorce_matrix", suorce_matrix)

# 保存图像
cv2.imwrite("volt_matrix.bmp", volt_matrix)
cv2.imwrite("suorce_matrix.bmp", suorce_matrix)
cv2.imwrite("bli_matrix.bmp", bli_matrix)


# 计算 PSNR
def calculate_psnr(image1, image2):
    mse = np.mean((image1 - image2) ** 2)
    if mse == 0:
        return 100  # 表示两幅图像完全相同
    PIXEL_MAX = 255.0
    psnr = 10 * np.log10((PIXEL_MAX**2) / mse)
    return psnr


# 计算各图像之间的 PSNR
psnr_bli_suorce = calculate_psnr(bli_matrix, suorce_matrix)

# 打印 PSNR
print(f"PSNR between bli_matrix and suorce_matrix: {psnr_bli_suorce} dB")

cv2.waitKey(0)
cv2.destroyAllWindows()


