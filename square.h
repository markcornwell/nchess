//---------------------------------------------------------------
//  square.h
//  nchess
//
//  Created by Mark Cornwell on 7/6/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//---------------------------------------------------------------

#ifndef nchess_square_h
#define nchess_square_h

#include "util.h"

typedef unsigned char Square;

// Constants to name all 64 squares, and one more to name no square, NSQ.

// Square represented by 1 byte.  Lowest order 3 bits is file, next 3 bits is rank
// Octal makes it easy to read of rank and file
// Note: C++ octal numbers all begin with 0

static const Square
    a8=070, b8=071, c8=072, d8=073, e8=074, f8=075, g8=076, h8=077,
    a7=060, b7=061, c7=062, d7=063, e7=064, f7=065, g7=066, h7=067,
    a6=050, b6=051, c6=052, d6=053, e6=054, f6=055, g6=056, h6=057,
    a5=040, b5=041, c5=042, d5=043, e5=044, f5=045, g5=046, h5=047,
    a4=030, b4=031, c4=032, d4=033, e4=034, f4=035, g4=036, h4=037,
    a3=020, b3=021, c3=022, d3=023, e3=024, f3=025, g3=026, h3=027,
    a2=010, b2=011, c2=012, d2=013, e2=014, f2=015, g2=016, h2=017,
    a1=000, b1=001, c1=002, d1=003, e1=004, f1=005, g1=006, h1=007,
    NSQ=0100;

static inline boolean isSquare(unsigned char x) { return a1<=x && x<=h8; }

static inline Square rank (Square sq) { return (sq & 070) >> 3; }   // sq div 8
static inline Square file (Square sq) { return sq & 007; }          // sq mod 8

static inline Square squareAt(Square f, Square r) { return f + 8*r; }

// Navigation

// Now we use functions to lookup

Square sqfwd(Square sq);
Square sqbak(Square sq);
Square sqrgt(Square sq);
Square sqlft(Square sq);

static Square Fwd[65], Bak[65], Lft[65], Rgt[65], Dfl[65], Dfr[65], Dbl[65], Dbr[65];

/*
static inline Square fwd(Square sq) { return Fwd[sq]; }
static inline Square bak(Square sq) { return Bak[sq]; }
static inline Square rgt(Square sq) { return Rgt[sq]; }
static inline Square lft(Square sq) { return Lft[sq]; }
static inline Square dfr(Square sq) { return Dfr[sq]; }
static inline Square dfl(Square sq) { return Dfl[sq]; }
static inline Square dbr(Square sq) { return Dbr[sq]; }
static inline Square dbl(Square sq) { return Dbl[sq]; }
*/

/* Work around until I can figure out the above scheme */

static inline Square fwd(Square sq) { return sqfwd(sq); }
static inline Square bak(Square sq) { return sqbak(sq); }
static inline Square rgt(Square sq) { return sqrgt(sq); }
static inline Square lft(Square sq) { return sqlft(sq); }
static inline Square dfr(Square sq) { return sqfwd(sqrgt(sq)); }
static inline Square dfl(Square sq) { return sqfwd(sqlft(sq)); }
static inline Square dbr(Square sq) { return sqbak(sqrgt(sq)); }
static inline Square dbl(Square sq) { return sqbak(sqlft(sq)); }

// Externals

void square_init();
void square_test();

const char *squareString(Square);
void printSquare(Square);


#endif
