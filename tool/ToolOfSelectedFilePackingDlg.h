
// ToolOfSelectedFilePackingDlg.h : ͷ�ļ�
//

#pragma once
#include "CalcMD5.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "helpinfo.h"
//#include "ResizableDialog.h"
// CToolOfSelectedFilePackingDlg �Ի���
class CToolOfSelectedFilePackingDlg : public CDialog
{
// ����
public:
	CToolOfSelectedFilePackingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TOOLOFSELECTEDFILEPACKING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	CListCtrl m_PackList;
	BOOL        m_bIsLoadXmlFile;
	CString m_nTotal;
	afx_msg void OnBnClickedButton2();
	static char *AbsulutePath;
	afx_msg void OnBnClickedCancel();
	BOOL        m_bisCalc;
	CListCtrl m_OldList;
	CString m_OldListTotal;
	vector<all_file_info> all_pack_vector; 
public:
	void MergeVector();
	afx_msg void OnBnClickedButton3();
};
