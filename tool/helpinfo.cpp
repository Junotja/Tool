// helpinfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ToolOfSelectedFilePacking.h"
#include "helpinfo.h"


// Chelpinfo �Ի���

IMPLEMENT_DYNAMIC(Chelpinfo, CDialog)

Chelpinfo::Chelpinfo(CWnd* pParent /*=NULL*/)
	: CDialog(Chelpinfo::IDD, pParent)
{

}

Chelpinfo::~Chelpinfo()
{
}

void Chelpinfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_helpinfo);
}


BEGIN_MESSAGE_MAP(Chelpinfo, CDialog)
	ON_BN_CLICKED(IDOK, &Chelpinfo::OnBnClickedOk)
END_MESSAGE_MAP()


// Chelpinfo ��Ϣ�������

BOOL Chelpinfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_helpinfo.SetWindowText("\"�ԱȽ��\"ǰ׺���ͣ�\r\n\r\n���������ļ�:ɸѡ�����ļ��к�׺��Ϊ��ini������xml�����ļ���(������Ҫ�˹�ѡ��)\r\n\r\n����������ͬ:�뵼��XML�Ա�֮�󱾵��ļ����ڵ����ֳ���ͬ���ļ���(��Ҫ���)\r\n\r\n���ض���:�뵼��XML�ȽϺ�ֻ�����ڱ��صļ�����Ϊ�����ļ���(��Ҫ���)\r\n\r\n�ֳ������ļ�:ɸѡ����XML�еĺ�׺��Ϊ��ini������xml�����ļ���(������Ҫ�˹�ѡ��)\r\n\r\n�ֳ�����:����XML�Ա�֮��ֻ����������XML���ֳ��ļ��м������ֳ��汾���¡�(��Ҫ�˹�ȷ��)");
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void Chelpinfo::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}
