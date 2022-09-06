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
using high_res_time_point
  = std::chrono::time_point<system_clock, std::chrono::duration<uint64_t, std::ratio<1, 1000000000>>>;

/**
 * @brief Gets the datetime as std::time to time_t.
 *
 * @remark Uses fmt for formatting.
 *
 * @return A localtime string in ISO_8601.
 */
std::string
get_POSIX_time_t()
{
  const std::time_t now = std::time(nullptr);
  return fmt::format("{:%Y-%m-%dT%H:%M:%S%z}\n", fmt::localtime(now));
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
get_clock_time_t_ISO8601()
{
  const std::time_t now = system_clock::to_time_t(system_clock::now());
  return fmt::format("{0:%Y-%m-%d}T{0:%H:%M:%S}{0:%z}\n", fmt::localtime(now));
}

/**
 * @brief Gets the datetime as system_clock converted to time_point, and calculates the milliseconds.
 *
 * @remark Uses fmt for formatting.
 *
 * @return A localtime string in ISO_8601 with milliseconds.
 */
std::string
get_clock_time_point_ms()
{
  const time_point<system_clock> time_now = system_clock::now();

  const auto now_ms = (duration_cast<milliseconds>(time_now.time_since_epoch()) % 1000).count();

  return fmt::format("{0:%Y-%m-%dT%H:%M:%S}.{1}{0:%z}\n", fmt::localtime(time_now), now_ms);
  //  auto duration = time_now.time_since_epoch();
  //  auto now_ms   = duration_cast<milliseconds>(duration) % 1000;
  //  return fmt::format("{0:%d-%m-%Y %H:%M:%S}.{1} {0:%z}\n", fmt::localtime(time_now), now_ms.count());
}

/**
 * @brief Gets the datetime in ISO_8601 using std::system_clock.
 *
 * @remark Uses fmt::format for formatting.
 *
 * @return A localtime string in ISO_8601.
 */
std::string
get_clock_time_point_ISO8601()
{
  return fmt::format("{0:%Y-%m-%d}T{0:%H:%M:%S}{0:%z}\n", fmt::localtime(system_clock::now()));
}

/**
 * @brief Gets datetime using time_t and iostreams.
 *
 * @return
 */
std::string
get_localtime_tm()
{
  const time_t  t  = std::time(nullptr);
  const std::tm tm = *localtime(&t);

  std::ostringstream st;
  st << std::put_time(&tm, "%Y-%m-%dT%T%z");

  return st.str();
}

/**
 * @brief Gets datetime using time_t and iostreams.
 *
 * @return
 */
std::string
get_localtime_system_clock()
{
  const std::time_t now = system_clock::to_time_t(system_clock::now());
  const std::tm     tm  = *localtime(&now);

  std::ostringstream st;
  st << std::put_time(&tm, "%Y-%m-%dT%T%z");

  return st.str();
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
 * @see https://en.wikipedia.org/wiki/ISO_8601
 * @see https://en.cppreference.com/w/cpp/io/manip/put_time
 * @see https://www.delftstack.com/es/howto/cpp/how-to-get-time-in-milliseconds-cpp/
 */
int
main()
{
  const auto start = count();

  std::cout << "localtime as std::tm     : ";
  std::cout << get_localtime_tm() << '\n';

  std::cout << "time_t from system_clock : ";
  std::cout << get_localtime_system_clock() << std::endl;

  fmt::print("{0:<25}: ", "std::time");
  fmt::print("{}", get_POSIX_time_t());

  fmt::print("{0:<25}: ", "time_point with ms");
  fmt::print("{}", get_clock_time_point_ms());

  fmt::print("Sleep for 1s\n");
  std::this_thread::sleep_for(1s);
  fmt::print("{0:<25}: ", "time_point with ms");
  fmt::print("{}", get_clock_time_point_ms());

  fmt::print("Sleep for 200ms\n");
  std::this_thread::sleep_for(200ms);
  fmt::print("{0:<25}: ", "time_point with ms");
  fmt::print("{}", get_clock_time_point_ms());

  fmt::print("{0:<25}: ", "time_t as ISO 8601");
  fmt::print("{}", get_clock_time_t_ISO8601());

  fmt::print("{0:<25}: ", "time_point as ISO 8601");
  fmt::print("{}", get_clock_time_point_ISO8601());

  std::this_thread::sleep_for(1us);

  const auto end = count();

  fmt::print("elapsed time {} ns", elapsed_time(start, end));

  return 0;
}
