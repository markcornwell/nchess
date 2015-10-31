//---------------------------------------------------------------
//  alphabeta.h
//  nchess
//
//  Created by Mark Cornwell on 8/6/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//---------------------------------------------------------------

#include "config.h"

#ifndef nchess_alphabeta_h
#define nchess_alphabeta_h

extern struct Movelist toplevel_mvs;
extern unsigned int toplevel_score[MVLISTMAX];
extern unsigned int depth;

// Gameplay
void new_game();

void mv_make(Move mv);
void mv_unmake(Move mv);
Move bestMove();
Color colorToMove();

void show_history();

// Move search
int alphabetaMax(int alpha, int beta, int depthleft);
int alphabetaMin(int alpha, int beta, int depthleft);

void alphabeta_init();
void alphabeta_test();

#endif
