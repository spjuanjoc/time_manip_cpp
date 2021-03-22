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
  fmt::print("Using std::time:{0:{1}}","", 17);
  std::time_t t = std::time(nullptr);
  fmt::print("1. The date is {:%d-%m-%Y %H:%M:%S}.\n", fmt::localtime(t));
//  auto a = fmt::format("1. The date is {:%d-%m-%Y %H:%M:%S}.\n", fmt::localtime(t));
//  return a;
}

void time_with_chrono()
{
  fmt::print("Using system_clock to_time_t:    ");
  std::time_t now = system_clock::to_time_t(system_clock::now());
  fmt::print("2. The date is {0:%d-%m-%Y %H:%M:%S}.\n", fmt::localtime(now));
}

void time_with_ms()
{
  fmt::print("Using chrono time_point with ms: ");
  time_point<system_clock> time_now = system_clock::now();
  auto duration = time_now.time_since_epoch();
  auto now_ms   = duration_cast<milliseconds>(duration) % 1000;
  fmt::print("3. The date is {0:%d-%m-%Y %H:%M:%S}.{1}\n", fmt::localtime(time_now), now_ms.count());
}

int main(int argc, char** argv)
{
  get_time_POSIX();
  time_with_chrono();
  time_with_ms();
  std::this_thread::sleep_for(1s);
  time_with_ms();
  std::this_thread::sleep_for(200ms);
  time_with_ms();

  return 0;
}

// https://www.delftstack.com/es/howto/cpp/how-to-get-time-in-milliseconds-cpp/
