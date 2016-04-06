#ifndef __INIFILE_H__
#define __INIFILE_H__

#include <iostream>
#include <cstdlib>

class IniFile
{
public:
	IniFile(void);
	virtual ~IniFile(void);
	int							Create(const char * lpszFullName);
	int							Create(const char * lpszPathName, const char * lpszFileName);
public:
	std::string					Read(const char *group, const char *key);
	bool						Read(const char *group, const char *key, std::string &val);
	bool						Read(const char *group, const char *key, bool &flag);
	bool						Read(const char *group, const char *key, char &num);
	bool						Read(const char *group, const char *key, short &num);
	bool						Read(const char *group, const char *key, int &num);
	bool						Read(const char *group, const char *key, float &num);
	bool						Read(const char *group, const char *key, unsigned char &num);
	bool						Read(const char *group, const char *key, unsigned short &num);
	bool						Read(const char *group, const char *key, unsigned int &num);
	bool						Read(const char *pszGroup, const char *pszKey, unsigned long &dwNumber);
public:
	const char *				GetConfigFileName() { return m_strConfigFileName.c_str(); }
	const char *				GetLastReadGroup() { return m_strLastReadGroup.c_str(); }
	const char *				GetLastReadKey() { return m_strLastReadKey.c_str(); }
private:
	std::string					m_strConfigFileName;
	std::string					m_strLastReadGroup;
	std::string					m_strLastReadKey;
};

#endif // __INIFILE_H__
