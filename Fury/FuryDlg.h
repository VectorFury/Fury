
// FuryDlg.h: 头文件
//

#pragma once
#include"Decompilation.h"

// CFuryDlg 对话框
class CFuryDlg : public CDialogEx
{
// 构造
public:
	CFuryDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FURY_DIALOG };
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

	afx_msg void OnBnClickedButtonLoadFile();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButtonFanBianYi();
	TCHAR* StringToChar(CString& str);
	afx_msg void OnBnClickedButtonBackToCompile();
	afx_msg void OnEnChangeEditFilePath();



private:
	CString Select_File_PATH;     //选择的文件路径
	CString Select_File_Name;     //选择的文件名
	CString Select_File_Full_Path;
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CEdit m_EditControl_FilePath;
};
