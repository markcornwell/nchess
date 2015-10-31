//-------------------------------------------------------------
//  attacks.c
//  nchess
//
//  Created by Mark Cornwell on 8/5/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//-------------------------------------------------------------

#include <stdio.h>
#include "attacks.h"
#include "board.h"

boolean attack_N(Square sq0, Color c) {
    assert( manAt(NSQ)==0 );
    assert( NSQ != bN );
    Man cN = (KNIGHT | c);
    if (manAt(fwd(dfr(sq0)))==cN) return 1;
    else if (manAt(fwd(dfl(sq0)))==cN) return 1;
    else if (manAt(rgt(dfr(sq0)))==cN) return 1;
    else if (manAt(rgt(dbr(sq0)))==cN) return 1;
    else if (manAt(bak(dbr(sq0)))==cN) return 1;
    else if (manAt(bak(dbl(sq0)))==cN) return 1;
    else if (manAt(lft(dfl(sq0)))==cN) return 1;
    else if (manAt(lft(dbl(sq0)))==cN) return 1;
    else return 0;
}

boolean attack_RQ(Square sq, Color c) {
    Man cR = (ROOK | c);
    Man cQ = (QUEEN | c);
    for (int i=fwd(sq); i!=NSQ; i=fwd(i)) {
        if (manAt(i)==cQ || manAt(i)==cR) return 1;
        else if (manAt(i)) break;
    }
    for (int i=rgt(sq); i!=NSQ; i=rgt(i)) {
        if (manAt(i)==cQ || manAt(i)==cR) return 1;
        else if (manAt(i)) break;
    }
    for (int i=bak(sq); i!=NSQ; i=bak(i)) {
        if (manAt(i)==cQ || manAt(i)==cR) return 1;
        else if (manAt(i)) break;
    }
    for (int i=lft(sq); i!=NSQ; i=lft(i)) {
        if (manAt(i)==cQ || manAt(i)==cR) return 1;
        else if (manAt(i)) break;
    }
    return 0;
}

boolean attack_BQ(Square sq, Color c) {
    Man cB = (BISHOP | c);
    Man cQ = (QUEEN | c);
    for (int i=dfr(sq); i!=NSQ; i=dfr(i)) {
        if (manAt(i)==cQ || manAt(i)==cB) return 1;
        else if (manAt(i)) break;
    }
    for (int i=dfl(sq); i!=NSQ; i=dfl(i)) {
        if (manAt(i)==cQ || manAt(i)==cB) return 1;
        else if (manAt(i)) break;
    }
    for (int i=dbr(sq); i!=NSQ; i=dbr(i)) {
        if (manAt(i)==cQ || manAt(i)==cB) return 1;
        else if (manAt(i)) break;
    }
    for (int i=dbl(sq); i!=NSQ; i=dbl(i)) {
        if (manAt(i)==cQ || manAt(i)==cB) return 1;
        else if (manAt(i)) break;
    }
    return 0;
}

boolean attack_P(Square sq, Color c) {
    if (c==WHITE && (manAt(dbl(sq))==wP || manAt(dbr(sq))==wP)) return 1;
    if (c==BLACK && (manAt(dfl(sq))==bP || manAt(dfr(sq))==bP)) return 1;
    return 0;
}

boolean attack_K(Square sq, Color c) {
    assert( manAt(NSQ)==0 );
    Man cK = (KING | c);
    if (manAt(fwd(sq))==cK) return 1;
    if (manAt(dfr(sq))==cK) return 1;
    if (manAt(rgt(sq))==cK) return 1;
    if (manAt(dbr(sq))==cK) return 1;
    if (manAt(bak(sq))==cK) return 1;
    if (manAt(dbl(sq))==cK) return 1;
    if (manAt(lft(sq))==cK) return 1;
    if (manAt(dfl(sq))==cK) return 1;
    return 0;
}

boolean attack(Square sq, Color c) {
    return attack_N(sq,c)
        || attack_RQ(sq,c)
        || attack_BQ(sq,c)
        || attack_P(sq,c)
        || attack_K(sq,c);
}

void attack_init() {
    // nothing needed, yet
}

void attack_test() {
    printf("---------------------------------- begin attack test\n");
    board_clear();
    
    // white pawn attacks
    addMan(e4,wP);
    printBoardMen();
    assert(attack(a1,WHITE)==0);
    assert(attack(d5,WHITE));
    assert(attack(f5,WHITE));
    
    // black pawn attacks
    addMan(e5,bP);
    printBoardMen();
    assert(attack(a1,BLACK)==0);
    assert(attack(d4,BLACK));
    assert(attack(f4,BLACK));
    
    //white knight attacks
    addMan(f3,wN);
    printBoardMen();
    assert(attack(g1,WHITE));
    assert(attack(e1,WHITE));
    assert(attack(d2,WHITE));
    assert(attack(d4,WHITE));
    assert(attack(e5,WHITE));
    assert(attack(g5,WHITE));
    assert(attack(h4,WHITE));
    assert(attack(h2,WHITE));
    
    //black bishop attack
    addMan(g6,bB);
    printBoardMen();
    assert(attack(f5,BLACK));
    assert(attack(e4,BLACK));
    assert(!attack(d3,BLACK));
    
    //white rook attack
    addMan(b5,wR);
    printBoardMen();
    assert(attack(e5,WHITE));
    assert(!attack(h5,WHITE));
    assert(attack(b1,WHITE));
    assert(attack(a5,WHITE));
    
    printf("----------------------------------   end attack test\n");
}

