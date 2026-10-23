// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 30.09.2021.
//

#include "AeoGameFramework.hpp"
#include "Internal.hpp"
using namespace std::chrono_literals;

TimeMs getTickCount() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        Clock::now() - framework_data->init_moment
    ).count();
}

Timer::Timer(TimeMs interval): interval(interval) { }

bool Timer::IsStarted() const {
    return last_check != 0;
}
bool Timer::IsExpired() const {
    return getTickCount() - last_check >= interval;
}

bool Timer::IfExpiredThenStart() {
    if(not IsExpired()) return false;
    Start();
    return true;
}
void Timer::SetInterval(TimeMs new_interval) { interval = new_interval; }
void Timer::Start() { last_check = getTickCount(); }
void Timer::Stop() { last_check = 0; }

TimeMs Timer::Interval() const { return interval; }
TimeMs Timer::StartTime() const { return last_check; }
TimeMs Timer::Elapsed() const { return getTickCount() - last_check; }
