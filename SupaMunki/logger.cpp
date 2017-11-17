#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/make_shared.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/sinks.hpp>
#include <fstream>
#include "logger.h"
#include "WinReg.h"
#include "Strings.h"


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;


using namespace winreg;


bool isThresholdReached(const boost::log::attribute_value_set& set)
{
	auto threshold = GetThreshold();
	return set["Severity"].extract<severity_level>() > 0;
}

void severity_and_message(const boost::log::record_view &view, boost::log::formatting_ostream &os)
{
	const boost::posix_time::ptime &pt = *logging::extract<boost::posix_time::ptime >("TimeStamp", view);

	os  << std::setw(4) << std::setfill('0') << pt.date().year() << "."
		<< std::setw(2) << std::setfill('0') << static_cast<int>(pt.date().month()) << "."
		<< std::setw(2) << std::setfill('0') << pt.date().day() << " "
		<< std::setw(2) << std::setfill('0') << pt.time_of_day().hours() << ":"
		<< std::setw(2) << std::setfill('0') << pt.time_of_day().minutes() << ":"
		<< std::setw(2) << std::setfill('0') << pt.time_of_day().seconds() << "."
		<< std::setw(3) << std::setfill('0') << pt.time_of_day().fractional_seconds() / 1000
		<< " "
		<< "L" << logging::extract<severity_level>("Severity", view)
		<< " "
		<< " "
		<< logging::extract<std::string>("Message", view);
}

std::wstring GetLogFile()
{
	RegKey key{ HKEY_CLASSES_ROOT, DEBUG_SUBKEY };
	std::wstring result(key.GetStringValue(DEBUG_TRACEDIR));

	return Strings::JoinPaths(result, LOGFILE);
}

LONG GetThreshold()
{
	RegKey key{ HKEY_CLASSES_ROOT, DEBUG_SUBKEY };

	return key.GetDwordValue(DEBUG_TRACELEVEL);
}


BOOST_LOG_GLOBAL_LOGGER_INIT(logger, boost::log::sources::severity_logger_mt< severity_level >)
{
	boost::log::sources::severity_logger_mt< severity_level > logger;

	auto threshold = GetThreshold();

	// add a text sink
	typedef sinks::asynchronous_sink<sinks::text_ostream_backend> text_sink;
	boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

	// add "console" output stream to our sink
	sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>(GetLogFile()));

	// specify the format of the log message
	sink->set_formatter(&severity_and_message);

	// just log messages with severity >= SEVERITY_THRESHOLD are written
	sink->set_filter(&isThresholdReached);

	// "register" our sink
	if (threshold > 0) {
		sink->locked_backend()->auto_flush(true);
		logging::core::get()->add_sink(sink);
	}

	logging::add_common_attributes();

	return logger;
}