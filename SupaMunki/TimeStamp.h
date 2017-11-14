#pragma once

#include <boost/log/trivial.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/make_shared.hpp>


class TimeStamp : public boost::log::attributes::local_clock {
public:
	typedef boost::log::attribute_value attribute_type;
	typedef boost::log::attributes::local_time_traits TimeTraitsT;
	typedef TimeTraitsT::time_type time_type;
	typedef boost::log::attributes::basic_clock< std::string > result_value;

public:
	boost::shared_ptr< attribute_type > get_value() {
		time_type posix_time = boost::date_time::microsec_clock< time_type >::universal_time();
		time_type::time_duration_type time = posix_time.time_of_day();
		time_type::date_type date = posix_time.date();
		std::stringstream formatter;

		formatter
			<< date.year() << "-"
			<< std::setfill('0') << std::setw(2) << int(date.month()) << "-"
			<< std::setfill('0') << std::setw(2) << date.day() << " "
			<< std::setfill('0') << std::setw(2) << boost::date_time::absolute_value(time.hours()) << ":"
			<< std::setfill('0') << std::setw(2) << boost::date_time::absolute_value(time.minutes()) << ":"
			<< std::setfill('0') << std::setw(2) << boost::date_time::absolute_value(time.seconds()) << ","
			<< std::setfill('0') << std::setw(2) << boost::date_time::absolute_value(time.fractional_seconds()) / 1000
			;

		return boost::make_shared< result_value >(formatter.str());
	}
};