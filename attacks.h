//---------------------------------------------------------------
//  attacks.h
//  nchess
//
//  Created by Mark Cornwell on 8/5/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//---------------------------------------------------------------

#ifndef nchess_attacks_h
#define nchess_attacks_h
#include "util.h"
#include "square.h"
#include "man.h"

boolean attack(Square sq, Color c);

void attack_init();
void attack_test();

#endif
