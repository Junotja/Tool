#include "CalcMD5.h"
std::fstream file_log;
vector<all_file_info> TraversalFile::compare_file_value_vector_calc_public;//���ض��в�ͬ
vector<all_file_info> TraversalFile::compare_file_value_vector_calc_private;//�Ա�������ͬ
vector<all_file_info> TraversalFile::compare_file_value_vector_input;//Զ�̶��в�ͬ
vector<all_file_info> TraversalFile::compare_file_value_vector_input_profile;//Զ�������ļ�
vector<all_file_info> TraversalFile::compare_file_value_vector_calc_profile;//���������ļ�
vector<string>        TraversalFile::file_add_failure;//������ʧ��

/**   @fn       ~Object()

 *    @brief    <��������������>

 */
Object::~Object()
{

}

/**   @fn       TraversalFile()

 *    @brief    <���캯������ȡ�ļ���ַ>

 */
TraversalFile::TraversalFile()
{
	_getcwd(m_cRootDirectory,_MAX_PATH);
}

/**   @fn       Run()

 *    @brief    <��������ڣ��������ʾ���>

 */
bool TraversalFile::Run()
{
	compare_file_value_vector_calc_public.clear();
	compare_file_value_vector_calc_public = StartTraversal(m_cRootDirectory);
	PrintXML(compare_file_value_vector_calc_public);
	return true;
}

/**   @fn vector<all_file_info> StartTraversal(const char *path,const char *file_type_distinguish)

 *    @brief                                   <�ļ���������>

 *    @param const char *path                  ��Ҫ�������ļ�·��[in].

 *    @param const char *file_type_distinguish �ļ�ɸѡƥ���[in].

 *    @return                                  �����ļ��б�

 */
vector<all_file_info> TraversalFile::StartTraversal(const char *path,const char *file_type_distinguish)
{
	intptr_t hfind_file;
	_finddata_t file_info;
	vector<all_file_info> file_value_vector;
	file_value_vector.clear();
	all_file_info file_value;
	ChangeWorkingDirectory(path);
	if ((hfind_file = _findfirst(file_type_distinguish,&file_info)) != -1)//�ɹ�����һ����������򷵻�-1
	{
		do  
		{  
			if (!(file_info.attrib & _A_SUBDIR))  
			{  
				char filename[_MAX_PATH];  
				strcpy(filename,path);  
				strcat(filename,file_info.name);  
				file_value.directory = filename;
				//PrintMD5(filename,file_value.MD5Value);
				PrintMD5(path,file_info.name,file_value.MD5Value);
				file_value_vector.push_back(file_value);
			}  
		} while (_findnext(hfind_file,&file_info) == 0);  
		_findclose(hfind_file);
		//DEBUGInfo("�����ļ���");
	}

	ChangeWorkingDirectory(path);
	if ((hfind_file=_findfirst("*.*",&file_info)) != -1)  
	{  
		do  
		{  
			if ((file_info.attrib & _A_SUBDIR))  //�Ƿ�Ϊ�ļ���
			{  
				if (strcmp(file_info.name,".") != 0 && strcmp  
					(file_info.name,"..") != 0)  //�ļ����л���name=��.���͡�..��
				{  
					char subdir[_MAX_PATH];  
					strcpy(subdir,path);  
					strcat(subdir,file_info.name);  
					strcat(subdir,"\\");  
					//OperateDir(subdir,path);  
					vector<all_file_info>tmp=StartTraversal(subdir,file_type_distinguish);
					for (vector<all_file_info>::iterator it=tmp.begin();it<tmp.end();it++)  
					{  
						file_value_vector.push_back(*it);  
					}  
				}  
			}  
		} while (_findnext(hfind_file,&file_info) == 0);  
		_findclose(hfind_file);  
	}
	return file_value_vector;
}

/**   @fn void ChangeWorkingDirectory()

 *    @brief                                   <Ŀ¼�л�����>

 */
void TraversalFile::ChangeWorkingDirectory()
{
	_chdir(m_cRootDirectory);
}

/**   @fn bool ChangeWorkingDirectory(const char *path)

 *    @brief                  <Ŀ¼�л�����>

 *    @param const char *path ��Ҫ�л�����·��[in].

 *    @return  bool

 */
bool TraversalFile::ChangeWorkingDirectory(const char *path)
{
	if (_chdir(path) != NULL)
	{
		//DEBUGInfo("����Ŀ¼Ϊ�գ�");
		return false;
	}
	return true;
}

/**   @fn bool ChangePathFromRelativeToAbsolute(const char *Path)

 *    @brief                  <���·���л�Ϊ����·��>

 *    @param const char *path ��Ҫ�л���·��[in].

 *    @return  bool

 */
bool TraversalFile::ChangePathFromRelativeToAbsolute(const char *Path)
{
	if (_fullpath(m_cRootDirectory,Path,_MAX_PATH) == NULL)
	{
		//DEBUGInfo("ת��Ϊ����·��ʧ�ܣ�");
		return false;
	}
	int len=strlen(m_cRootDirectory);  
	if (m_cRootDirectory[len-1] != '\\')  
		strcat(m_cRootDirectory,"\\");  
	return true;
}

/**   @fn bool PrintXML(vector<all_file_info> &fileInfoAndMD5)

 *    @brief                                       <��ӡ�ļ���Ϣ�������ļ�����·����MD5ֵ>

 *    @param vector<all_file_info> &fileInfoAndMD5 ��Ҫ��ӡ���ļ���Ϣ�б�[in].

 *    @return  bool

 */
bool TraversalFile::PrintXML(vector<all_file_info> &fileInfoAndMD5)
{
	TiXmlDeclaration *declaration = new TiXmlDeclaration("1.0","UTF-8","yes");
	TiXmlDocument    *document    = new TiXmlDocument();
	document->LinkEndChild(declaration);
	TiXmlElement     *element     = new TiXmlElement("document");
	document->LinkEndChild(element);
	TiXmlComment     *comment     = new TiXmlComment("this is a test about how to write XML!");
	element->LinkEndChild(comment);
	for (unsigned int i = 0;i < fileInfoAndMD5.size();i++)
	{
		TiXmlElement     *file_name   = new TiXmlElement("file");
		file_name->SetAttribute("number",i+1);
		file_name->SetAttribute("filename",fileInfoAndMD5[i].directory.c_str());
		file_name->SetAttribute("MD5",fileInfoAndMD5[i].MD5Value.c_str());
		element->LinkEndChild(file_name);
	}
	ChangeWorkingDirectory((fileInfoAndMD5[0].directory.c_str()));
	char *out_path = new char[_MAX_PATH];
	strcpy(out_path,m_cRootDirectory);
	strcat(out_path,"��ʶ��.xml");
	document->SaveFile(out_path);
	delete[] out_path;
	delete	document;
	return true;
}

/**   @fn bool PrintMD5(const char *Path,const char *file_name,string &temp)

 *    @brief                       <��Ҫ������д��MD5���㺯��>

 *    @param const char *Path      ��Ҫ������ļ�·����Ϣ[in].

 *    @param const char *file_name ��Ҫ������ļ�������Ϣ[in].

 *    @param const char *Path      ������ɵ�MD5ֵ[out].

 *    @return  bool

 */
bool TraversalFile::PrintMD5(const char *Path,const char *file_name,string &temp)
{
	return true;
}

/**   @fn bool CompressFile(vector<all_file_info> &file_compress,const char* password)

 *    @brief                                       <���ѹ������>

 *    @param vector<all_file_info> &file_compress  ��Ҫѹ�����ļ��б�[in].

 *    @param const char* password                  ��Ҫ����ѹ���ļ��ļ�������[in]����ѡ��.

 *    @return  bool

 */
bool TraversalFile::CompressFile(vector<all_file_info> &file_compress,const char* password /* = NULL */)
{
	if (file_compress.size() == 0)
	{
		return false;
	}
	HZIP    hzip_out;
	char *out_path = new char[_MAX_PATH];
	strcpy(out_path,m_cRootDirectory);
	strcat(out_path,_T("����ļ�.zip"));
	hzip_out = password == NULL ? CreateZip(out_path,0):CreateZip(out_path,0,password);
	if (hzip_out == 0)
	{
		delete []out_path;
		CloseZip(hzip_out);
		return false;	
	}
	for (vector<all_file_info>::iterator it = file_compress.begin();it < file_compress.end();it ++)
	{
		string file_name = SubDiskNameFromPath((*it).directory);
		if ((*it).directory.compare("") == 0)
		{
			continue;
		}
		if (ZipAdd(hzip_out,file_name.c_str(),(*it).directory.c_str()) != ZR_OK)
		{
			file_add_failure.push_back((*it).directory);
			/*delete []out_path;
			CloseZip(hzip_out);
			return false;	*/
		}
	}
	delete []out_path;
	CloseZip(hzip_out);
	return true;
}

/**   @fn bool GetAbsolutePath(char *AbsolutePath)

 *    @brief                    <�������ȡ��·�����>

 *    @param char *AbsolutePath ��Ҫ��õ���·��[out].

 *    @return  bool

 */
bool TraversalFile::GetAbsolutePath(char *AbsolutePath)
{
	strcpy(AbsolutePath,m_cRootDirectory);
	if ( NULL != AbsolutePath)
	{
		return true;
	}
	return false;
}

/**   @fn SubFileSuffix(string &m_directory)

 *    @brief                     <��ȡ�ļ���׺��>

 *    @param string &m_directory ��Ҫ��ȡ���ļ�����·��.

 *    @return  bool

 */
bool TraversalFile::SubFileSuffix(string &m_directory)
{
	string temp = m_directory; 
	int nPos = temp.rfind(".");
	if (-1 != nPos)
	{
		temp = temp.substr(nPos + 1, temp.length() - nPos - 1);
		for (int i = 0; i < LengthofArray(File_Suffix); i ++)
		{
			if (temp.compare(File_Suffix[i]) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

/**   @fn CalcMD5()

 *    @brief    <����MD5��Ŀչ��캯��>

 */
CalcMD5::CalcMD5()
{

}

/**   @fn PrintMD5(const char *Path,const char *file_name,string &temp)

 *    @brief                       <��д�˻���ĺ�������Ҫ���������ļ�MD5ֵ>

 *    @param const char *Path      ��Ҫ������ļ�·����Ϣ[in].

 *    @param const char *file_name ��Ҫ������ļ�������Ϣ[in].

 *    @param string &temp          ���������MD5ֵ���[out].

 *    @return  bool

 */
bool CalcMD5::PrintMD5(const char *Path,const char *file_name,string &temp)
{
	MD5_CTX testMD5;
	if(ChangeWorkingDirectory(Path))
	{
		//string MD5_value;
		int len = 0;
		unsigned char buffer[1024] = {0};
		unsigned char digest[16]   = {0};
		FILE *pFile;
		pFile = fopen(file_name,"rb");
		if (NULL == pFile)
		{
			temp = "";
			//fclose(pFile);
			return false;
		}
		MD5_Init(&testMD5);
		while((len = fread(buffer,1,1024,pFile)) > 0)
		{
			MD5_Update(&testMD5,buffer,len);
		}

		MD5_Final(digest,&testMD5);
		char buf[33] = {0};  
		char tmp[3] = {0};  
		for(int i = 0; i < 16; i++ )  
		{  
			sprintf(tmp,"%02X", digest[i]);
			strcat(buf, tmp);  
		} 
		temp = buf;
		fclose(pFile);
		//ChangeWorkingDirectory()
		return true;
	}
	return false;
}

/**   @fn bool LoadXML(const char *Path)

 *    @brief                  <�Ա�MD5ֵ�ȵ����ֳ����ɵ�XML�ļ����˴��������������XML�ļ�>

 *    @param const char *Path �����ļ�·��.

 *    @return  bool

 */
bool TraversalFile::LoadXML(const char *Path)
{
	TiXmlDocument *doc = new TiXmlDocument(Path);
	if (!doc->LoadFile())
	{
		return false;
	}
	TiXmlElement  *root_node = doc->RootElement();
	//SaveToMemory(root_node);
	TiXmlNode* child; 
	TiXmlElement* element = NULL;
	TiXmlAttribute *attr = NULL;
	child = root_node->FirstChildElement();
	compare_file_value_vector_input.clear();
	int ct;
	while(child)
	{
		ct = child->Type();
		switch(ct)
		{
		case TiXmlNode::TINYXML_TEXT:
			child = child->NextSiblingElement();
			break;
		case TiXmlNode::TINYXML_ELEMENT:
			{
				element = child->ToElement();
				attr = element->FirstAttribute()->Next();
				all_file_info compare_file_info;
				compare_file_info.directory = attr->Value();
				//cout << attr->NameTStr() << "=" << attr->ValueStr() << '\t';
				compare_file_info.MD5Value = attr->Next()->Value();
				compare_file_value_vector_input.push_back(compare_file_info);
				child = child->NextSiblingElement();
				break;
			}
			
		default:
			child = child->NextSiblingElement();
			break;
		}
	}
	delete doc;
	return true;
}

/**   @fn string SubFileNameFromBack(string &m_directory)

 *    @brief                     <���ļ���������·����ȡ�ļ�����>

 *    @param string &m_directory �����ļ���������·��.

 *    @return  string            ����ļ�����

 */
string TraversalFile::SubFileNameFromBack(string &m_directory)
{
	string temp = m_directory; 
	int nPos = temp.rfind("\\");
	if (-1 != nPos)
	{
		temp = temp.substr(nPos + 1, temp.length() - nPos - 1);
		if (0 == nPos)
		{
			SubFileNameFromBack(temp);
		}
	}
	return temp;
}

/**   @fn string SubDiskNameFromPath(string &m_directory)

 *    @brief                     <���ļ���������·����ȡ�ļ����ڴ��̺�>

 *    @param string &m_directory �����ļ���������·��.

 *    @return  string            �����ȡ���̺ź���ļ�·��

 */
string TraversalFile::SubDiskNameFromPath(string &m_directory)
{
	string temp = m_directory; 
	int nPos = temp.find(":");
	if (-1 != nPos)
	{
		temp = temp.substr(nPos+2, temp.length() - nPos);
	}
	return temp;
}

/**   @fn void CompareTwoListByMD5(vector<all_file_info>& compare_input,vector<all_file_info>& compare_calc)

 *    @brief                                      <ͨ��MD5ֵ�ԱȲ�ͬ�ļ�>

 *    @param vector<all_file_info>& compare_input �����ֳ��ļ���Ϣ��ͨ������XML�ļ������ڴ�.

 *    @param  vector<all_file_info>& compare_calc ���뱾���ļ���Ϣͨ������õ�.

 *    @return  void           

 */
void  CalcMD5::CompareTwoListByMD5(vector<all_file_info>& compare_input,
								   vector<all_file_info>& compare_calc)//���������ļ�
{
	if (compare_calc.size() == 0 && compare_input.size() == 0)
	{
		return;
	}
	compare_file_value_vector_calc_profile.clear();
	compare_file_value_vector_input_profile.clear();
	compare_file_value_vector_calc_private.clear();
	DeleteBuildFile(compare_calc,compare_file_value_vector_calc_profile);//ɾ�����ɵ��ļ�
	DeleteBuildFile(compare_input,compare_file_value_vector_input_profile);
	vector<all_file_info>::iterator it_calc  = compare_calc.begin();
	vector<all_file_info>::iterator it_input = compare_input.begin();
	while(it_input != compare_input.end())
	{
		if(((*it_input).MD5Value).compare((*it_calc).MD5Value) == 0 )
		{
			if (it_input == compare_input.end()-1)
			{
				compare_input.pop_back();
				if (it_calc == compare_calc.end()-1)
				{
					compare_calc.pop_back();
					it_input = compare_input.end();
					break;
				}
				it_calc  = compare_calc.erase(it_calc);
				it_input = compare_input.end();
				break;
			}
			
				it_input = compare_input.erase(it_input);
				it_calc  = compare_calc.erase(it_calc);
		}
		else
		{
			if (++it_calc == compare_calc.end())
			{
				it_calc = compare_calc.begin();
				it_input++;
			}
			/*++it_calc;*/
		}
	}
	CompareTwoListByName(compare_input,compare_calc);//���ֶ����ļ�
	return;
}

/**   @fn void CompareTwoListByName(vector<all_file_info>& compare_input, vector<all_file_info>& compare_calc)

 *    @brief                                      <ͨ���Ա��ļ����ƣ��ڶԱ���MD5֮�����>

 *    @param vector<all_file_info>& compare_input ����Աȹ�MD5֮����ļ���Ϣ.

 *    @param  vector<all_file_info>& compare_calc ����Աȹ�MD5֮��ı����ļ���Ϣ.

 *    @return  void           

 */
void CalcMD5::CompareTwoListByName(vector<all_file_info>& compare_input, 
								   vector<all_file_info>& compare_calc)
{
	if (compare_calc.size() == 0)
	{
		return;
	}
	vector<all_file_info>::iterator it_calc  = compare_calc.begin();
	vector<all_file_info>::iterator it_input = compare_input.begin();
	while(it_input != compare_input.end())
	{
		string name_input = SubFileNameFromBack((*it_input).directory);
		string name_clac  = SubFileNameFromBack((*it_calc).directory);
		if(name_input.compare(name_clac) == 0)
		{
			if (it_input == compare_input.end() - 1)
			{
				compare_input.pop_back();//����
				CalcMD5::compare_file_value_vector_calc_private.push_back(*it_calc);//��ͬ
				compare_calc.pop_back();
				it_input = compare_input.end();
				break;
			}
			it_input = compare_input.erase(it_input);
			CalcMD5::compare_file_value_vector_calc_private.push_back(*it_calc);//��ͬ
			it_calc  = compare_calc.erase(it_calc);
		}
		else
		{
			if (it_calc == compare_calc.end()-1)
			{
				++it_input;
			}
			it_calc++;
		}
		if (it_calc == compare_calc.end())
		{
			it_calc = compare_calc.begin();
		}
	}
	return;
}

/**   @fn void DeleteBuildFile(vector<all_file_info>& compare_calc,vector<all_file_info>&  out_profile)

 *    @brief                                      <�ļ�ɸѡ��ȥ������Աȵ��ļ�������File_Suffix[]>

 *    @param vector<all_file_info>& compare_input ���뵼����ļ���Ϣ.

 *    @param  vector<all_file_info>& compare_calc ��������ı����ļ���Ϣ.

 *    @return  void           

 */
void  CalcMD5::DeleteBuildFile(vector<all_file_info>& compare_calc,
							   vector<all_file_info>&  out_profile)
{
	if (compare_calc.size() == 0)
	{
		return;
	}
	vector<all_file_info>::iterator it = compare_calc.begin();
	while(it < compare_calc.end())
	{
		string name_clac  = SubFileNameFromBack((*it).directory);
		
		if(name_clac.compare("��ʶ��.xml") == 0 || name_clac.compare("����ļ�.zip") == 0)
		{
			if ((it == compare_calc.end() - 1))
			{
				compare_calc.pop_back();
				it = compare_calc.end();
				break;
			}
			it = compare_calc.erase(it);
		}
		bool name_suffix = SubFileSuffix((*it).directory);
		if (name_suffix)
		{
			out_profile.push_back(*it);
			if ((it == compare_calc.end() - 1))
			{
				compare_calc.pop_back();
				it = compare_calc.end();
				break;
			}
			it = compare_calc.erase(it);
		}
		else
		{
			it++;
		}
		
	}
}