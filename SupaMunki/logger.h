//source: http://gernotklingler.com/blog/simple-customized-logger-based-boost-log-v2/ 
#pragma once

//#define BOOST_LOG_DYN_LINK // necessary when linking the boost_log library dynamically

#include <boost/log/trivial.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <string>
#include <windows.h>

// the logs are also written to LOGFILE
#define LOGFILE "SupaMunki.log"
#define DEBUG_SUBKEY L"TypeLib\\{7C9AAAA5-ED08-49CB-BFD2-738C33731292}\\1.0\\Debug"
#define DEBUG_TRACELEVEL L"tracelevel"
#define DEBUG_TRACEDIR L"tracedir"

enum severity_level
{
	basic,
	general,
	detailed,
	verbose
};

// register a global logger
BOOST_LOG_GLOBAL_LOGGER(logger, boost::log::sources::severity_logger_mt< severity_level >)

// ===== log macros =====
#define LOG_BASIC    BOOST_LOG_SEV(logger::get(), severity_level::basic)		// errors only
#define LOG_GENERAL  BOOST_LOG_SEV(logger::get(), severity_level::general)		// gerenal info about what's going on
#define LOG_DETAILED BOOST_LOG_SEV(logger::get(), severity_level::detailed)		// detailed info about internal calls
#define LOG_VERBOSE	 BOOST_LOG_SEV(logger::get(), severity_level::verbose)		// values of internal variables, addresses, e.t.c: all info

bool isThresholdReached(const boost::log::attribute_value_set& set);
void severity_and_message(const boost::log::record_view &view, boost::log::formatting_ostream &os);
std::wstring GetLogFile();
LONG GetThreshold();