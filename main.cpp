/**
 * @brief Manipulates some different time structures, and prints it to the console.
 *
 * @author spjuanjoc
 * @date   2021-03-22
 */

#include <fmt/chrono.h>
#include <fmt/format.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;
using std::chrono::system_clock;
using std::chrono::time_point;

using duration_ratio      = std::chrono::duration<uint64_t, std::ratio<1, 1000000000>>;
using high_res_time_point = std::chrono::time_point<system_clock, duration_ratio>;


/**
 * @brief Gets datetime using time_t and iostreams.
 *
 * @return
 */
std::string
getLocaltimeTm()
{
  const time_t  timeStamp = std::time(nullptr);
  const std::tm localTime = *localtime(&timeStamp);

  std::ostringstream st;
  st << std::put_time(&localTime, "%Y-%m-%dT%T%z");

  return st.str();
}

/**
 * @brief Gets datetime using time_t and iostreams.
 *
 * @return
 */
std::string
getLocaltimeSystemClock()
{
  const std::time_t now       = system_clock::to_time_t(system_clock::now());
  const std::tm     localTime = *localtime(&now);

  std::ostringstream st;
  st << std::put_time(&localTime, "%Y-%m-%dT%T%z");

  return st.str();
}

/**
 * @brief Gets the datetime as std::time to time_t.
 *
 * @remark Uses fmt for formatting.
 *
 * @return A localtime string in ISO_8601.
 */
std::string
getPosixTimeT()
{
  const std::time_t now = std::time(nullptr);
  return fmt::format("{:%Y-%m-%dT%H:%M:%S%z}\n", fmt::localtime(now));
}


/**
 * @brief Gets the datetime as system_clock converted to time_point, and calculates the milliseconds.
 *
 * @remark Uses fmt for formatting.
 *
 * @return A localtime string in ISO_8601 with milliseconds.
 */
std::string
getClockTimePointMs()
{
  const time_point<system_clock> time_now = system_clock::now();

  const auto now_ms = (duration_cast<milliseconds>(time_now.time_since_epoch()) % 1000).count();

  return fmt::format("{0:%Y-%m-%dT%H:%M:%S}.{1}{0:%z}\n", fmt::localtime(time_now), now_ms);
  //  auto duration = time_now.time_since_epoch();
  //  auto now_ms   = duration_cast<milliseconds>(duration) % 1000;
  //  return fmt::format("{0:%d-%m-%Y %H:%M:%S}.{1} {0:%z}\n", fmt::localtime(time_now), now_ms.count());
}

/**
 * @brief Gets the datetime as system_clock converted to time_t.
 *
 * @remark Uses fmt form formatting.
 *         This should be compatible with C time.
 *
 * @return A localtime string in ISO_8601
 */
std::string
getClockTimeT_ISO8601()
{
  const std::time_t now = system_clock::to_time_t(system_clock::now());
  return fmt::format("{0:%Y-%m-%d}T{0:%H:%M:%S}{0:%z}\n", fmt::localtime(now));
}

/**
 * @brief Gets the datetime in ISO_8601 using std::system_clock.
 *
 * @remark Uses fmt::format for formatting.
 *
 * @return A localtime string in ISO_8601.
 */
std::string
getClockTimePoint_ISO8601()
{
  return fmt::format("{0:%Y-%m-%d}T{0:%H:%M:%S}{0:%z}\n", fmt::localtime(system_clock::now()));
}


/**
 * @brief Gets the now time with the max possible precision.
 *
 * @return The high resolution time point.
 */
high_res_time_point
count()
{
  return std::chrono::high_resolution_clock::now();
}

/**
 * @brief Calculates the elapsed microseconds since begin to end.
 *
 * @param begin The starting time point.
 * @param end   The ending time point.
 *
 * @return The microseconds elapsed.
 */
auto
elapsed_time(const high_res_time_point& begin, const high_res_time_point& end)
{
  return duration_cast<nanoseconds>(end - begin).count();
}

/**
 * @brief Creates an std::tm and converts it to an std::time_t.
 *
 * @return The stream with the timestamp and the tm ISO C time structure.
 */
std::string
convertTmToTimeT()
{
  std::tm date_time_tm = tm();

  date_time_tm.tm_year = 2021 - 1900;
  date_time_tm.tm_mon  = 1;
  date_time_tm.tm_mday = 10;
  date_time_tm.tm_hour = 12;
  date_time_tm.tm_min  = 15;
  date_time_tm.tm_sec  = 30;

  const std::time_t date_time_time_t = mktime(&date_time_tm);

  std::ostringstream stream;
  stream << "Unix timestamp: " << date_time_time_t << " for: " <<  std::put_time(&date_time_tm, "%Y-%m-%dT%T%z") << '\n';

  return stream.str();
}

/**
 * @see https://en.wikipedia.org/wiki/ISO_8601
 * @see https://en.cppreference.com/w/cpp/io/manip/put_time
 * @see https://www.delftstack.com/es/howto/cpp/how-to-get-time-in-milliseconds-cpp/
 */
int
main()
{
  const auto start = count();

  fmt::print("{0:<25}: ", "localtime as std::tm");
  fmt::print("{}\n", getLocaltimeTm());

  fmt::print("{0:<25}: ", "time_t from system_clock");
  fmt::print("{}\n", getLocaltimeSystemClock());

  fmt::print("{0:<25}: ", "std::time");
  fmt::print("{}", getPosixTimeT());

  fmt::print("{0:<25}: ", "time_point with ms");
  fmt::print("{}", getClockTimePointMs());

//  fmt::print("\tSleep for 1 s\n");
//  std::this_thread::sleep_for(1s);

  fmt::print("{0:<25}: ", "time_point with ms");
  fmt::print("{}", getClockTimePointMs());

//  fmt::print("\tSleep for 200 ms\n");
//  std::this_thread::sleep_for(200ms);

  fmt::print("{0:<25}: ", "time_point with ms");
  fmt::print("{}", getClockTimePointMs());

  fmt::print("{0:<25}: ", "time_t as ISO 8601");
  fmt::print("{}", getClockTimeT_ISO8601());

  fmt::print("{0:<25}: ", "time_point as ISO 8601");
  fmt::print("{}", getClockTimePoint_ISO8601());

  fmt::print("{0:<25}: ", "std::tm to std::time_t");
  fmt::print("{}", convertTmToTimeT());

//  fmt::print("\tSleep for 1 us\n");
//  std::this_thread::sleep_for(1us);

  const auto end = count();
  fmt::print("elapsed time {} ns", elapsed_time(start, end));

  return 0;
}
