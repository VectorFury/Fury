#pragma once
#include<string>
#include<Windows.h>

using namespace std;

/*
	ִ�ж���APK�ļ��ķ�����
*/


class Decompilation
{
public:
	Decompilation();

	~Decompilation();


	/**
	ִ��jar���ĵ��ã�ִ����Ϸ��ؽ��
	strJarDir jar����Ŀ¼
	strJarName jar��������
	**/
	bool Run(const CString& strApkDir, const CString& strApkName);

private:
	bool CallApkTool(const CString& strApkName);
};
