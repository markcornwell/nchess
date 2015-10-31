//---------------------------------------------------------------
//  trials.h
//  nchess
//
//  Created by Mark Cornwell on 7/27/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//---------------------------------------------------------------

#ifndef nchess_trials_h
#define nchess_trials_h

#include "man.h"
#include "square.h"
#include "board.h"
#include "movelist.h"
#include "attacks.h"


// these get updated on initial moves of kings and rooks; and whenever castling
// When =0 white can castle; if not =0, holds half move white lost that privilege

extern unsigned int whiteOO;
extern unsigned int whiteOOO;
extern unsigned int blackOO;
extern unsigned int blackOOO;


void trials(Movelist *mvs, Color colorToMove);

void trials_init();
void trials_test();

#endif

