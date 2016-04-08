#pragma once
#include "afxwin.h"


// Chelpinfo 对话框

class Chelpinfo : public CDialog
{
	DECLARE_DYNAMIC(Chelpinfo)

public:
	Chelpinfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Chelpinfo();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_helpinfo;
	afx_msg void OnBnClickedOk();
};
