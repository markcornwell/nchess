//---------------------------------------------------------------
//  test-board.c
//  nchess
//
//  Created by Mark Cornwell on 7/29/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//
// IMPORTANT: Set Type to C++ Header in XCode GUI
//---------------------------------------------------------------

#include <stdio.h>
#include "test.h"

#include "square.h"
#include "man.h"
#include "board.h"

//
// Regression testng
//

tfy_define(test_manAt) {
    tfy_name("test_manAt");
    //printBoard();
    board_clear();
    for (int i=a1; i<=h8; i++) {
        tfy_assert(manAt(i)==0);
    }
    tfy_assert(kind(wR)==ROOK);
    tfy_assert(color(wR)==WHITE);
    
    addMan(a1,wR);
    
    tfy_assert(kind(manAt(a1))==ROOK);
    tfy_assert(color(manAt(a1))==WHITE);
    tfy_assert(manAt(a1)==wR);
    
    delMan(a1);
    tfy_assert(manAt(a1)==0);
}


tfy_define(test_board_clear) {
    tfy_name("test_board_clear");
    //printf("board_clear\n");
    board_clear();
    board_clear();
    board_clear();
    for (int i=0; i<=63; i++) tfy_assert(manAt(i)==0);    
    addMan(e4,wP);
    for (int i=0; i<=63; i++) {
        if (i!=e4) {
            tfy_assert(manAt(i)==0);
        }
        else {
            tfy_assert(manAt(i)==wP);
        }
    }

    tfy_assert( manAt(e4)==wP );
    verifyBoard();
    board_clear();
    tfy_assert( manAt(e4)==0 );
    for (int i=0; i<=63; i++) tfy_assert(manAt(i)==0);
}

tfy_define(test_addMan) {
    tfy_name("test_addMan");
    addMan(a1,wR);
    addMan(b1,wN);
    addMan(c1,wB);
    addMan(d1,wQ);
    addMan(e1,wK);
    addMan(f1,wB);
    addMan(g1,wN);
    addMan(h1,wR);
    for (int i=a2; i<=h2; i++) addMan(i,wP);
    addMan(a8,bR);
    addMan(b8,bN);
    addMan(c8,bB);
    addMan(d8,bQ);
    addMan(e8,bK);
    addMan(f8,bB);
    addMan(g8,bN);
    addMan(h8,bR);
    for (int i=a7; i<=h7; i++) addMan(i,bP);
    printBoard();
    tfy_assert( manAt(a1)==wR );
    tfy_assert( manAt(h8)==bR );
    board_clear();
}

tfy_define(test_delMan) {
    tfy_name("test_delMan");
    addMan(a1,wR);
    addMan(b1,wN);
    addMan(c1,wB);
    addMan(d1,wQ);
    addMan(e1,wK);
    addMan(f1,wB);
    addMan(g1,wN);
    addMan(h1,wR);
    for (int i=a2; i<=h2; i++) addMan(i,wP);
    addMan(a8,bR);
    addMan(b8,bN);
    addMan(c8,bB);
    addMan(d8,bQ);
    addMan(e8,bK);
    addMan(f8,bB);
    addMan(g8,bN);
    addMan(h8,bR);
    for (int i=a7; i<=h7; i++) addMan(i,bP);
    
    delMan(e2);
    addMan(e4,wP);
    delMan(e7);
    addMan(e6,bP);
    delMan(g1);
    addMan(f3,wN);
    delMan(b8);
    addMan(c6,bN);
    
    printBoard();

    delMan(a1);
    delMan(h8);
    tfy_assert( manAt(a1)==0 );
    tfy_assert( manAt(h8)==0 );
    tfy_assert( manAt(e2)==0 );
    tfy_assert( manAt(e7)==0 );
    tfy_assert( manAt(b8)==0 );
    tfy_assert( manAt(g1)==0 );
    
    board_clear();
}

tfy_define(test_unoccupied) {
    tfy_name("test_unoccupied");
    board_clear();
    for (int i=0; i<=63; i++) tfy_assert(manAt(i)==0);
    for (int i=0; i<=63; i++) tfy_assert(unoccupied(i));
    for (int i=0; i<=63; i++) tfy_assert(!occupied(i));
    addMan(e5,wQ);
    tfy_assert(occupied(e5));
    tfy_assert(unoccupied(e3));
    board_clear();
}


tfy_define(test_forWhiteMen) {
    tfy_name("test_forWhiteMen");
    board_clear();
    addMan(a1,wR);
    addMan(b1,wN);
    addMan(c1,wB);
    addMan(d1,wQ);
    addMan(e1,wK);
    addMan(f1,wB);
    addMan(g1,wN);
    addMan(h1,wR);
    for (int i=a2; i<=h2; i++) addMan(i,wP);
    forWhiteMen(printSquare);
    printf("\n");
    board_clear();
}

tfy_define(test_forBlackMen) {
    tfy_name("test_forBlackMen");
    addMan(a8,bR);
    addMan(b8,bN);
    addMan(c8,bB);
    addMan(d8,bQ);
    addMan(e8,bK);
    addMan(f8,bB);
    addMan(g8,bN);
    addMan(h8,bR);
    for (int i=a7; i<=h7; i++) addMan(i,bP);
    forBlackMen(printSquare);
    printf("\n");
    board_clear();  
}

tfy_define(test_printBoardMen) {
    tfy_name("test_printBoardMen");
    addMan(a1,wR);
    addMan(b1,wN);
    addMan(c1,wB);
    addMan(d1,wQ);
    addMan(e1,wK);
    addMan(f1,wB);
    addMan(g1,wN);
    addMan(h1,wR);
    for (int i=a2; i<=h2; i++) addMan(i,wP);
    addMan(a8,bR);
    addMan(b8,bN);
    addMan(c8,bB);
    addMan(d8,bQ);
    addMan(e8,bK);
    addMan(f8,bB);
    addMan(g8,bN);
    addMan(h8,bR);
    for (int i=a7; i<=h7; i++) addMan(i,bP);
    printBoardMen();
    board_clear();
}

// test main

void test_board_main() {
    test_init();
    test_add(test_manAt);
    test_add(test_board_clear);
    test_add(test_addMan);
    test_add(test_delMan);
    test_add(test_unoccupied);
    test_add(test_forWhiteMen);
    test_add(test_forBlackMen);
    test_add(test_printBoardMen);
    test_runall();
    test_report();
}


