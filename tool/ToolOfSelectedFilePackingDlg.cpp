
// ToolOfSelectedFilePackingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ToolOfSelectedFilePacking.h"
#include "ToolOfSelectedFilePackingDlg.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
char *CToolOfSelectedFilePackingDlg::AbsulutePath = new char[_MAX_PATH];
CalcMD5 calcMd5;
#define calc_public_vector  CalcMD5::compare_file_value_vector_calc_public
#define calc_private_vector  CalcMD5::compare_file_value_vector_calc_private
#define calc_profile_vector  CalcMD5::compare_file_value_vector_calc_profile
#define input_vector         CalcMD5::compare_file_value_vector_input 
#define input_profile_vector CalcMD5::compare_file_value_vector_input_profile
#define failure_vector CalcMD5::file_add_failure
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CToolOfSelectedFilePackingDlg 对话框




CToolOfSelectedFilePackingDlg::CToolOfSelectedFilePackingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolOfSelectedFilePackingDlg::IDD, pParent),m_bIsLoadXmlFile(FALSE),m_bisCalc(FALSE)
	, m_nTotal(_T(""))
	, m_OldListTotal(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CToolOfSelectedFilePackingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PACKLIST, m_PackList);
	DDX_Text(pDX, IDC_EDIT1, m_nTotal);
	DDX_Control(pDX, IDC_LIST_OLDLIST, m_OldList);
	DDX_Text(pDX, IDC_EDIT2, m_OldListTotal);
}

BEGIN_MESSAGE_MAP(CToolOfSelectedFilePackingDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CToolOfSelectedFilePackingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CToolOfSelectedFilePackingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CToolOfSelectedFilePackingDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &CToolOfSelectedFilePackingDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &CToolOfSelectedFilePackingDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CToolOfSelectedFilePackingDlg 消息处理程序

BOOL CToolOfSelectedFilePackingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect rect_Pack; 
	CRect rect_Old; 
	m_PackList.GetClientRect(&rect_Pack);
	m_OldList.GetClientRect(&rect_Old);
	m_PackList.InsertColumn(0,_T("本地文件名称"),LVCFMT_LEFT,rect_Pack.Width()*0.8);
	m_PackList.InsertColumn(1,_T("MD5值"),LVCFMT_LEFT,rect_Pack.Width()*0.2);
	m_OldList.InsertColumn(0,_T("对比结果"),LVCFMT_LEFT,rect_Old.Width());
	m_PackList.SetExtendedStyle(m_PackList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP );  
	m_OldList.SetExtendedStyle(m_OldList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_CHECKBOXES | LVS_EX_INFOTIP); 
	CFont m_Font;
	m_Font.CreatePointFont(60,"楷书");
	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font);
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CToolOfSelectedFilePackingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CToolOfSelectedFilePackingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CToolOfSelectedFilePackingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CToolOfSelectedFilePackingDlg::MergeVector()
{
	all_pack_vector.clear();
	all_pack_vector.insert(all_pack_vector.end(),calc_profile_vector.begin(),calc_profile_vector.end());
	all_pack_vector.insert(all_pack_vector.end(),calc_private_vector.begin(),calc_private_vector.end());
	all_pack_vector.insert(all_pack_vector.end(),calc_public_vector.begin(),calc_public_vector.end());
	all_pack_vector.insert(all_pack_vector.end(),input_profile_vector.begin(),input_profile_vector.end());
	all_pack_vector.insert(all_pack_vector.end(),input_vector.begin(),input_vector.end());

}

void CToolOfSelectedFilePackingDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (!m_bisCalc)
	{
		calcMd5.ChangePathFromRelativeToAbsolute("./");
		calcMd5.GetAbsolutePath(AbsulutePath);
	}
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_NORMAL);
	CFont m_Font;
	m_Font.CreatePointFont(180,"楷书");
	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font);
	if (calcMd5.Run())
	{
		switch(m_bIsLoadXmlFile)
		{
		case FALSE:
			m_PackList.DeleteAllItems();
			for (unsigned int i = 0; i < calc_public_vector.size(); i++)
			{
				CString FileName,FileMD5;
				FileName.Format("%s",calc_public_vector[i].directory.c_str());
				FileMD5.Format("%s",calc_public_vector[i].MD5Value.c_str());
				m_PackList.InsertItem(i,FileName);
				m_PackList.SetItemText(i,1,FileMD5);
				CString total_file;
				total_file.Format("%d",calc_public_vector.size());
				m_nTotal = total_file;
				UpdateData(FALSE);
				//m_PackList.SetCheck(i,TRUE);+
			}
			GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
			MessageBox(_T("计算完成!如需对比请先导入！"));
			m_bisCalc =TRUE;
			break;
		case TRUE:
			{
 				//m_PackList.DeleteAllItems();
				m_OldList.DeleteAllItems();
				calcMd5.CompareTwoListByMD5(input_vector,calc_public_vector);
				for (unsigned int i = 0; i < calc_profile_vector.size(); i++)
				{
					CString FileName;
					FileName.Format("(本地配置文件)%s",calc_profile_vector[i].directory.c_str());
					m_OldList.InsertItem(i,FileName);
				}
				for (unsigned int i = calc_profile_vector.size(); 
					i < calc_profile_vector.size() + calc_private_vector.size();i ++)
				{
					CString FileName;
					FileName.Format("(本地重名不同)%s",calc_private_vector[i-calc_profile_vector.size()].directory.c_str());
					m_OldList.InsertItem(i,FileName);
					m_OldList.SetCheck(i,TRUE);
				}
				for (unsigned int i = calc_profile_vector.size() + calc_private_vector.size();
					i < calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size();i ++)
				{
					CString FileName;
					FileName.Format("(本地独有)%s",calc_public_vector[i-(calc_profile_vector.size() + calc_private_vector.size())].directory.c_str());
					m_OldList.InsertItem(i,FileName);
					m_OldList.SetCheck(i,TRUE);
				}
				for (unsigned int i = calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size();
					i < calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size() + input_profile_vector.size();i ++)
				{
					CString FileName;
					FileName.Format("(现场配置文件)%s",input_profile_vector[i-(calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size())].directory.c_str());
					m_OldList.InsertItem(i,FileName);
				}
				for (unsigned int i = calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size() + input_profile_vector.size();
					i < calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size() + input_profile_vector.size() + input_vector.size();i ++)
				{
					CString FileName;
					FileName.Format("(现场独有)%s",input_vector[i - (calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size() + input_profile_vector.size())].directory.c_str());
					m_OldList.InsertItem(i,FileName);
				}
				CString total_file;
				total_file.Format("%d",calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size() + input_profile_vector.size() + input_vector.size());
				m_OldListTotal = total_file;
				UpdateData(FALSE);
				GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
				if (m_OldList.GetItemCount() == 0)
				{
					MessageBox("文件相同！");
					GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
					m_bisCalc =TRUE;
					m_bIsLoadXmlFile = FALSE;
					break;
				}
				MessageBox(_T("对比完成！"));
				GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
				m_bisCalc =TRUE;
				m_bIsLoadXmlFile = FALSE;
			}
			break;
		}

	}

	//OnOK();
}

void CToolOfSelectedFilePackingDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CalcMD5 loadXMLInfo;
	CFileDialog m_dlg(TRUE,NULL,NULL,OFN_OVERWRITEPROMPT,_T("XMLFile|*.xml|*.XML|"));
	if (m_dlg.DoModal() == IDOK)
	{
		CString a = m_dlg.GetPathName();
		char *temp = a.GetBuffer(0);
		a.ReleaseBuffer();
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_NORMAL);
		CFont m_Font;
		m_Font.CreatePointFont(180,"楷书");
		GetDlgItem(IDC_STATIC1)->SetFont(&m_Font);
		if (loadXMLInfo.LoadXML(temp))
		{
			m_PackList.DeleteAllItems();
			for (unsigned int i = 0; i < input_vector.size(); i++)
			{
				CString FileName,FileMD5;
				FileName.Format("%s",input_vector[i].directory.c_str());
				FileMD5.Format("%s",input_vector[i].MD5Value.c_str());
				m_PackList.InsertItem(i,FileName);
				m_PackList.SetItemText(i,1,FileMD5);
			}
			CString total_file;
			total_file.Format("%d",input_vector.size());
			m_nTotal = total_file;
			UpdateData(FALSE);
			GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
			MessageBox("导入成功！");
			m_bIsLoadXmlFile = TRUE;
		}
		
	}
}

void CToolOfSelectedFilePackingDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CalcMD5 packing;
	int     calc_getchecked = 0;
	MergeVector();
	if (0 == all_pack_vector.size())
	{
		MessageBox(_T("未进行对比或无不同文件无需打包！"));
		return;
	}
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_NORMAL);
	CFont m_Font;
	m_Font.CreatePointFont(180,"楷书");
	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font);
	if (packing.ChangePathFromRelativeToAbsolute(AbsulutePath))
	{
		for (int i = 0; i < m_OldList.GetItemCount();i++)
		{
			//m_OldList.GetCheck(i) != 0 ? calc_getchecked++:all_pack_vector[i].directory = "";
			if(!m_OldList.GetCheck(i))
			{ 
				all_pack_vector[i].directory = "";
			} 
			else
			{
				calc_getchecked++;
			}
		}
		if (calc_getchecked == 0)
		{
			GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
			MessageBox("请先选中至少一个文件！");
			return;
		}
		if (packing.CompressFile(all_pack_vector))
		{
			if (failure_vector.size() == 0)
			{
				GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
				MessageBox(_T("打包成功！"));
				return;
			}
			m_OldList.DeleteAllItems();
			for (unsigned int i = 0; i < failure_vector.size(); i++)
			{
				CString FileName;
				FileName.Format("(打包失败可能被占用！)%s",failure_vector[i].c_str());
				m_OldList.InsertItem(i,FileName);
				m_OldList.SetCheck(i,TRUE);
				
			}
			//MessageBox(_T("打包失败！请确认文件没有被打开或使用！"));
			GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
				MessageBox(_T("其他文件打包成功!"));
			return;
		}
		
	}
	
}

void CToolOfSelectedFilePackingDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	delete []AbsulutePath;
	OnCancel();
}

void CToolOfSelectedFilePackingDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	Chelpinfo m_HelpDlg;
	m_HelpDlg.DoModal();
}
