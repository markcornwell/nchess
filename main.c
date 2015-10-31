//-----------------------------------------------------------------
//  main.c
//  nchess
//
//  Created by Mark Cornwell on 7/6/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//-----------------------------------------------------------------


#include <stdio.h>
#include "util.h"
#include "square.h"
#include "man.h"
#include "board.h"
#include "move.h"
#include "movelist.h"
#include "trials.h"
#include "attacks.h"
#include "alphabeta.h"
#include "control.h"

#define RUN_TESTS

#ifdef RUN_TESTS
#include "test.h"
#include "test-example.c"
#include "test-man.c"
#include "test-board.c"
#include "test-trials.c"
#endif


int main(int argc, const char * argv[])
{

    // insert code here...
    printf("Welcome to nchess\n");
    
    // initialize all modules
    square_init();
    man_init();
    board_init();
    movelist_init();
    trials_init();
    attack_init();
    alphabeta_init();
    
    // run unit tests

    square_test();
    man_test();
    board_test();
    move_test();
    movelist_test();
    trials_test();
    attack_test();
    alphabeta_test();
    
    // run test harness tests
    test_example_main();
    test_man_main();
    test_board_main();
    test_trials_main();
    //test_attack_main();
    
    //start toplevel
    int retval = toplevel();
    
    return retval;
}

