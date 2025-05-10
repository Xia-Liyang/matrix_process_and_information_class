
// MFC_matrix_processDlg.h: 头文件
//

#pragma once

#include "Matrix_process.h"
// CMFCmatrixprocessDlg 对话框
class CMFCmatrixprocessDlg : public CDialogEx
{
// 构造
public:
	CMFCmatrixprocessDlg(CWnd* pParent = nullptr);	// 标准构造函数
	//获取用户输入的文件地址
	CString file_address_user_input;
	matrix input_img_indx;
	int** input_img;
	bool is_input;
	int** conv_img;
	int kernal_size;
	int **kernal;
	int padding;
	int stride;
	int** bilinear_img;
	matrix* bilinear_img_indx;
	matrix *conv_img_indx;
	float PSNR;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_MATRIX_PROCESS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit12();
	CStatic input_pic_frame;
	afx_msg void OnStnClickedStaticpic1();
	afx_msg void OnStnClickedStaticpic2();
	afx_msg void OnStnClickedStaticpic3();
	CComboBox padding_ctrl;
	CComboBox stride_ctrl;
	CEdit PSNR_result;
	CEdit kernal_00;
	CEdit kernal_01;
	CEdit kernal_02;
	CEdit kernal_10;
	CEdit kernal_11;
	CEdit kernal_12;
	CEdit kernal_20;
	CEdit kernal_21;
	CEdit kernal_22;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	CEdit file_name_box;
};
