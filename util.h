//---------------------------------------------------------------
//  util.h
//  nchess
//
//  Created by Mark Cornwell on 7/21/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//---------------------------------------------------------------

#ifndef nchess_util_h
#define nchess_util_h

#include <assert.h>

//#define assert( expr )

#include <mach/mach_time.h>

static const uint64_t NANOS_PER_USEC = 1000ULL;
static const uint64_t NANOS_PER_MILLISEC = 1000ULL * NANOS_PER_USEC;
static const uint64_t NANOS_PER_SEC = 1000ULL * NANOS_PER_MILLISEC;

static mach_timebase_info_data_t timebase_info;

//  nanosecond   one billionth of a second
//  microsecond  one millionth of a second
//  millisecond  one thousandth of a second
//

static unsigned long long abs_to_nanos(unsigned long long abs) {
    mach_timebase_info(&timebase_info);
    return abs * timebase_info.numer  / timebase_info.denom;
}

static float abs_to_milliseconds(unsigned int long long abs) {
    return abs_to_nanos(abs)/(float) 1000000.0;
}

typedef unsigned int boolean;

static inline void error(const char *msg) {
    printf("ERROR:   %s\n", msg);
    assert( 0 );  // break to debugger
}

static inline void warning(const char *msg) {
    printf("WARNING: %s\n", msg);
}

static inline boolean odd(unsigned int n) { return n & 01; }

#endif
