
// ToolOfSelectedFilePacking.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CToolOfSelectedFilePackingApp:
// �йش����ʵ�֣������ ToolOfSelectedFilePacking.cpp
//

class CToolOfSelectedFilePackingApp : public CWinAppEx
{
public:
	CToolOfSelectedFilePackingApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CToolOfSelectedFilePackingApp theApp;