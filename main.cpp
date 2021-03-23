#include "fmt/format.h"
#include <fmt/chrono.h>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;
using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::time_point;
using std::chrono::duration_cast;

auto get_time_POSIX()
{
  fmt::print("{0:<35}: ", "Using std::time");
  std::time_t t = std::time(nullptr);
  fmt::print("{:%d-%m-%Y %H:%M:%S}\n", fmt::localtime(t));
//  auto a = fmt::format("1. The date is {:%d-%m-%Y %H:%M:%S}.\n", fmt::localtime(t));
//  return a;
}

void time_with_chrono()
{
  fmt::print("{0:<35}: ", "Using system_clock to_time_t");
  std::time_t now = system_clock::to_time_t(system_clock::now());
  fmt::print("{0:%d-%m-%Y %H:%M:%S}\n", fmt::localtime(now));
}

void time_with_ms()
{
  fmt::print("{0:<35}: ", "Using chrono time_point with ms");
  time_point<system_clock> time_now = system_clock::now();
  auto duration = time_now.time_since_epoch();
  auto now_ms   = duration_cast<milliseconds>(duration) % 1000;
  fmt::print("{0:%d-%m-%Y %H:%M:%S}.{1} {0:%z}\n", fmt::localtime(time_now), now_ms.count());
}

// https://en.wikipedia.org/wiki/ISO_8601
// Date and time in UTC	2021-03-22T16:07:49+00:00
// 2021-03-22T16:07:49Z
// 20210322T160749Z
void time_ISO8601()
{
  fmt::print("{0:<35}: ", "Time as ISO 8601 with UTC");
  std::time_t now = system_clock::to_time_t(system_clock::now());
  fmt::print("{0:%Y-%m-%d}T{0:%H:%M:%S}{0:%z}\n", fmt::localtime(now));
}

int main(int argc, char** argv)
{
  get_time_POSIX();
  time_with_chrono();
  time_with_ms();
//  std::this_thread::sleep_for(1s);
//  time_with_ms();
  std::this_thread::sleep_for(200ms);
  time_with_ms();
  time_ISO8601();

  return 0;
}

// https://www.delftstack.com/es/howto/cpp/how-to-get-time-in-milliseconds-cpp/
