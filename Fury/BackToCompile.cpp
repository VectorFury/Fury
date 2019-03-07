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
	CString apktool = _T("F:\\C++\\Fury\\tool\\apktool.jar");    //暂时写死apktool的路径
	strCmdLine += apktool;
	strCmdLine += _T(" b ");
	strCmdLine += BackToCompileApkPath;   //构造CMD的命令行  java -jar ...apktool.jar d *.apk

	//一些改变
	//创建进程
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	BOOL bRunApkToolBack = CreateProcess(strFullPath.GetBuffer(), strCmdLine.GetBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	int x = GetLastError();

	strFullPath.ReleaseBuffer();
	strCmdLine.ReleaseBuffer();

	//判断进程是否创建运行成功
	if (!bRunApkToolBack) {
		return false;
	}

	//等待程序运行结束之后关闭句柄
	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);

	return true;
}