// helpinfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ToolOfSelectedFilePacking.h"
#include "helpinfo.h"


// Chelpinfo 对话框

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


// Chelpinfo 消息处理程序

BOOL Chelpinfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_helpinfo.SetWindowText("\"对比结果\"前缀解释：\r\n\r\n本地配置文件:筛选本地文件中后缀名为“ini”，“xml”的文件。(可能需要人工选择)\r\n\r\n本地重名不同:与导入XML对比之后本地文件存在但与现场不同的文件。(需要打包)\r\n\r\n本地独有:与导入XML比较后只存在于本地的即可能为新增文件。(需要打包)\r\n\r\n现场配置文件:筛选导入XML中的后缀名为“ini”，“xml”的文件。(可能需要人工选择)\r\n\r\n现场独有:导入XML对比之后只存在于生成XML的现场文件中即可能现场版本较新。(需要人工确定)");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void Chelpinfo::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
