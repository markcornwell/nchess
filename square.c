//------------------------------------------------------------------------
//  square.c
//  nchess
//
//  Created by Mark Cornwell on 7/6/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//------------------------------------------------------------------------

#include <stdio.h>
#include "square.h"

// For movements fwd, bak, rgt, lft, dfr, dfl, dbr, dbl

Square sqfwd(Square sq) {
    if (sq == NSQ) return NSQ;
    else if (rank(sq) == 7) return NSQ;
    else return sq+8;
}

Square sqbak(Square sq) {
    if (sq==NSQ) return NSQ;
    else if (rank(sq) == 0) return NSQ;
    else return sq-8;
}

Square sqrgt(Square sq) {
    if (sq==NSQ) return NSQ;
    else if (file(sq) == 7) return NSQ;
    else return sq+1;
}

Square sqlft(Square sq) {
    if (sq==NSQ) return NSQ;
    else if (file(sq) == 0) return NSQ;
    else return sq-1;
}

//-----------------------------------------------------------------------------
// Optimization: save the cost of two compares and one add by precomputing
// these values in 8 different tables.  Then use the square as offset
// into the table.  Memory is cheap, cycles are dear.
//-----------------------------------------------------------------------------

void square_init () {
    for(Square sq = 0; sq <= NSQ ; sq++) {
        Fwd[sq] = sqfwd(sq);
        Bak[sq] = sqbak(sq);
        Rgt[sq] = sqrgt(sq);
        Lft[sq] = sqlft(sq);
        Dfl[sq] = sqfwd(sqlft(sq));
        Dfr[sq] = sqfwd(sqrgt(sq));
        Dbl[sq] = sqbak(sqlft(sq));
        Dbr[sq] = sqbak(sqrgt(sq));
    }
}


const char *sqName[65]={"a1","b1","c1","d1","e1","f1","g1","h1"
                       ,"a2","b2","c2","d2","e2","f2","g2","h2"
                       ,"a3","b3","c3","d3","e3","f3","g3","h3"
                       ,"a4","b4","c4","d4","e4","f4","g4","h4"
                       ,"a5","b5","c5","d5","e5","f5","g5","h5"
                       ,"a6","b6","c6","d6","e6","f6","g6","h6"
                       ,"a7","b7","c7","d7","e7","f7","g7","h7"
                       ,"a8","b8","c8","d8","e8","f8","g8","h8"
                       ,"NS"
                       };

void printSquare(Square sq) {
    printf("%s", sqName[sq]);
}

const char *squareString(Square sq) {
    return sqName[sq];
}

//-----------------------------------------------------------------
// A simple test is to print out the tables from the specification
//-----------------------------------------------------------------


void sqTestFile(Square startsq) {
    printf("%c-file\n",file(startsq)+'a');
    printf("Sq R F fwd bak rgt lft dfl dfr dbl dbr\n");
    for(unsigned char sq=startsq; sq != NSQ; sq=fwd(sq)) {
        printf("%s %c %c %s  %s  %s  %s  %s  %s  %s  %s\n",
               sqName[sq],
               // note: rank(sq)+'0' idiom to convert small unsigned value to its ascii digit
               rank(sq)+'0',
               file(sq)+'0',
               sqName[fwd(sq)],
               sqName[bak(sq)],
               sqName[rgt(sq)],
               sqName[lft(sq)],
               sqName[dfl(sq)],
               sqName[dfr(sq)],
               sqName[dbl(sq)],
               sqName[dbr(sq)]);
    }
}

extern void square_test() {
    printf("---------------------------------- square test\n");
    square_init();
    sqTestFile(a1);
    sqTestFile(b1);
    sqTestFile(c1);
    sqTestFile(d1);
    sqTestFile(e1);
    sqTestFile(f1);
    sqTestFile(g1);
    sqTestFile(h1);
    
    assert(fwd(a1)==a2);
    assert(dfr(e4)==f5);
    
    printf("----------------------------------end square test\n\n");
}

