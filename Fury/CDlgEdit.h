#pragma once
#include <afxwin.h>
class CDlgEdit :
	public CEdit
{
public:
	CDlgEdit();
	~CDlgEdit();

	afx_msg void OnDropFiles(HDROP hDropInfo);
};

