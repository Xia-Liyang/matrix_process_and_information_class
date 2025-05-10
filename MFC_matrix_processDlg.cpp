
// MFC_matrix_processDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC_matrix_process.h"
#include "MFC_matrix_processDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCmatrixprocessDlg 对话框



CMFCmatrixprocessDlg::CMFCmatrixprocessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_MATRIX_PROCESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCmatrixprocessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_pic_1, input_pic_frame);
	DDX_Control(pDX, IDC_COMBO1, padding_ctrl);
	DDX_Control(pDX, IDC_COMBO2, stride_ctrl);
	DDX_Control(pDX, IDC_EDIT4, kernal_00);
	DDX_Control(pDX, IDC_EDIT5, kernal_01);
	DDX_Control(pDX, IDC_EDIT6, kernal_02);
	DDX_Control(pDX, IDC_EDIT7, kernal_10);
	DDX_Control(pDX, IDC_EDIT8, kernal_11);
	DDX_Control(pDX, IDC_EDIT9, kernal_12);
	DDX_Control(pDX, IDC_EDIT10, kernal_20);
	DDX_Control(pDX, IDC_EDIT11, kernal_21);
	DDX_Control(pDX, IDC_EDIT12, kernal_22);
	DDX_Control(pDX, IDC_EDIT3, PSNR_result);
	DDX_Control(pDX, IDC_EDIT1, file_name_box);
}

BEGIN_MESSAGE_MAP(CMFCmatrixprocessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCmatrixprocessDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCmatrixprocessDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCmatrixprocessDlg::OnEnChangeEdit1)
	//ON_EN_CHANGE(IDC_EDIT2, &CMFCmatrixprocessDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCmatrixprocessDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCmatrixprocessDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCmatrixprocessDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCmatrixprocessDlg::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCmatrixprocessDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCmatrixprocessDlg::OnCbnSelchangeCombo2)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCmatrixprocessDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CMFCmatrixprocessDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CMFCmatrixprocessDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CMFCmatrixprocessDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &CMFCmatrixprocessDlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, &CMFCmatrixprocessDlg::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, &CMFCmatrixprocessDlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, &CMFCmatrixprocessDlg::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, &CMFCmatrixprocessDlg::OnEnChangeEdit12)
	ON_STN_CLICKED(IDC_STATIC_pic_1, &CMFCmatrixprocessDlg::OnStnClickedStaticpic1)
	ON_STN_CLICKED(IDC_STATIC_pic_2, &CMFCmatrixprocessDlg::OnStnClickedStaticpic2)
	ON_STN_CLICKED(IDC_STATIC_pic_3, &CMFCmatrixprocessDlg::OnStnClickedStaticpic3)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCmatrixprocessDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCmatrixprocessDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCmatrixprocessDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMFCmatrixprocessDlg 消息处理程序

BOOL CMFCmatrixprocessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	/*对于combox控件的初始化*/
	padding_ctrl.AddString("0");
	padding_ctrl.AddString("1");
	padding_ctrl.AddString("2");
	padding_ctrl.AddString("3");
	padding_ctrl.SetCurSel(2);


	stride_ctrl.AddString("1");
	stride_ctrl.AddString("2");
	stride_ctrl.AddString("3");
	stride_ctrl.SetCurSel(1);

	//对于卷积核的初始化
	matrix kernal_indx;
	kernal_indx.col = 3;
	kernal_indx.row = 3;
	kernal=ask_2d(&kernal_indx);
	for (int i = 0; i < kernal_indx.col; i++)
	{
		for (int j = 0; j < kernal_indx.row; j++) {
			kernal[i][j] = 1;
		}
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCmatrixprocessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCmatrixprocessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCmatrixprocessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CMFCmatrixprocessDlg::OnEnChangeEdit1()
{
	GetDlgItemText(IDC_EDIT1, file_address_user_input);
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}








void CMFCmatrixprocessDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

}

void CMFCmatrixprocessDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
}







void CMFCmatrixprocessDlg::OnEnChangeEdit4()
{

	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnEnChangeEdit9()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnEnChangeEdit10()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnEnChangeEdit11()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnEnChangeEdit12()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnStnClickedStaticpic1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnStnClickedStaticpic2()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCmatrixprocessDlg::OnStnClickedStaticpic3()
{
	// TODO: 在此添加控件通知处理程序代码
}





void CMFCmatrixprocessDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




