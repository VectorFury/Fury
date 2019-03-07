#pragma once

#include<Windows.h>

using namespace std;


class BackToCompile
{
public:
	BackToCompile();
	~BackToCompile();


public:
	bool RunBackToCompile(const CString& BackToCompileApkPath);
private:
	bool CallApkTool(const CString& BackToCompileApkPath);
	
};

