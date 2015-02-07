/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file timeout_debuger.h
 * @author yuanyi03(yuanyi03@baidu.com)
 * @date 2014/11/10 20:53:50
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef PS_SPI_TIMEOUT_DEBUGER_H
#define PS_SPI_TIMEOUT_DEBUGER_H

#include <sys/time.h>
#include <string>

#include "noncopyable.h"

namespace common {
namespace util {

class TimerDebuger: public noncopyable
{
public:
    explicit TimerDebuger(const std::string& log_info): 
        _log_info(log_info)
    {
        gettimeofday(&_start_tm, NULL);            
    }

    TimeDeubuger(const char* fmt, ...);

    TimerDebuger()
    {
        gettimeofday(&_start_tm, NULL); 
    }

    unsigned long LastTimeMS() {
        struct timeval time; 
        gettimeofday(&time, NULL);
        unsigned long last_time = 
            (time.tv_sec - _start_tm.tv_sec) * 1000 +
            (time.tv_usec - _start_tm.tv_usec) / 1000;
        return last_time;
    }

    unsigned long LastTimeUS() {
        struct timeval time; 
        gettimeofday(&time, NULL);
        unsigned long last_time = 
            (time.tv_sec - _start_tm.tv_sec) * 1000000 +
            (time.tv_usec - _start_tm.tv_usec) ;
        return last_time;
    }

    ~TimerDebuger()
    {
        gettimeofday(&_end_tm, NULL); 
        long last_time = 
            (_end_tm.tv_sec - _start_tm.tv_sec ) * 1000000 +
            (_end_tm.tv_usec - _start_tm.tv_usec) ;
        fprintf(stderr, "%s %luus", log_info.c_str(), last_time);
    }
private:
    std::string _log_info;
    struct timeval _start_tm;
    struct timeval _end_tm;
};
}   // ending namespace util
}   // ending namespace common


#endif  //PS_SPI_TIMEOUT_DEBUGER_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
