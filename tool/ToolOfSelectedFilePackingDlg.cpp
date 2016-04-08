
// ToolOfSelectedFilePackingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ToolOfSelectedFilePacking.h"
#include "ToolOfSelectedFilePackingDlg.h"


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
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

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CToolOfSelectedFilePackingDlg �Ի���




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


// CToolOfSelectedFilePackingDlg ��Ϣ�������

BOOL CToolOfSelectedFilePackingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect rect_Pack; 
	CRect rect_Old; 
	m_PackList.GetClientRect(&rect_Pack);
	m_OldList.GetClientRect(&rect_Old);
	m_PackList.InsertColumn(0,_T("�����ļ�����"),LVCFMT_LEFT,rect_Pack.Width()*0.8);
	m_PackList.InsertColumn(1,_T("MD5ֵ"),LVCFMT_LEFT,rect_Pack.Width()*0.2);
	m_OldList.InsertColumn(0,_T("�ԱȽ��"),LVCFMT_LEFT,rect_Old.Width());
	m_PackList.SetExtendedStyle(m_PackList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP );  
	m_OldList.SetExtendedStyle(m_OldList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_CHECKBOXES | LVS_EX_INFOTIP); 
	CFont m_Font;
	m_Font.CreatePointFont(60,"����");
	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font);
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CToolOfSelectedFilePackingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	if (!m_bisCalc)
	{
		calcMd5.ChangePathFromRelativeToAbsolute("./");
		calcMd5.GetAbsolutePath(AbsulutePath);
	}
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_NORMAL);
	CFont m_Font;
	m_Font.CreatePointFont(180,"����");
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
			MessageBox(_T("�������!����Ա����ȵ��룡"));
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
					FileName.Format("(���������ļ�)%s",calc_profile_vector[i].directory.c_str());
					m_OldList.InsertItem(i,FileName);
				}
				for (unsigned int i = calc_profile_vector.size(); 
					i < calc_profile_vector.size() + calc_private_vector.size();i ++)
				{
					CString FileName;
					FileName.Format("(����������ͬ)%s",calc_private_vector[i-calc_profile_vector.size()].directory.c_str());
					m_OldList.InsertItem(i,FileName);
					m_OldList.SetCheck(i,TRUE);
				}
				for (unsigned int i = calc_profile_vector.size() + calc_private_vector.size();
					i < calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size();i ++)
				{
					CString FileName;
					FileName.Format("(���ض���)%s",calc_public_vector[i-(calc_profile_vector.size() + calc_private_vector.size())].directory.c_str());
					m_OldList.InsertItem(i,FileName);
					m_OldList.SetCheck(i,TRUE);
				}
				for (unsigned int i = calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size();
					i < calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size() + input_profile_vector.size();i ++)
				{
					CString FileName;
					FileName.Format("(�ֳ������ļ�)%s",input_profile_vector[i-(calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size())].directory.c_str());
					m_OldList.InsertItem(i,FileName);
				}
				for (unsigned int i = calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size() + input_profile_vector.size();
					i < calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size() + input_profile_vector.size() + input_vector.size();i ++)
				{
					CString FileName;
					FileName.Format("(�ֳ�����)%s",input_vector[i - (calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size() + input_profile_vector.size())].directory.c_str());
					m_OldList.InsertItem(i,FileName);
				}
				CString total_file;
				total_file.Format("%d",calc_profile_vector.size() + calc_private_vector.size() + calc_public_vector.size() + input_profile_vector.size() + input_vector.size());
				m_OldListTotal = total_file;
				UpdateData(FALSE);
				GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
				if (m_OldList.GetItemCount() == 0)
				{
					MessageBox("�ļ���ͬ��");
					GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
					m_bisCalc =TRUE;
					m_bIsLoadXmlFile = FALSE;
					break;
				}
				MessageBox(_T("�Ա���ɣ�"));
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CalcMD5 loadXMLInfo;
	CFileDialog m_dlg(TRUE,NULL,NULL,OFN_OVERWRITEPROMPT,_T("XMLFile|*.xml|*.XML|"));
	if (m_dlg.DoModal() == IDOK)
	{
		CString a = m_dlg.GetPathName();
		char *temp = a.GetBuffer(0);
		a.ReleaseBuffer();
		GetDlgItem(IDC_STATIC1)->ShowWindow(SW_NORMAL);
		CFont m_Font;
		m_Font.CreatePointFont(180,"����");
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
			MessageBox("����ɹ���");
			m_bIsLoadXmlFile = TRUE;
		}
		
	}
}

void CToolOfSelectedFilePackingDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CalcMD5 packing;
	int     calc_getchecked = 0;
	MergeVector();
	if (0 == all_pack_vector.size())
	{
		MessageBox(_T("δ���жԱȻ��޲�ͬ�ļ���������"));
		return;
	}
	GetDlgItem(IDC_STATIC1)->ShowWindow(SW_NORMAL);
	CFont m_Font;
	m_Font.CreatePointFont(180,"����");
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
			MessageBox("����ѡ������һ���ļ���");
			return;
		}
		if (packing.CompressFile(all_pack_vector))
		{
			if (failure_vector.size() == 0)
			{
				GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
				MessageBox(_T("����ɹ���"));
				return;
			}
			m_OldList.DeleteAllItems();
			for (unsigned int i = 0; i < failure_vector.size(); i++)
			{
				CString FileName;
				FileName.Format("(���ʧ�ܿ��ܱ�ռ�ã�)%s",failure_vector[i].c_str());
				m_OldList.InsertItem(i,FileName);
				m_OldList.SetCheck(i,TRUE);
				
			}
			//MessageBox(_T("���ʧ�ܣ���ȷ���ļ�û�б��򿪻�ʹ�ã�"));
			GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
				MessageBox(_T("�����ļ�����ɹ�!"));
			return;
		}
		
	}
	
}

void CToolOfSelectedFilePackingDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	delete []AbsulutePath;
	OnCancel();
}

void CToolOfSelectedFilePackingDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Chelpinfo m_HelpDlg;
	m_HelpDlg.DoModal();
}
