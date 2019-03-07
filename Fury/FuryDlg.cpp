
// FuryDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Fury.h"
#include "FuryDlg.h"
#include "afxdialogex.h"
#include "BackToCompile.h"

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


// CFuryDlg 对话框



CFuryDlg::CFuryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FURY_DIALOG, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFuryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE_PATH, m_EditControl_FilePath);
}

BEGIN_MESSAGE_MAP(CFuryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD_FILE, &CFuryDlg::OnBnClickedButtonLoadFile)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CFuryDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON_FAN_BIAN_YI, &CFuryDlg::OnBnClickedButtonFanBianYi)
	ON_BN_CLICKED(IDC_BUTTON_BACK_TO_COMPILE, &CFuryDlg::OnBnClickedButtonBackToCompile)
	ON_EN_CHANGE(IDC_EDIT_FILE_PATH, &CFuryDlg::OnEnChangeEditFilePath)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CFuryDlg 消息处理程序

BOOL CFuryDlg::OnInitDialog()
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
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
	DragAcceptFiles(TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFuryDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFuryDlg::OnPaint()
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
HCURSOR CFuryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFuryDlg::OnBnClickedButtonLoadFile()
{
	// TODO: 在此添加控件通知处理程序代码
	//打开文件
	CFileDialog open_file(TRUE,
		NULL,
		NULL,
		OFN_OVERWRITEPROMPT,
		_T("APK文件(*.apk; *.dex; *.jar)|*.apk; *.dex; *.jar"), 
		NULL);
	if (open_file.DoModal() == IDOK) {

		Select_File_Full_Path = open_file.GetPathName();   //得到所选文件的路径
		Select_File_PATH = open_file.GetFolderPath();
		Select_File_Name = open_file.GetFileName();
		/**
		//从路径中截取到文件名
		string filepath = CT2A(file_select.GetBuffer());    //记得使用GetBuffer之后要释放
		int pos = filepath.find_first_of('/');
		string filename(filepath.substr(pos + 1));
		Select_File_Name = filename.c_str();
		**/

		SetDlgItemText(IDC_EDIT_FILE_PATH, Select_File_Full_Path);     //将文件的路径显示在显示框中
	}else {
		MessageBoxA(NULL, "打开文件的路径错误", "注意", 0);
	}


}


void CFuryDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码



}


/**********************************
		反编译应用
***********************************/
void CFuryDlg::OnBnClickedButtonFanBianYi()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strApkPath = Select_File_PATH;
	CString strApkName = Select_File_Name;

	Decompilation de;
	if (!de.Run(strApkPath, strApkName)) {
		//启动失败
		MessageBoxA(NULL, "反编译失败", "错误", 0);
	}
}


//CString格式转化为TCHAR的格式
TCHAR* CFuryDlg::StringToChar(CString& str) {
	int len = str.GetLength();
	TCHAR* tr = str.GetBuffer(len);
	str.ReleaseBuffer();
	return tr;
}


/**********************************
		回编译应用
***********************************/
void CFuryDlg::OnBnClickedButtonBackToCompile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString CurrentFilePath;
	GetDlgItemText(IDC_EDIT_FILE_PATH, CurrentFilePath);
	//得到当前的目录后调用apktool开始回编译
	BackToCompile btc;
	if (!btc.RunBackToCompile(CurrentFilePath)) {
		MessageBoxA(NULL, "回编译失败", "错误", 0);
	}
	
}



void CFuryDlg::OnEnChangeEditFilePath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



//支持文件到对话框的任意拖拽功能
void CFuryDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int count = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	for (int i = 0; i < count; ++i) {
		wchar_t filepath[MAX_PATH] = { 0 };
		if (DragQueryFile(hDropInfo, i, filepath, MAX_PATH) > 0) {
			m_EditControl_FilePath.SetWindowTextW(filepath);
		}
	}

	CDialogEx::OnDropFiles(hDropInfo);
}
