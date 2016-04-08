/**   @file CalcMD5.h

 *    @note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.

 *    @brief �����ļ��Աȼ���������ܺ���

 *    @author         shenyang7

 *    @date           2016/01/25

 *    @note �����������Ϊ����ʶ��.xml����������ļ�.zip�������ļ�


 */
#ifndef TRAVERSAL_FILE_H
#define TRAVERSAL_FILE_H
#include "direct.h"
#include "io.h"
#include "string.h"
#include "md5.h"
#include <vector>
#include "tinyxml.h"
#include "zip.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG/**< ��ӡdebug��Ϣ */
#define DEBUGInfo(Message) file_log<<"File: "<<__FILE__<<"Line: "<<__LINE__<<": "<<Message<<endl
#else
#define ERROR(Message) file_log<<"error:"<<Message<<std::endl
#endif 

#ifdef _DEBUG/**< ��ӡ�ڴ�������Ϣ */
#define new   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

extern std::fstream file_log;

/** @array File_Suffix[CalcMD5.h]

*   @brief ɸѡ�б����б��ڵĺ�׺�������Ա�ֱ����ʾ��

*/
const string File_Suffix[] = {
	"xml","ini"
};

/** @Template LengthofArray[CalcMD5.h]

*   @brief ���ڼ��������Ա������

*/

template<class T,size_t N>  
unsigned int LengthofArray(T (&array)[N]){  
	return sizeof(array) / sizeof(T);  
}

/** @struct all_file_info[CalcMD5.h]

*   @brief �洢�ļ�·����MD5ֵ��

*/
struct all_file_info
{
	string MD5Value;
	string directory;
};

/** @class Object[CalcMD5.h]

*   @brief �������ࡣ

*/
class Object
{
public:
	virtual ~Object();
};

/**   @class TraversalFile [CalcMD5.h]

 *    @brief ����XML������ࡣ

 *

 * ��Ҫ�����˱����ļ��С���ȡ��������������XML������ļ��ȹ��ܡ�

 */
class TraversalFile:public Object
{
public:
	TraversalFile();
	

public:
	vector<all_file_info> StartTraversal(const char *path,const char *file_type_distinguish = "*.*");
	bool                  Run();
	void 			      ChangeWorkingDirectory(void);
	bool 			      ChangeWorkingDirectory(const char *file_type_distinguish);
	bool 			      ChangePathFromRelativeToAbsolute(const char *Path);
	bool                   LoadXML(const char *Path);
	bool                  PrintXML(vector<all_file_info> &fileInfoAndMD5);
	string                SubFileNameFromBack(string &m_directory);
	string                SubDiskNameFromPath(string &m_directory);
	bool                  SubFileSuffix(string &m_directory);
	bool                  CompressFile(vector<all_file_info> &file_compress,const char* password = NULL);

public:
	bool                  GetAbsolutePath(char *AbsolutePath);
protected:
	virtual bool          PrintMD5(const char *Path,const char *file_name,string &temp);

protected:
	char                         m_cRootDirectory[_MAX_PATH];
	char                         m_cNodeDirectory[_MAX_PATH];
public:
	static vector<all_file_info> compare_file_value_vector_input;
	static vector<all_file_info> compare_file_value_vector_input_profile;
	static vector<all_file_info> compare_file_value_vector_calc_private;
	static vector<all_file_info> compare_file_value_vector_calc_public;
	static vector<all_file_info> compare_file_value_vector_calc_profile;
	static vector<string>         file_add_failure;
};

/**   @class CalcMD5 [CalcMD5.h]

 *    @brief ����MD5�̳���TraversalFile��

 *	  ��Ҫ��������MD5ֵ���Ա�MD5ֵ�ȹ��ܡ�

 */
class CalcMD5:public TraversalFile
{
public:
	CalcMD5();
public:
	//bool PrintMD5(const char *Path,string &temp);
	bool                   PrintMD5(const char *Path,const char *file_name,string &temp);
	
	void                   CompareTwoListByMD5(vector<all_file_info>& compare_input,
											   vector<all_file_info>& compare_calc);
	void                   CompareTwoListByName(vector<all_file_info>& compare_input,
											    vector<all_file_info>& compare_calc);
	void                   DeleteBuildFile(vector<all_file_info>& compare_calc,
											vector<all_file_info>& out_profile);
};

#endif
