//---------------------------------------------------------------
//  test-man.c
//  nchess
//
//  Created by Mark Cornwell on 7/29/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//---------------------------------------------------------------

#include <stdio.h>
#include "test.h"
#include "man.h"

// test cases


tfy_define(man_white_piece_contants) {
    tfy_name("white pieces constants");
    tfy_assert(color(wP)==WHITE);
    tfy_assert(kind(wP)==PAWN);
    tfy_assert(color(wN)==WHITE);
    tfy_assert(kind(wN)==KNIGHT);
    tfy_assert(color(wB)==WHITE);
    tfy_assert(kind(wB)==BISHOP);
    tfy_assert(color(wR)==WHITE);
    tfy_assert(kind(wR)==ROOK);
    tfy_assert(color(wQ)==WHITE);
    tfy_assert(kind(wQ)==QUEEN);
    tfy_assert(color(wK)==WHITE);
    tfy_assert(kind(wK)==KING);
    tfy_assert(kind(wK)!=QUEEN);
    tfy_assert(color(wK)!=BLACK);
    tfy_assert(isBlack(bK));
    tfy_assert(!isBlack(wR));
}


tfy_define(man_black_piece_constants) {
    tfy_name("man black piece constants");
    tfy_assert(color(bP)==BLACK);
    tfy_assert(kind(bP)==PAWN);
    tfy_assert(color(bN)==BLACK);
    tfy_assert(kind(bN)==KNIGHT);
    tfy_assert(color(bB)==BLACK);
    tfy_assert(kind(bB)==BISHOP);
    tfy_assert(color(bR)==BLACK);
    tfy_assert(kind(bR)==ROOK);
    tfy_assert(color(bQ)==BLACK);
    tfy_assert(kind(bQ)==QUEEN);
    tfy_assert(color(bK)==BLACK);
    tfy_assert(kind(bK)==KING);
    tfy_assert(kind(bK)!=QUEEN);
    tfy_assert(color(bK)!=WHITE);
    tfy_assert(isBlack(bP));
    tfy_assert(!isBlack(wN));
}

tfy_define(man_isMan) {
    tfy_name("test isMan");
    tfy_assert(isMan(wP));
    tfy_assert(isMan(bK));
    tfy_assert(isMan(wQ));
    tfy_assert(!isMan(0));
}

// test main

void test_man_main() {
    test_init();
    test_add(man_white_piece_contants);
    test_add(man_black_piece_constants);
    test_add(man_isMan);
    test_runall();
    test_report();
}


