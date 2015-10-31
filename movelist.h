//-------------------------------------------------------------
//  movelist.h
//  nchess
//
//  Created by Mark Cornwell on 7/26/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//-------------------------------------------------------------

#ifndef nchess_movelist_h
#define nchess_movelist_h

#include "move.h"

void movelist_test();

/*** scheme for static inlines sharing variable in headers isn't working ****/


static const unsigned int MVLISTMAX = 218;
// max nbr of pseudo-moves thought to be 218
// https://chessprogramming.wikispaces.com/Encoding+Moves#cite_note-1

//extern Move mvlist[MVLISTMAX];
//extern unsigned int mvtop;

// each stackframe is going to cost 1K.  Is this ok??
struct Movelist {
    Move mvlist[MVLISTMAX];
    int mvtop;
    void init() {
        mvtop = 0;
    }
    void clear() {
        mvtop = 0;
    }
    unsigned int len() {
        return mvtop;
    }
    Move get(unsigned int i) {
        assert ( i < mvtop );
        return mvlist[i];
    }
    void push(Move mv) {
        assert ( mvtop+1 < MVLISTMAX );
        mvlist[mvtop++] = mv;
    }
    Move pop() {
        assert ( mvtop > 0 );
        return mvlist[--mvtop];
    }
    boolean empty() {
        return mvtop == 0;
    }
    boolean find(Move m) { // for testing only: O(n)
        for (int i=0; i<mvtop; i++) {
            if (mvlist[i]==m) return 1;
        }
        return 0;
    }
    Move findMove(Square sq0, Square sq1) { // for outer loops only -- O(n)  *** NEW ***
        for (int i=0; i<mvtop; i++) {
            if (sq0==sqFrom(mvlist[i]) && sq1==sqTo(mvlist[i])) return mvlist[i];
        }
        return 0;
    }
    void print() {
        for( int i=0; i<mvtop; i++) {
            printMove(mvlist[i]);
            printf("\n");
        }
    }
};


static inline void movelist_init() {
    // mvs_current = (struct Movelist *) malloc(sizeof(struct Movelist));
};

#endif
