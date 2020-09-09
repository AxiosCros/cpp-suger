#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/time_parsers.hpp>
#include <csugar.h>
#include <ctime>

std::string csugar::utc_datetime(const time_t &time) {
  char buf[80];
  std::strftime(buf, sizeof buf, "%FT%TZ", gmtime(&time));
  return buf;
}

time_t csugar::utc_strtotime(const std::string &utc_datetime) {
  struct tm tm {};
  strptime(utc_datetime.c_str(), "%Y-%m-%dT%H:%M:%SZ", &tm);
  time_t t = timegm(&tm);
  return boost::lexical_cast<long long>(t);
}

long csugar::timestamp() {
  boost::posix_time::ptime pt;
  boost::posix_time::time_duration du =
      boost::posix_time::second_clock::universal_time() - pt;
  return du.total_seconds();
}

std::string csugar::datetime(const std::string &format, long timestamp) {
  time_t t = timestamp;
  ctime(&t);
  char buf[80];
  std::strftime(buf, sizeof buf, format.c_str(), gmtime(&t));
  return buf;
}