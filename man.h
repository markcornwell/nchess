//-----------------------------------------------------------------------
//  man.h
//  nchess
//
//  Created by Mark Cornwell on 7/15/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//-----------------------------------------------------------------------

#ifndef nchess_man_h
#define nchess_man_h

//-----------------------------------------------------------------------
// An architectural design goal of this module is to hide the encoding
// of chess men. Some things in the header file because we want to inline
// functions, but they are supposed to be secrets of this module.
// Rule of thumb: don't rely on the right hand side of any constant
// or function declarations you see in the header file. They are secrets
// subject to change.
//-----------------------------------------------------------------------

#include "util.h"

//-----------------------------------------------------------------------
// Kind is 3 bits - the following encoding is a secret
//   s + x
//   0 0 1   P  01
//   0 1 0   N  02
//   0 1 1   K  03
//   1 0 1   B  05
//   1 1 0   R  06
//   1 1 1   Q  07
//-----------------------------------------------------------------------

typedef unsigned char Kind, Color, Man;

static const Kind PAWN=1, KNIGHT=2, KING=3, BISHOP=5, ROOK=6, QUEEN=7;

static inline char sliding_piece(Kind k) { return k & 4; }


// defined if a sliding_piece
static inline char slides_like_rook(Kind k) { return k & 2; }
static inline char slides_like_bishop(Kind k) {return k & 1; }

static const Color WHITE = 0, BLACK= 8;

#define white(k)    (k)
#define black(k)    (k|8)

// useful constants for pieces
static const Man
   wP=white(PAWN)    , bP=black(PAWN),
   wN=white(KNIGHT)  , bN=black(KNIGHT),
   wB=white(BISHOP)  , bB=black(BISHOP),
   wR=white(ROOK)    , bR=black(ROOK),
   wQ=white(QUEEN)   , bQ=black(QUEEN),
   wK=white(KING)    , bK=black(KING);

#undef white
#undef black

// defined if m is non-zero
static inline boolean isMan(unsigned char x) { return wP<=x && x<=bQ && x!=4 && x!=12; }

static inline Color color(Man m)         { return 8 & m; }
static inline Kind  kind(Man m)          { return 7 & m; }
static inline Man   man(Color c, Kind k) { return c & k; }

static inline boolean isBlack(Man m)     { return color(m); }


const char *man_string(Man);

void printKind(Kind);
void printColor(Color);
void printMan(Man);

void man_test();
void man_init();

#endif
