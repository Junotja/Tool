#pragma once
#include "afxwin.h"


// Chelpinfo �Ի���

class Chelpinfo : public CDialog
{
	DECLARE_DYNAMIC(Chelpinfo)

public:
	Chelpinfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Chelpinfo();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_helpinfo;
	afx_msg void OnBnClickedOk();
};
