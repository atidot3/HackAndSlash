#include "IniReader.h"
#include <Winsock2.h>
#include <Windows.h>

const unsigned int MAX_BUFFER = 256;

IniFile::IniFile()
{

}
IniFile::~IniFile()
{

}
int IniFile::Create(const char * lpszFullName)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(lpszFullName, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		return GetLastError();
	}
	FindClose(hFind);
	m_strConfigFileName = lpszFullName;
	m_strLastReadGroup.clear();
	m_strLastReadKey.clear();
	return 0;
}
int IniFile::Create(const char * lpszPathName, const char * lpszFileName)
{
	m_strConfigFileName = lpszPathName;
	m_strConfigFileName.append("/");
	m_strConfigFileName.append(lpszFileName);
	return 0;
}
bool IniFile::Read(const char *group, const char *key, std::string &val)
{
	if (NULL == group || NULL == key)
	{
		return false;
	}
	m_strLastReadGroup = group;
	m_strLastReadKey = key;
	char buffer[MAX_BUFFER + 1] = { 0x00, };
	if (0 == GetPrivateProfileString(group, key, NULL, buffer, MAX_BUFFER, m_strConfigFileName.c_str()))
	{
		std::cout << "truc compliqué " << group << " " << key << " " << m_strConfigFileName.c_str() << std::endl;
		return false;
	}
	val = buffer;
	return true;
}
std::string IniFile::Read(const char *group, const char *key)
{
	std::string strTemp;
	if (NULL == group || NULL == key)
	{
		return strTemp;
	}
	m_strLastReadGroup = group;
	m_strLastReadKey = key;
	if (!Read(group, key, strTemp))
	{
		strTemp = "";
	}
	return strTemp;
}
bool IniFile::Read(const char *group, const char *key, bool &bFlag)
{
	if (NULL == group || NULL == key)
	{
		return false;
	}
	m_strLastReadGroup = group;
	m_strLastReadKey = key;
	std::string strTemp;
	if (!Read(group, key, strTemp))
	{
		return false;
	}
	if (0 == strTemp.compare("true") || 0 == strTemp.compare("TRUE"))
	{
		bFlag = true;
	}
	else
	{
		bFlag = false;
	}
	return true;
}
bool IniFile::Read(const char *group, const char *key, char &num)
{
	if (NULL == group || NULL == key)
	{
		return false;
	}
	m_strLastReadGroup = group;
	m_strLastReadKey = key;
	std::string strTemp;
	if (!Read(group, key, strTemp))
	{
		return false;
	}
	num = (char)atoi(strTemp.c_str());
	return true;
}
bool IniFile::Read(const char *group, const char *key, short &num)
{
	if (NULL == group || NULL == key)
	{
		return false;
	}

	m_strLastReadGroup = group;
	m_strLastReadKey = key;

	std::string strTemp;
	if (!Read(group, key, strTemp))
	{
		return false;
	}
	num = (short)atoi(strTemp.c_str());
	return true;
}
bool IniFile::Read(const char *group, const char *key, int &num)
{
	if (NULL == group || NULL == key)
	{
		return false;
	}
	m_strLastReadGroup = group;
	m_strLastReadKey = key;
	std::string strTemp;
	if (!Read(group, key, strTemp))
	{
		return false;
	}
	num = atoi(strTemp.c_str());
	return true;
}
bool IniFile::Read(const char *group, const char *key, float &num)
{
	if (NULL == group || NULL == key)
	{
		return false;
	}
	m_strLastReadGroup = group;
	m_strLastReadKey = key;
	std::string strTemp;
	if (!Read(group, key, strTemp))
	{
		return false;
	}
	num = (float)atof(strTemp.c_str());
	return true;
}
bool IniFile::Read(const char *group, const char *key, unsigned char &num)
{
	if (NULL == group || NULL == key)
	{
		return false;
	}
	m_strLastReadGroup = group;
	m_strLastReadKey = key;
	std::string strTemp;
	if (!Read(group, key, strTemp))
	{
		return false;
	}
	num = (unsigned char)atoi(strTemp.c_str());
	return true;
}
bool IniFile::Read(const char *group, const char *key, unsigned short &num)
{
	if (NULL == group || NULL == key)
	{
		return false;
	}
	m_strLastReadGroup = group;
	m_strLastReadKey = key;
	std::string strTemp;
	if (!Read(group, key, strTemp))
	{
		return false;
	}
	num = (unsigned short)atoi(strTemp.c_str());
	return true;
}
bool IniFile::Read(const char *group, const char *key, unsigned int &num)
{
	if (NULL == group || NULL == key)
	{
		return false;
	}
	m_strLastReadGroup = group;
	m_strLastReadKey = key;
	std::string strTemp;
	if (!Read(group, key, strTemp))
	{
		return false;
	}
	num = (unsigned int)atoi(strTemp.c_str());
	return true;
}
bool IniFile::Read(const char *pszGroup, const char *pszKey, unsigned long &dwNumber)
{
	if (NULL == pszGroup || NULL == pszKey)
	{
		return false;
	}
	m_strLastReadGroup = pszGroup;
	m_strLastReadKey = pszKey;
	std::string strTemp;
	if (false == Read(pszGroup, pszKey, strTemp))
	{
		return false;
	}
	dwNumber = (unsigned long)(atoi(strTemp.c_str()));
	return true;
}