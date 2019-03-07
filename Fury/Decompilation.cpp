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
	调用apktool的jar包
***********************************/
bool Decompilation::CallApkTool(const CString& strApkName) {
	
	WCHAR sSysDir[MAX_PATH] = { 0 };
	GetSystemDirectory(sSysDir, MAX_PATH);
	CString strFullPath = sSysDir;
	strFullPath += _T("\\cmd.exe");
	CString strCmdLine = _T(" /C ");
	strCmdLine += _T("java -jar ");
	CString apktool = _T("F:\\C++\\Fury\\tool\\apktool.jar");    //暂时写死apktool的路径
	strCmdLine += apktool;
	strCmdLine += _T(" d ");
	strCmdLine += strApkName;   //构造CMD的命令行  java -jar ...apktool.jar d *.apk
	

	//创建进程
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	BOOL bRunApkTool = CreateProcess(strFullPath.GetBuffer(), strCmdLine.GetBuffer(), NULL,NULL,FALSE, 0, NULL, NULL, &si, &pi);
	int x = GetLastError();

	strFullPath.ReleaseBuffer();
	strCmdLine.ReleaseBuffer();

	//判断进程是否创建运行成功
	if (!bRunApkTool) {
		return false;
	}

	//等待程序运行结束之后关闭句柄
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);

	return true;

}