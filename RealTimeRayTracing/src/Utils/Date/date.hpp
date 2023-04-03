#ifndef __TIME_HPP__
#define __TIME_HPP__


struct Date
{
    int year;
    int month;
    int day;

    int hour;
    int minute;
    int second;
    int milisecond;
    int microsecond;
    int nanosecond;

    static Date getCurrentDate();
};

#endif
