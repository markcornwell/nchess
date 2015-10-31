//-----------------------------------------------------------------------------------
//  move.h
//  nchess
//
//  Created by Mark Cornwell on 7/21/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//-----------------------------------------------------------------------------------

#ifndef nchess_move_h
#define nchess_move_h

#include "util.h"
#include "square.h"
#include "man.h"

//-----------------------------------------------------------------------------------
// Information we need to represent fits nicely into 4 bytes, a 32 bit integer
//
// from square    // 0 .. 63   (needs 2^6 - 1 or 6 bits)
// to square      // 0 .. 63   (needs 2^6 - 1 or 6 bits)
// captured       // man  (man captured - needs 4 bits or 3 since color redundant)
// flags          // en passant, pawn promote Q/B/N/R, check, mate, stalemate
//
// Expect that packing move into a single 4 byte integer is more efficient that
// accessing individual fields since compiler will use just one memory reference to
// get the integer.  Masks and shifts operate on a value already in a register which
// should be faster than accessing the fields of a struct.  Try to validate this
// benchmarking tests.
//-----------------------------------------------------------------------------------

typedef unsigned int Move;   // 4 bytes

void move_test();

static const unsigned int MV_FROM       = 0x0000003F;   // 6 bits 1-6;   7-8  unused
static const unsigned int MV_TO         = 0x00003F00;   // 6 bits 9-14; 15-16 unused
static const unsigned int MV_CAPTURE    = 0x000F0000;   // 4 bits 17-20  (man)

static const unsigned int MV_FLAGS      = 0x1FF00000;   // 9 bits 21-29

static const unsigned int MV_ENPASSANT  = 0x00100000;   // 1 bit  21

static const unsigned int MV_PROMOTE    = 0x00E00000;   // 3 bits 22-24
static const unsigned int MV_PROMOTE_KNIGHT = (KNIGHT << 21);
static const unsigned int MV_PROMOTE_BISHOP = (BISHOP << 21);
static const unsigned int MV_PROMOTE_ROOK   = (ROOK   << 21);
static const unsigned int MV_PROMOTE_QUEEN  = (QUEEN  << 21);

static const unsigned int MV_CASTLE           = 0x03000000;   // 2 bits 25-26
static const unsigned int MV_CASTLE_KINGSIDE  = 0x01000000;   // 1 bit  25
static const unsigned int MV_CASTLE_QUEENSIDE = 0x02000000;   // 1 bit  26

static const unsigned int MV_CHECK      = 0x04000000;   // 1 bit 27
static const unsigned int MV_STALEMATE  = 0x08000000;   // 1 bit 28
static const unsigned int MV_MATE       = 0x10000000;   // 1 bit 29

static inline Square    sqFrom(Move mv)           { return (mv & MV_FROM); }
static inline Square    sqTo(Move mv)             { return (mv & MV_TO) >> 8; }
static inline boolean   isCapture(Move mv)        { return (mv & MV_CAPTURE); }
static inline Man       manCaptured(Move mv)      { return (Man)((mv & MV_CAPTURE) >> 16); }

static inline boolean   isEnPassant(Move mv)      { return (mv & 0x00100000); }

static inline boolean   isPromote(Move mv)        { return (mv & 0x00E00000); }
static inline Kind      kindPromotedTo(Move mv)   { return ((mv & 0x00E00000) >> 21); }

static inline boolean   isCastle(Move mv)         { return (mv & MV_CASTLE); }
static inline boolean   isCastleKingside(Move mv) { return (mv & MV_CASTLE_KINGSIDE); }
static inline boolean   isCastleQueenside(Move mv){return  (mv & MV_CASTLE_QUEENSIDE); }
static inline boolean   isCheck(Move mv)          { return (mv & MV_CHECK); }
static inline boolean   isStalemate(Move mv)      { return (mv & MV_STALEMATE); }
static inline boolean   isMate(Move mv)           { return (mv & MV_MATE); }


static inline Move newMove(Square from, Square to, Man capture, unsigned int flags){
    return from | (to << 8)| (capture << 16) | flags;
}

void printMove(Move mv);   // human readable, e.g. e2-e4, d5xPe4
#endif

