//-----------------------------------------------------------------------
//  board.h
//  nchess
//
//  Created by Mark Cornwell on 7/16/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//
//
// NOTE: board knows nothing about the module Move.  Keep it that way.
//       For mods requiring knowledge Move go up to trials.
//-----------------------------------------------------------------------

#ifndef nchess_board_h
#define nchess_board_h

#include "man.h"
#include "square.h"
#include "movelist.h"

void board_init();  // startup initialization
void board_clear(); // clear board of all men
void board_setup(); // setup pieces for new game

Man manAt(Square sq);
void addMan(Square sq, Man man);
void delMan(Square sq);

boolean occupied(Square);
boolean unoccupied(Square);


void forWhiteMen (void fcn(Square));
void forBlackMen (void fcn(Square));

int forWhiteMen (int fcn(Square));
int forBlackMen (int fcn(Square));


void forWhiteMen (Movelist *,void fcn(Movelist *, Square));
void forBlackMen (Movelist *,void fcn(Movelist *, Square));

void printBoard();
void printMen();
void printBoardMen();

void board_test();  // unit tests
void verifyBoard(); // for debugging

#endif
