
/** Logger.hpp
 * Refactored in Oct, 2017
 * (c) 2017 white
 */

#pragma once
#ifndef JUBEON_LOGGER_HPP_
#define JUBEON_LOGGER_HPP_

#include <string>
#include <mutex>
#include <memory>

namespace jubeon{

/** class Logger
 * Logging class
 * @version 2017.10
 */
class Logger {
public:

	enum LogLevel {
		kAll = 0,
		kWarningAndError = 1,
		kErrorOnly = 2,
		kNoLogging = 3
	};

	explicit Logger(const std::string & tag, bool is_output_stdio = true, bool is_output_file = true);
	virtual ~Logger();

	void information(const std::string & text);
	void warning(const std::string & text);
	void error(const std::string & text);
	
	void changeLogLevel(LogLevel log_level);
	void setFileName(const std::string & new_filename);
	std::string getFileName(void) const;

private:
	Logger() = delete;
	const std::string tag_;
	const bool is_output_stdio_;
	const bool is_output_file_;

	void _write(const std::string & status, const std::string & text);

	//STATICAL FUNCTIONS AND VARIABLES
	//static std::ofstream output_file_stream_;
	static std::mutex mutex_;
	static LogLevel log_level_;
	static std::string filename_;
	
	
};

};


//### inline functions ###

inline jubeon::Logger::Logger(const std::string & tag, bool is_output_stdio, bool is_output_file)
	: tag_(tag), is_output_stdio_(is_output_stdio), is_output_file_(is_output_file){
}

inline jubeon::Logger::~Logger(){
	//Nothing to do.
}

inline void jubeon::Logger::information(const std::string & text) {
	if(this->log_level_ == kAll) this->_write("INFO", text);
}

inline void jubeon::Logger::warning(const std::string & text) {
	if(this->log_level_ <= kWarningAndError) this->_write("WARN", text);
}

inline void jubeon::Logger::error(const std::string & text) {
	if(this->log_level_ <= kErrorOnly) this->_write("ERRO", text);
}

inline void jubeon::Logger::changeLogLevel(LogLevel log_level) {
	//for thread safe, lock with mutex
	std::lock_guard<std::mutex> lock(Logger::mutex_);

	this->log_level_ = log_level;
}

inline void jubeon::Logger::setFileName(const std::string & new_filename)
{
	//for thread safe, lock with mutex
	std::lock_guard<std::mutex> lock(Logger::mutex_);

	this->filename_ = new_filename;
}

inline std::string jubeon::Logger::getFileName(void) const
{
	return filename_;
}

#endif // JUBEON_LOGGER_HPP_
