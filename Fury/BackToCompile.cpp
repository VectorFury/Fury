#include "stdafx.h"
#include "BackToCompile.h"


BackToCompile::BackToCompile()
{
}


BackToCompile::~BackToCompile()
{
}


bool BackToCompile::RunBackToCompile(const CString& BackToCompileApkPath)
{
	bool callResult = CallApkTool(BackToCompileApkPath);
	return callResult;
}

bool BackToCompile::CallApkTool(const CString& BackToCompileApkPath)
{
	WCHAR sSysDir[MAX_PATH] = { 0 };
	GetSystemDirectory(sSysDir, MAX_PATH);
	CString strFullPath = sSysDir;
	strFullPath += _T("\\cmd.exe");
	CString strCmdLine = _T(" /C ");
	strCmdLine += _T("java -jar ");
	CString apktool = _T("F:\\C++\\Fury\\tool\\apktool.jar");    //��ʱд��apktool��·��
	strCmdLine += apktool;
	strCmdLine += _T(" b ");
	strCmdLine += BackToCompileApkPath;   //����CMD��������  java -jar ...apktool.jar d *.apk

	//һЩ�ı�
	//��������
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	BOOL bRunApkToolBack = CreateProcess(strFullPath.GetBuffer(), strCmdLine.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	int x = GetLastError();

	strFullPath.ReleaseBuffer();
	strCmdLine.ReleaseBuffer();

	//�жϽ����Ƿ񴴽����гɹ�
	if (!bRunApkToolBack) {
		return false;
	}

	//�ȴ��������н���֮��رվ��
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);

	return true;
}