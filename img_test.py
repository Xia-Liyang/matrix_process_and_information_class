import cv2
import numpy as np


def psnr(original, compared):
    mse = np.mean((original - compared) ** 2)
    if mse == 0:
        return float("inf")
    PIXEL_MAX = 255.0
    return 10 * np.log10(PIXEL_MAX**2 / mse)


def main(image_path, kernel, padding=1, stride=1):
    # 读取灰度图
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    if img is None:
        print("读取图片失败")
        return

    original_shape = img.shape

    # 使用 OpenCV 进行卷积
    convolved = cv2.filter2D(img, -1, kernel, borderType=cv2.BORDER_CONSTANT)

    # 使用 OpenCV 进行双线性插值回原始大小
    resized = cv2.resize(
        convolved,
        (original_shape[1], original_shape[0]),
        interpolation=cv2.INTER_LINEAR,
    )

    # 计算 PSNR
    computed_psnr = psnr(img.astype(np.float32), resized.astype(np.float32))
    print(f"PSNR: {computed_psnr:.2f} dB")

    # 显示结果
    cv2.imshow("Original", img)
    cv2.imshow("Convolved + Resized", resized.astype(np.uint8))
    cv2.waitKey(0)
    cv2.destroyAllWindows()


if __name__ == "__main__":
    # 设置自定义卷积核
    # 例如：一个简单的 3x3 平均卷积核
    kernel = np.array([[1, 2, 1], [2, 4, 2], [1, 2, 1]], dtype=np.float32) / 16
    # 调整这里的图片路径、padding 和 stride
    main("./volt_matrix.png", kernel, padding=2, stride=1)
