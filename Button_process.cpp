#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pch.h"
#include "framework.h"
#include "MFC_matrix_process.h"
#include "MFC_matrix_processDlg.h"
#include "afxdialogex.h"
#include <atlimage.h>
#include "Windows.h"
void CMFCmatrixprocessDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	PSNR = caculator_PSNR(input_img, bilinear_img, &input_img_indx); 
    CString temp;  
    temp.Format(_T("%.2f"), PSNR); // Format the float value to a string with 2 decimal places  
    PSNR_result.SetWindowText(temp);
	/*CDialogEx::OnOK();*/
}

void CMFCmatrixprocessDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CMFCmatrixprocessDlg::OnBnClickedButton1()
{
	CMFCmatrixprocessDlg::OnEnChangeEdit1();
	const TCHAR* file_name = file_address_user_input.GetBuffer();
	is_input = true;
	FILE* fp = fopen(file_name, "rb");
	if (fp==NULL)
	{
		MessageBox("请选择一个Y0A后缀的文件","error",MB_ICONASTERISK);
		return;
	}
	else
	{
		input_img_indx.col = 0;
		input_img_indx.row = 0;
		input_img = read_y(fp, &input_img_indx);
		// 准备 BITMAPINFO
		BITMAPINFO bmi = { 0 };
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = input_img_indx.col;
		bmi.bmiHeader.biHeight = -input_img_indx.row; // 上下颠倒
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biCompression = BI_RGB;

		// 计算行对齐后的字节数
		int bytesPerLine = ((input_img_indx.col * 3 + 3) / 4) * 4;
		BYTE* pPixels = new BYTE[bytesPerLine * input_img_indx.row];
		memset(pPixels, 0, bytesPerLine * input_img_indx.row);

		// 填充灰度数据
		for (int i = 0; i < input_img_indx.row; i++) {
			for (int j = 0; j < input_img_indx.col; j++) {
				int idx = i * bytesPerLine + j * 3;
				BYTE gray = (BYTE)input_img[i][j];
				pPixels[idx] = gray;        // B
				pPixels[idx + 1] = gray;    // G
				pPixels[idx + 2] = gray;    // R
			}
		}

		// 创建 HBITMAP
		HDC hdc = ::GetDC(NULL);
		HBITMAP hBitmap = CreateDIBitmap(hdc, &bmi.bmiHeader, CBM_INIT, pPixels, &bmi, DIB_RGB_COLORS);
		::ReleaseDC(NULL, hdc);  // 记得释放 DC

		// 保存 BMP
		CImage INPUT_IMG_CI;
		INPUT_IMG_CI.Attach(hBitmap);
		HRESULT hr = INPUT_IMG_CI.Save(_T("./pic/input_img.bmp"));
		if (hr == S_OK) {
			MessageBox(_T("Image saved successfully as BMP."), "info", MB_ICONASTERISK);
		}
		else {
			AfxMessageBox(_T("Failed to save image as BMP."));
		}

		CRect rect;
		CWnd* pWnd = GetDlgItem(IDC_STATIC_pic_1);
		CClientDC dc(pWnd);
		pWnd->GetClientRect(&rect);
		dc.SetStretchBltMode(STRETCH_HALFTONE);
		INPUT_IMG_CI.Draw(dc.m_hDC, rect);
		INPUT_IMG_CI.Destroy();
		// 清理内存
		delete[] pPixels;
	}

	// TODO: 在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnBnClickedButton2()
{
	padding = padding_ctrl.GetCurSel();
	stride = stride_ctrl.GetCurSel()+1;
	kernal_size = 3;
	if (!is_input)
	{
		AfxMessageBox(_T("请先加载图片"));
		return;
	}
	conv_img_indx = (matrix*)malloc(sizeof(matrix));
	conv_img_indx = caculate_output_size(&input_img_indx,kernal_size,padding,stride);
	conv_img = ask_2d(conv_img_indx);

	matrix_conv(input_img, &input_img_indx,kernal,kernal_size, padding, stride, conv_img,conv_img_indx,true);
	//// 准备 BITMAPINFO
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = conv_img_indx->col;
	bmi.bmiHeader.biHeight = -conv_img_indx->row; // 上下颠倒
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;

	//// 计算行对齐后的字节数
	int bytesPerLine = ((conv_img_indx->col * 3 + 3) / 4) * 4;
	BYTE* pPixels = new BYTE[bytesPerLine * conv_img_indx->row];
	memset(pPixels, 0, bytesPerLine * conv_img_indx->row);

	//// 填充灰度数据
	for (int i = 0; i < conv_img_indx->row; i++) {
		for (int j = 0; j < conv_img_indx->col; j++) {
			int idx = i * bytesPerLine + j * 3;
			BYTE gray = (BYTE)conv_img[i][j];
			pPixels[idx] = gray;        // B
			pPixels[idx + 1] = gray;    // G
			pPixels[idx + 2] = gray;    // R
		}
	}

	//// 创建 HBITMAP
	HDC hdc = ::GetDC(NULL);
	HBITMAP hBitmap = CreateDIBitmap(hdc, &bmi.bmiHeader, CBM_INIT, pPixels, &bmi, DIB_RGB_COLORS);
	::ReleaseDC(NULL, hdc);  // 记得释放 DC

	//// 保存 BMP
	CImage INPUT_IMG_CI;
	INPUT_IMG_CI.Attach(hBitmap);
	HRESULT hr = INPUT_IMG_CI.Save(_T("./pic/conv_img.bmp"));
	if (hr == S_OK) {
		MessageBox(_T("Image saved successfully as BMP."), "info", MB_ICONASTERISK);
	}
	else {
		AfxMessageBox(_T("Failed to save image as BMP."));
	}

	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_pic_2);
	CClientDC dc(pWnd);
	pWnd->GetClientRect(&rect);
	dc.SetStretchBltMode(STRETCH_HALFTONE);
	INPUT_IMG_CI.Draw(dc.m_hDC, rect);
	INPUT_IMG_CI.Destroy();
	//// 清理内存
	delete[] pPixels;


	//显示卷积核
	CString temp;
	temp.Format(_T("%d"), kernal[0][0]);
	kernal_00.SetWindowText(temp);
	temp.Format(_T("%d"), kernal[0][1]);
	kernal_01.SetWindowText(temp);
	temp.Format(_T("%d"), kernal[0][2]);
	kernal_02.SetWindowText(temp);
	temp.Format(_T("%d"), kernal[1][0]);
	kernal_10.SetWindowText(temp);
	temp.Format(_T("%d"), kernal[1][1]);
	kernal_11.SetWindowText(temp);
	temp.Format(_T("%d"), kernal[1][2]);
	kernal_12.SetWindowText(temp);
	temp.Format(_T("%d"), kernal[2][0]);
	kernal_20.SetWindowText(temp);
	temp.Format(_T("%d"), kernal[2][1]);
	kernal_21.SetWindowText(temp);
	temp.Format(_T("%d"), kernal[2][2]);
	kernal_22.SetWindowText(temp);
	// 释放内存
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnBnClickedButton3()
{
	bilinear_img = ask_2d(&input_img_indx);
	Bilinear(conv_img, conv_img_indx,bilinear_img, &input_img_indx);
	//// 准备 BITMAPINFO
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = input_img_indx.col;
	bmi.bmiHeader.biHeight = -input_img_indx.row; // 上下颠倒
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;

	//// 计算行对齐后的字节数
	int bytesPerLine = ((input_img_indx.col * 3 + 3) / 4) * 4;
	BYTE* pPixels = new BYTE[bytesPerLine * input_img_indx.row];
	memset(pPixels, 0, bytesPerLine * input_img_indx.row);

	// 填充灰度数据
	for (int i = 0; i < input_img_indx.row; i++) {
		for (int j = 0; j < input_img_indx.col; j++) {
			int idx = i * bytesPerLine + j * 3;
			BYTE gray = (BYTE)bilinear_img[i][j];
			pPixels[idx] = gray;        // B
			pPixels[idx + 1] = gray;    // G
			pPixels[idx + 2] = gray;    // R
		}
	}

	//// 创建 HBITMAP
	HDC hdc = ::GetDC(NULL);
	HBITMAP hBitmap = CreateDIBitmap(hdc, &bmi.bmiHeader, CBM_INIT, pPixels, &bmi, DIB_RGB_COLORS);
	::ReleaseDC(NULL, hdc);  // 记得释放 DC

	//// 保存 BMP
	CImage INPUT_IMG_CI;
	INPUT_IMG_CI.Attach(hBitmap);
	HRESULT hr = INPUT_IMG_CI.Save(_T("./pic/bilinear.bmp"));
	if (hr == S_OK) {
		MessageBox(_T("Image saved successfully as BMP."), "info", MB_ICONASTERISK);
	}
	else {
		AfxMessageBox(_T("Failed to save image as BMP."));
	}

	CRect rect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_pic_3);
	CClientDC dc(pWnd);
	pWnd->GetClientRect(&rect);
	dc.SetStretchBltMode(STRETCH_HALFTONE);
	INPUT_IMG_CI.Draw(dc.m_hDC, rect);
	INPUT_IMG_CI.Destroy();
	//// 清理内存
	delete[] pPixels;
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnBnClickedButton4()
{
	MessageBox("Copyright (C) 2025 XLY. All Rights Reserved.","Copyright", MB_ICONASTERISK);
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnBnClickedButton5()
{
	CString temp;
	kernal_00.GetWindowText(temp);
	if (temp.IsEmpty())
	{
		MessageBox("请输入卷积核的值", "error", MB_ICONASTERISK);
		temp = "1";
		return;
	}
	kernal[0][0] = _ttoi(temp);
	kernal_01.GetWindowText(temp);
	if (temp.IsEmpty())
	{
		MessageBox("请输入卷积核的值", "error", MB_ICONASTERISK);
		temp = "1";
		return;
	}
	kernal[0][1] = _ttoi(temp);
	kernal_02.GetWindowText(temp);
	if (temp.IsEmpty())
	{
		MessageBox("请输入卷积核的值", "error", MB_ICONASTERISK);
		temp = "1";
		return;
	}
	kernal[0][2] = _ttoi(temp);
	kernal_10.GetWindowText(temp);
	if (temp.IsEmpty())
	{
		MessageBox("请输入卷积核的值", "error", MB_ICONASTERISK);
		temp = "1";
		return;
	}
	kernal[1][0] = _ttoi(temp);
	kernal_11.GetWindowText(temp);
	if (temp.IsEmpty())
	{
		MessageBox("请输入卷积核的值", "error", MB_ICONASTERISK);
		temp = "1";
		return;
	}
	kernal[1][1] = _ttoi(temp);
	kernal_12.GetWindowText(temp);
	if (temp.IsEmpty())
	{
		MessageBox("请输入卷积核的值", "error", MB_ICONASTERISK);
		temp = "1";
		return;
	}
	kernal[1][2] = _ttoi(temp);
	kernal_20.GetWindowText(temp);
	if (temp.IsEmpty())
	{
		MessageBox("请输入卷积核的值", "error", MB_ICONASTERISK);
		temp = "1";
		return;
	}
	kernal[2][0] = _ttoi(temp);
	kernal_21.GetWindowText(temp);
	if (temp.IsEmpty())
	{
		MessageBox("请输入卷积核的值", "error", MB_ICONASTERISK);
		temp = "1";
		return;
	}
	kernal[2][1] = _ttoi(temp);
	kernal_22.GetWindowText(temp);
	if (temp.IsEmpty())
	{
		MessageBox("请输入卷积核的值", "error", MB_ICONASTERISK);
		temp = "1";
		return;
	}
	kernal[2][2] = _ttoi(temp);
	MessageBox("卷积核设置成功", "info", MB_ICONASTERISK);
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码

	CFileDialog dlg(TRUE, _T("*.y0a"), "", OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, "y0a files (*.y0a)|*.y0a|", NULL);
	char title[] = { "Open y0a" };
	dlg.m_ofn.lpstrTitle = title;
	if (dlg.DoModal() == IDOK)
	{
		file_address_user_input = dlg.GetPathName();
		file_name_box.SetWindowText(file_address_user_input);
	}
	else
		return;

}