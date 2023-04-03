#include "date.hpp"
#include <chrono>
#include <ctime>

Date Date::getCurrentDate()
{
    Date date;
    
    auto now = std::chrono::system_clock::now();
    auto fullNanosec = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();

    

    auto timer = std::chrono::system_clock::to_time_t(now);
    std::tm dateTm = *std::localtime(&timer);

    date.year = dateTm.tm_year + 1900;
    date.month = dateTm.tm_mon + 1;
    date.day = dateTm.tm_mday;

    date.hour = dateTm.tm_hour;
    date.minute = dateTm.tm_min;
    date.second = dateTm.tm_sec;

    date.milisecond = (fullNanosec / 1000000) % 1000;
    date.microsecond = (fullNanosec / 1000) % 1000;
    date.nanosecond = fullNanosec % 1000;

    return date;
}
