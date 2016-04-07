#include	"Utils/Logger.hpp"

Logger	Logger::_instance = Logger();

Logger	&Logger::getInstance()
{
	return _instance;
}

void	Logger::registerFile(std::string const &logFileName, Logger::Mode mode)
{
	std::ofstream	*file = new std::ofstream();
	std::ios_base::openmode	openMode = std::ios::app;

	if (mode == Logger::ATE)
		openMode = std::ios::ate;
	else if (mode == Logger::TRUNC)
		openMode = std::ios::trunc;
	else
		openMode = std::ios::app;

	file->open(logFileName, openMode);
	if (file->is_open())
		_logFileList[logFileName] = file;
	else
		std::cerr << "Can't open file: " << logFileName << std::endl;
}

void	Logger::closeFile(std::string const &logFileName)
{
	std::map<std::string, std::ofstream*>::iterator	it;

	if ((it = _logFileList.find(logFileName)) != _logFileList.end())
	{
		(*it).second->close();
		delete (*it).second;
		_logFileList.erase(it);
	}
}

std::string	Logger::getTimeStr()
{
	time_t		t = time(0);
	tm			now;
	std::stringstream oss;
	std::string	date;

	localtime_s(&now, &t);
	oss << std::to_string(now.tm_mday) + '/' + std::to_string(1 + now.tm_mon) + '/' + std::to_string(1900 + now.tm_year) + ' ';
	oss << std::setfill('0') << std::setw(2) << std::to_string(now.tm_hour) + ':';
	oss << std::setfill('0') << std::setw(2) << std::to_string(now.tm_min) + ':';
	oss << std::setfill('0') << std::setw(2) << std::to_string(now.tm_sec);
	date = "[" + oss.str() + "] ";
	return date;
}

void	Logger::logToOstream(std::ostream &os, std::string const &msg)
{
	os << Logger::getTimeStr() << msg << std::endl;
}

void	Logger::logToFile(std::string const &logFileName, std::string const &msg)
{
	std::map<std::string, std::ofstream*>::iterator	it;

	if ((it = _logFileList.find(logFileName)) != _logFileList.end())
		*((*it).second) << Logger::getTimeStr() << msg << std::endl;
}