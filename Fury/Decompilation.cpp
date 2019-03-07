#include "stdafx.h"
#include "Decompilation.h"
#include "FuryDlg.h"



Decompilation::Decompilation()
{
	
}


Decompilation::~Decompilation()
{
}


bool Decompilation::Run(const CString& strApkDir, const CString& strApkName) {

	WCHAR sOldDir[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, sOldDir);

	SetCurrentDirectory(strApkDir);
	bool bCalRest = CallApkTool(strApkName);

	SetCurrentDirectory(sOldDir);


	return bCalRest;
}

/**********************************
	����apktool��jar��
***********************************/
bool Decompilation::CallApkTool(const CString& strApkName) {
	
	WCHAR sSysDir[MAX_PATH] = { 0 };
	GetSystemDirectory(sSysDir, MAX_PATH);
	CString strFullPath = sSysDir;
	strFullPath += _T("\\cmd.exe");
	CString strCmdLine = _T(" /C ");
	strCmdLine += _T("java -jar ");
	CString apktool = _T("F:\\C++\\Fury\\tool\\apktool.jar");    //��ʱд��apktool��·��
	strCmdLine += apktool;
	strCmdLine += _T(" d ");
	strCmdLine += strApkName;   //����CMD��������  java -jar ...apktool.jar d *.apk
	

	//��������
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	BOOL bRunApkTool = CreateProcess(strFullPath.GetBuffer(), strCmdLine.GetBuffer(), NULL,NULL,FALSE, 0, NULL, NULL, &si, &pi);
	int x = GetLastError();

	strFullPath.ReleaseBuffer();
	strCmdLine.ReleaseBuffer();

	//�жϽ����Ƿ񴴽����гɹ�
	if (!bRunApkTool) {
		return false;
	}

	//�ȴ��������н���֮��رվ��
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);

	return true;

}