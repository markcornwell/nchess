//---------------------------------------------------------------
//  test-trials.c
//  nchess
//
//  Created by Mark Cornwell on 8/1/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//---------------------------------------------------------------


#include <stdio.h>


//---------------------------------------------------------------------
//  This file needs to be type C++ Header inside XCode IDE
//---------------------------------------------------------------------


tfy_define(test_lone_wN) {
    tfy_name("test_lone_wN");
    tfy_purpose("verify trial moves of a lone knight at f3.");
    board_clear();
    addMan(f3,wN);
    printBoardMen();
    Movelist mvs;
    trials(&mvs,WHITE);
    printf("White to move\n");
    //printMoves(&mvs);
    mvs.print();
    // need automated check
    // - number of moves  mvs.len()
    // - find a particular move  mvs.find(Move m);
    tfy_assert(mvs.len()==8);
    tfy_assert(mvs.find(newMove(f3,g5,0,0)));
    tfy_assert(mvs.find(newMove(f3,e5,0,0)));
    tfy_assert(mvs.find(newMove(f3,h4,0,0)));
    tfy_assert(mvs.find(newMove(f3,h2,0,0)));
    tfy_assert(mvs.find(newMove(f3,g1,0,0)));
    tfy_assert(mvs.find(newMove(f3,e1,0,0)));
    tfy_assert(mvs.find(newMove(f3,d4,0,0)));
    tfy_assert(mvs.find(newMove(f3,d2,0,0)));
    tfy_assert(!mvs.find(newMove(f3,f5,0,0)));
    mvs.clear();
    tfy_pass;
}

tfy_define(test_initial_position) {
    tfy_name("test_initial_position");
    tfy_purpose("verify trial moves for White 1st move.");
    board_clear();
    board_setup();
    printBoardMen();
    Movelist mvs;
    trials(&mvs, WHITE);
    printf("White to move\n");
    printf("%i trial moves\n",mvs.len());
    //printMoves(&mvs);
    mvs.print();
    tfy_assert( mvs.len()==20 );
    tfy_assert( mvs.find(newMove(h2,h4,0,0)) );
    tfy_assert( mvs.find(newMove(h2,h3,0,0)) );
    tfy_assert( mvs.find(newMove(g2,g4,0,0)) );
    tfy_assert( mvs.find(newMove(g2,g3,0,0)) );
    tfy_assert( mvs.find(newMove(h2,h4,0,0)) );
    tfy_assert( mvs.find(newMove(h2,h3,0,0)) );
    tfy_assert( mvs.find(newMove(f2,f4,0,0)) );
    tfy_assert( mvs.find(newMove(f2,f3,0,0)) );
    tfy_assert( mvs.find(newMove(e2,e4,0,0)) );
    tfy_assert( mvs.find(newMove(e2,e3,0,0)) );
    tfy_assert( mvs.find(newMove(d2,d4,0,0)) );
    tfy_assert( mvs.find(newMove(d2,d3,0,0)) );
    tfy_assert( mvs.find(newMove(c2,c4,0,0)) );
    tfy_assert( mvs.find(newMove(c2,c3,0,0)) );
    tfy_assert( mvs.find(newMove(b2,b4,0,0)) );
    tfy_assert( mvs.find(newMove(b2,b3,0,0)) );
    tfy_assert( mvs.find(newMove(a2,a4,0,0)) );
    tfy_assert( mvs.find(newMove(a2,a3,0,0)) );
    tfy_assert( mvs.find(newMove(g1,h3,0,0)) );
    tfy_assert( mvs.find(newMove(g1,f3,0,0)) );
    tfy_assert( mvs.find(newMove(b1,c3,0,0)) );
    tfy_assert( mvs.find(newMove(b1,a3,0,0)) );
}

tfy_define(test_after_1_e4_e5) {
    tfy_name("test_after_white_e4");
    tfy_purpose("verify trial moves after 1 e4 e5.");
    board_clear();
    board_setup();
    delMan(e2);
    addMan(e4,wP);
    delMan(e7);
    addMan(e5,bP);
    printBoardMen();
    Movelist mvs;
    trials(&mvs,WHITE);
    printf("White to move\n");
    printf("%i trial moves\n",mvs.len());
    //printMoves(&mvs);
    mvs.print();
}

// test main

void test_trials_main() {
    test_init();
    test_add( test_lone_wN );
    test_add( test_initial_position );
    test_add( test_after_1_e4_e5 );
    test_runall();
    test_report();
}


