// EsTsO.h : EsTsO DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEsTsOApp
// �йش���ʵ�ֵ���Ϣ������� EsTsO.cpp
//

class CEsTsOApp : public CWinApp
{
public:
	CEsTsOApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
