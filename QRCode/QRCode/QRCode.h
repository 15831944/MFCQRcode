
// QRCode.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

int mainrun(const char*);
// CQRCodeApp:
// �йش����ʵ�֣������ QRCode.cpp
//

class CQRCodeApp : public CWinApp
{
public:
	CQRCodeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQRCodeApp theApp;