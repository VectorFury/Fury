#include "stdafx.h"
#include "CDragEdit.h"


CDragEdit::CDragEdit()
{
}


CDragEdit::~CDragEdit()
{
}


CDragEdit::CDragEdit()
{
}


CDragEdit::~CDragEdit()
{
}


int CDragEdit::WM_CREATE()
{
	// TODO: 在此处添加实现代码.
	DragAcceptFile(TRUE);
	return 0;
}
