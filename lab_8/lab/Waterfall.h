
// Waterfall.h : Waterfall ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CWaterfallApp:
// �� Ŭ������ ������ ���ؼ��� Waterfall.cpp�� �����Ͻʽÿ�.
//

class CWaterfallApp : public CWinApp
{
public:
	CWaterfallApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CWaterfallApp theApp;
