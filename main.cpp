#include "fmt/format.h"
#include <fmt/chrono.h>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;
using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::time_point;
using std::chrono::duration_cast;

auto get_POSIX_time_t()
{
  std::time_t now = std::time(nullptr);
  return fmt::format("{:%Y-%m-%d %H:%M:%S%z}\n", fmt::localtime(now));
}

auto get_clock_time_t()
{
  std::time_t now = system_clock::to_time_t(system_clock::now());
  return fmt::format("{0:%Y-%m-%d %H:%M:%S%z}\n", fmt::localtime(now));
}

auto get_clock_time_point_ms()
{
  time_point<system_clock> time_now = system_clock::now();
  auto now_ms = (duration_cast<milliseconds>(time_now.time_since_epoch()) % 1000).count();
//  auto duration = time_now.time_since_epoch();
//  auto now_ms   = duration_cast<milliseconds>(duration) % 1000;
//  fmt::print("{0:%d-%m-%Y %H:%M:%S}.{1} {0:%z}\n", fmt::localtime(time_now), now_ms.count());
  return fmt::format("{0:%Y-%m-%d %H:%M:%S}.{1}{0:%z}\n", fmt::localtime(time_now), now_ms);
}

/// Get time in ISO 8602 using system_clock as time_t
/// This should be compatible to C time
/// Date and time in UTC	2021-03-22T16:07:49+00:00
/// https://en.wikipedia.org/wiki/ISO_8601
/// \return
auto get_clock_time_t_ISO8601()
{
  const std::time_t now = system_clock::to_time_t(system_clock::now());
  return fmt::format("{0:%Y-%m-%d}T{0:%H:%M:%S}{0:%z}\n", fmt::localtime(now));
}

/// Get time in ISO 8601 using system_clock as time_point
/// \return
auto get_clock_time_point_ISO8601()
{
  return fmt::format("{0:%Y-%m-%d}T{0:%H:%M:%S}{0:%z}\n", fmt::localtime(system_clock::now()));
}

int main()
{
  fmt::print("{0:<25}: ", "std::time");
  fmt::print("{}", get_POSIX_time_t());

  fmt::print("{0:<25}: ", "system_clock to_time_t");
  fmt::print("{}", get_clock_time_t());

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

  return 0;
}

// https://www.delftstack.com/es/howto/cpp/how-to-get-time-in-milliseconds-cpp/
