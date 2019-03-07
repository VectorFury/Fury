#pragma once
#include<string>
#include<Windows.h>

using namespace std;

/*
	执行对于APK文件的反编译
*/


class Decompilation
{
public:
	Decompilation();

	~Decompilation();


	/**
	执行jar包的调用，执行完毕返回结果
	strJarDir jar包的目录
	strJarName jar包的名称
	**/
	bool Run(const CString& strApkDir, const CString& strApkName);

private:
	bool CallApkTool(const CString& strApkName);
};
