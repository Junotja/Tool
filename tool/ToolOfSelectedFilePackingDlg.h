
// ToolOfSelectedFilePackingDlg.h : 头文件
//

#pragma once
#include "CalcMD5.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "helpinfo.h"
//#include "ResizableDialog.h"
// CToolOfSelectedFilePackingDlg 对话框
class CToolOfSelectedFilePackingDlg : public CDialog
{
// 构造
public:
	CToolOfSelectedFilePackingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TOOLOFSELECTEDFILEPACKING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
