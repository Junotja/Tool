/**   @file CalcMD5.h

 *    @note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.

 *    @brief 计算文件对比及打包主功能函数

 *    @author         shenyang7

 *    @date           2016/01/25

 *    @note 程序会生成名为“标识码.xml”及“打包文件.zip”两个文件


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

#ifdef _DEBUG/**< 打印debug信息 */
#define DEBUGInfo(Message) file_log<<"File: "<<__FILE__<<"Line: "<<__LINE__<<": "<<Message<<endl
#else
#define ERROR(Message) file_log<<"error:"<<Message<<std::endl
#endif 

#ifdef _DEBUG/**< 打印内存申请信息 */
#define new   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

extern std::fstream file_log;

/** @array File_Suffix[CalcMD5.h]

*   @brief 筛选列表，此列表内的后缀名不被对比直接显示。

*/
const string File_Suffix[] = {
	"xml","ini"
};

/** @Template LengthofArray[CalcMD5.h]

*   @brief 用于计算数组成员个数。

*/

template<class T,size_t N>  
unsigned int LengthofArray(T (&array)[N]){  
	return sizeof(array) / sizeof(T);  
}

/** @struct all_file_info[CalcMD5.h]

*   @brief 存储文件路径及MD5值。

*/
struct all_file_info
{
	string MD5Value;
	string directory;
};

/** @class Object[CalcMD5.h]

*   @brief 派生基类。

*/
class Object
{
public:
	virtual ~Object();
};

/**   @class TraversalFile [CalcMD5.h]

 *    @brief 生成XML，打包类。

 *

 * 主要包括了遍历文件夹、读取二进制流、操作XML、打包文件等功能。

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

 *    @brief 计算MD5继承自TraversalFile。

 *	  主要包括计算MD5值、对比MD5值等功能。

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
