#ifndef		LOGGER_HPP_
# define	LOGGER_HPP_

# include	<iostream>
# include	<fstream>
# include	<sstream>
# include	<string>
# include	<iomanip>
# include	<map>
# include	<ctime>

// For writing log message to standard / error output or to log files
class Logger
{
public:

	// Set the open Mode for files
	enum Mode
	{
		APPEND = 0,	// Append data to the end of file
		ATE = 1,	// Set position to the end of file
		TRUNC = 2	// Replace file content
	};

private:

	// Member data
	static Logger	_instance;
	std::map<std::string, std::ofstream*>	_logFileList;

public:
	// Destructor
	virtual ~Logger()
	{
		std::map<std::string, std::ofstream*>::iterator	it = _logFileList.begin();

		for (; it != _logFileList.end(); ++it)
		{
			(*it).second->close();
			delete (*it).second;
			it = _logFileList.erase(it);
		}
	}

	/*
		Return instance of the Logger Class.
	*/
	static Logger	&getInstance();

	/*
		Open a file to log on until closing it
		@param &logFileName: Path to the file to open
		@param mode: Open Mode. Default value is APPEND
	*/
	void	registerFile(std::string const &logFileName, Logger::Mode mode = Logger::APPEND);

	/*
		Close a previously opened file
		@param &logFileName: Path to the file to open
	*/
	void	closeFile(std::string const &logFileName);

	/*
		Returns the current time as string with the following format:
		[dd/mm/yy hh:mm:ss]
	*/
	static std::string	getTimeStr();

	/*
		Write msg to an output stream
		@param &os: Output stream
		@param &msg: Message to write
	*/
	static void	logToOstream(std::ostream &os, std::string const &msg);

	/*
		Write msg to a previously opened file
		@param logFileName: Path to the file to open
		@param &msg: Message to write
	*/
	void		logToFile(std::string const &logFileName, std::string const &msg);

private:
	// Private Constructor
	Logger() {}
	// Private copy Constructor
	Logger(Logger const &) {}
	// Private Assignment Constructor
	Logger	&operator=(Logger const &) {}
};

/* General Use MACRO */
/* Log to stdout */
# define	LOG(msg)	Logger::getInstance().logToOstream(std::cout, msg)
/* Log to stderr */
# define	LOGERR(msg)	Logger::getInstance().logToOstream(std::cerr, msg)
/* Log to a specified file if set */
# define	LOGFILE(fileName, msg)	Logger::getInstance().logToFile(fileName, msg)

#endif // !LOGGER_HPP_