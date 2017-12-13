
#include "Logger.hpp"
#include <iomanip>
#include <thread>
#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
#include <fstream>

//STATICAL VARIABLE DECLARATION
std::mutex gh::Logger::mutex_;
std::string gh::Logger::filename_("logger.log");

#ifdef _DEBUG
	constexpr gh::Logger::LogLevel kDefaultLogLevel = gh::Logger::kAll;
#else
	constexpr gh::Logger::LogLevel kDefaultLogLevel = gh::Logger::kErrorOnly;
#endif
	gh::Logger::LogLevel gh::Logger::log_level_ = kDefaultLogLevel;


void gh::Logger::_write(const std::string & status, const std::string & text){
	//[status] Thread:(thread_no) 2017-10-15 03:47:24 <tag> | [text]
	//______________________________________________________| [multi text]

	//error check
	if (text.empty() || status.empty()) return;

	//for thread safe, lock with mutex
	std::lock_guard<std::mutex> lock(Logger::mutex_);
	
	//multi line text split
	std::vector<std::string> multiline_text;
	std::string line_text("");
	for (auto c : text) {
		if (c == '\n') {
			multiline_text.push_back(line_text);
			line_text.clear();
		}
		else line_text.push_back(c);
	}
	multiline_text.push_back(line_text);

	//get the now date and time
	time_t now = std::time(nullptr);
	struct tm* local_now = std::localtime(&now);

	//formatting status string
	std::stringstream status_text_sstream;
	status_text_sstream << status << " Thread:" << std::setw(8) << std::left << std::this_thread::get_id() << " ";
	status_text_sstream << (local_now->tm_year + 1900) << "-"  << std::right << std::setfill('0') << std::setw(2) << (local_now->tm_mon + 1) << "-" << std::setfill('0') << std::setw(2) << local_now->tm_mday << " ";
	status_text_sstream << std::setfill('0') << std::setw(2) << local_now->tm_hour << ":" << std::setfill('0') << std::setw(2) << local_now->tm_min << ":" << std::setw(2) << std::setfill('0') << local_now->tm_sec << " ";
	if(15 - this->tag_.size() > 0) status_text_sstream << std::setw(15 - this->tag_.size()) << std::setfill(' ') << " ";
	status_text_sstream << "<" << this->tag_ << "> ";

	//generate output strings
	std::string output_text(status_text_sstream.str());
	output_text += "| " + multiline_text.at(0);
	for (auto line_text = multiline_text.begin()+1; line_text != multiline_text.end(); ++line_text) {
		output_text += '\n';
		std::string space_str;
		space_str.resize(status_text_sstream.str().size(), ' ');
		output_text += space_str;
		output_text += "| " + *line_text;
	}

	//open the log file.
	if(this->is_output_file_){
		std::ofstream output_file_stream(filename_, std::ios::app);
		if (output_file_stream) output_file_stream << output_text << std::endl;
	}

	//write down to standard io
	if (this->is_output_stdio_) std::cout << output_text << std::endl;

}

