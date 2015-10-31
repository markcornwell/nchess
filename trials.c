//-----------------------------------------------------------------------
//  trials.c
//  nchess
//
//  Created by Mark Cornwell on 7/27/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//
//
//  Function: Populate the movelist with a pseudo-legal moves given a
//            board position and color to move.
//
//  Secrets:  How trial moves are computed.  Internal selection of data
//            structures and algorithms for pseudo-legal move generation.
//-----------------------------------------------------------------------

// TBD - en passant

#include <stdio.h>
#include "trials.h"

unsigned int whiteOO  = 0;
unsigned int whiteOOO = 0;
unsigned int blackOO  = 0;
unsigned int blackOOO = 0;

void trials_init() {
    square_init();
    assert(fwd(a1)==a2);  // sanity check
}

// Knight Moves

// Note: manAt should be a static inline for speed

static inline void mv1(Movelist *mvs, Square sq0, Square sqN) {
    if (sqN == NSQ)
        return;
    else if (manAt(sqN) == 0) {
        mvs->push(newMove(sq0,sqN,0,0));
    }
    else if (color(manAt(sqN)) != color(manAt(sq0))) {
        mvs->push(newMove(sq0,sqN, manAt(sqN),0));
    }
}

static inline void knightmvs(Movelist *mvs,Square sq0) {
    mv1(mvs,sq0,fwd(dfr(sq0)));
    mv1(mvs,sq0,fwd(dfl(sq0)));
    mv1(mvs,sq0,rgt(dfr(sq0)));
    mv1(mvs,sq0,rgt(dbr(sq0)));
    mv1(mvs,sq0,bak(dbr(sq0)));
    mv1(mvs,sq0,bak(dbl(sq0)));
    mv1(mvs,sq0,lft(dfl(sq0)));
    mv1(mvs,sq0,lft(dbl(sq0)));
}

// King Moves

static inline void castle(Movelist *mvs,Square sq0) {
    assert( kind(manAt(sq0))==KING );
    
    if ( sq0 == e1 && manAt(sq0)==wK ) {
        
        if ( whiteOO==0
            && manAt(f1)==0
            && manAt(g1)==0
            && manAt(h1)==wR
            && !attack(e1,BLACK)
            && !attack(f1,BLACK)
            && !attack(g1,BLACK)
            )
            mvs->push(newMove(e1,g1,0,MV_CASTLE_KINGSIDE));
        
        if ( whiteOOO == 0
            && manAt(d1)==0
            && manAt(c1)==0
            && manAt(b1)==0
            && manAt(a1) == wR
            && !attack(e1,BLACK)
            && !attack(d1,BLACK)
            && !attack(c1,BLACK)
            )
            mvs->push(newMove(e1,c1,0,MV_CASTLE_QUEENSIDE));
    }
    
    if ( sq0 == e8 && manAt(sq0)==bK ) {
        
        if ( blackOO == 0
            && manAt(f8)==0
            && manAt(g8)==0
            && manAt(h8)==bR
            && !attack(e8,WHITE)
            && !attack(f8,WHITE)
            && !attack(g8,WHITE)
            )
            mvs->push(newMove(e8,g8,0,MV_CASTLE_KINGSIDE));
        
        if ( blackOOO == 0
            && manAt(d8)==0
            && manAt(c8)==0
            && manAt(b8)==0
            && manAt(a8) == bR
            && !attack(e8,WHITE)
            && !attack(d8,WHITE)
            && !attack(c8,WHITE)
            )
            mvs->push(newMove(e8,c8,0,MV_CASTLE_QUEENSIDE));
    }
}

static inline void kingmvs(Movelist *mvs,Square sq0) {
    mv1(mvs,sq0,fwd(sq0));
    mv1(mvs,sq0,dfr(sq0));
    mv1(mvs,sq0,rgt(sq0));
    mv1(mvs,sq0,dbr(sq0));
    mv1(mvs,sq0,bak(sq0));
    mv1(mvs,sq0,dbl(sq0));
    mv1(mvs,sq0,lft(sq0));
    mv1(mvs,sq0,dfl(sq0));
    castle(mvs,sq0);
}

// Pawn Moves

static inline void wP_mvs(Movelist *mvs,Square sq0) {

    assert( rank(sq0) != 7 );
    assert (rank(sq0) != 0 );
    
    // two squares fwd
    if ( (rank(sq0)==1) &&  (manAt(fwd(sq0))==0) && (manAt(fwd(fwd(sq0)))==0))
        mvs->push(newMove(sq0, fwd(fwd(sq0)), 0, 0));
    

    // other non promoting moves
    if (rank(sq0)<6) {
        
        // one square fwd
        if( manAt(fwd(sq0))==0 )
            mvs->push(newMove(sq0, fwd(sq0), 0, 0));

        // capture diagonally left
        if (file(sq0)>0 && manAt(dfl(sq0)) && (color(manAt(dfl(sq0))) != WHITE) )
            mvs->push( newMove(sq0, dfl(sq0), manAt(dfl(sq0)), 0) );
        
        // capture diagonally right
        if (file(sq0)<7 && manAt(dfr(sq0)) && (color(manAt(dfr(sq0))) != WHITE) )
            mvs->push( newMove(sq0, dfr(sq0), manAt(dfr(sq0)), 0) );
    }
    
    // promoting moves
    if (rank(sq0)==6 ) {

        // one square fwd
        if( manAt(fwd(sq0))==0 ) {
            mvs->push(newMove(sq0, fwd(sq0), 0, MV_PROMOTE_QUEEN));
            mvs->push(newMove(sq0, fwd(sq0), 0, MV_PROMOTE_ROOK));
            mvs->push(newMove(sq0, fwd(sq0), 0, MV_PROMOTE_BISHOP));
            mvs->push(newMove(sq0, fwd(sq0), 0, MV_PROMOTE_KNIGHT));
        }

        // capture diagonally left
        if (file(sq0)>0 && manAt(dfl(sq0)) && (color(manAt(dfl(sq0))) != WHITE) ) {
            mvs->push( newMove(sq0, dfl(sq0), manAt(dfl(sq0)), MV_PROMOTE_QUEEN) );
            mvs->push( newMove(sq0, dfl(sq0), manAt(dfl(sq0)), MV_PROMOTE_ROOK) );
            mvs->push( newMove(sq0, dfl(sq0), manAt(dfl(sq0)), MV_PROMOTE_BISHOP) );
            mvs->push( newMove(sq0, dfl(sq0), manAt(dfl(sq0)), MV_PROMOTE_KNIGHT) );
        }

        // capture diagonally right
        if (file(sq0)<7 && manAt(dfr(sq0)) && (color(manAt(dfr(sq0))) != WHITE) ) {
            mvs->push( newMove(sq0, dfr(sq0), manAt(dfr(sq0)), MV_PROMOTE_QUEEN) );
            mvs->push( newMove(sq0, dfr(sq0), manAt(dfr(sq0)), MV_PROMOTE_ROOK) );
            mvs->push( newMove(sq0, dfr(sq0), manAt(dfr(sq0)), MV_PROMOTE_BISHOP) );
            mvs->push( newMove(sq0, dfr(sq0), manAt(dfr(sq0)), MV_PROMOTE_KNIGHT) );
        }
    }
}

static inline void bP_mvs(Movelist *mvs,Square sq0) {
    assert( rank(sq0) != 7 );
    assert (rank(sq0) != 0 );
    
    // two squares bak
    if ( (rank(sq0)==6) &&  (manAt(bak(sq0))==0) && (manAt(bak(bak(sq0)))==0))
        mvs->push(newMove(sq0, bak(bak(sq0)), 0, 0));
    
    
    // other non promoting moves
    if (rank(sq0)>1) {
        
        // one square bak
        if( manAt(bak(sq0))==0 )
            mvs->push(newMove(sq0, bak(sq0), 0, 0));
        
        // capture diagonally left
        if (file(sq0)>0 && manAt(dbl(sq0)) && (color(manAt(dbl(sq0))) != BLACK) )
            mvs->push( newMove(sq0, dbl(sq0), manAt(dbl(sq0)), 0) );
        
        // capture diagonally right
        if (file(sq0)<7 && manAt(dbr(sq0)) && (color(manAt(dbr(sq0))) != BLACK) )
            mvs->push( newMove(sq0, dbr(sq0), manAt(dbr(sq0)), 0) );
    }
    
    // promoting moves
    if (rank(sq0)==1 ) {
        
        // one square bak
        if( manAt(bak(sq0))==0 ) {
            mvs->push(newMove(sq0, bak(sq0), 0, MV_PROMOTE_QUEEN));
            mvs->push(newMove(sq0, bak(sq0), 0, MV_PROMOTE_ROOK));
            mvs->push(newMove(sq0, bak(sq0), 0, MV_PROMOTE_BISHOP));
            mvs->push(newMove(sq0, bak(sq0), 0, MV_PROMOTE_KNIGHT));
        }
        
        // capture diagonally left
        if (file(sq0)>0 && manAt(dbl(sq0)) && (color(manAt(dbl(sq0))) != BLACK) ) {
            mvs->push( newMove(sq0, dbl(sq0), manAt(dbl(sq0)), MV_PROMOTE_QUEEN) );
            mvs->push( newMove(sq0, dbl(sq0), manAt(dbl(sq0)), MV_PROMOTE_ROOK) );
            mvs->push( newMove(sq0, dbl(sq0), manAt(dbl(sq0)), MV_PROMOTE_BISHOP) );
            mvs->push( newMove(sq0, dbl(sq0), manAt(dbl(sq0)), MV_PROMOTE_KNIGHT) );
        }
        
        // capture diagonally right
        if (file(sq0)<7 && manAt(dbr(sq0)) && (color(manAt(dbr(sq0))) != BLACK) ) {
            mvs->push( newMove(sq0, dbr(sq0), manAt(dbr(sq0)), MV_PROMOTE_QUEEN) );
            mvs->push( newMove(sq0, dbr(sq0), manAt(dbr(sq0)), MV_PROMOTE_ROOK) );
            mvs->push( newMove(sq0, dbr(sq0), manAt(dbr(sq0)), MV_PROMOTE_BISHOP) );
            mvs->push( newMove(sq0, dbr(sq0), manAt(dbr(sq0)), MV_PROMOTE_KNIGHT) );
        }
    }
    
    // en passant -- TBD
    // required knowledge of en-passant square from last move
}

static inline void pawnmvs(Movelist *mvs, Square sq0) {
    
    assert( manAt(sq0) );
    assert( !(color(manAt(sq0))==WHITE) || rank(sq0)>0 );
    assert( !(color(manAt(sq0))==BLACK) || rank(sq0)<7 );
    
    switch(color(manAt(sq0))) {
        case WHITE: wP_mvs(mvs,sq0); break;
        case BLACK: bP_mvs(mvs,sq0); break;
    }
}
                                
// Slider Moves (Bishop, Rook, Queen)

// Would be nice to combine these 8 with a single macro as in Lisp
// Could pass in Fwd array but don't like the access overhead.

static inline void slider_fwd(Movelist *mvs, Square sq0) {
    Square sqN = fwd(sq0);
    while (sqN!=NSQ && manAt(sqN) == 0) {
        mvs->push(newMove(sq0,sqN,0,0));
        sqN = fwd(sqN);
    }
    if ( sqN!=NSQ && color(manAt(sqN)) != color(manAt(sq0))) {
        mvs->push(newMove(sq0,sqN,manAt(sqN),0));
    }
}

static inline void slider_rgt(Movelist *mvs, Square sq0) {
    Square sqN = rgt(sq0);
    while (sqN!=NSQ && manAt(sqN) == 0) {
        mvs->push(newMove(sq0,sqN,0,0));
        sqN = rgt(sqN);
    }
    if ( sqN!=NSQ && color(manAt(sqN)) != color(manAt(sq0))) {
        mvs->push(newMove(sq0,sqN,manAt(sqN),0));
    }
}

static inline void slider_bak(Movelist *mvs, Square sq0) {
    Square sqN = bak(sq0);
    while (sqN!=NSQ && manAt(sqN) == 0) {
        mvs->push(newMove(sq0,sqN,0,0));
        sqN = bak(sqN);
    }
    if ( sqN!=NSQ && color(manAt(sqN)) != color(manAt(sq0))) {
        mvs->push(newMove(sq0,sqN,manAt(sqN),0));
    }
}

static inline void slider_lft(Movelist *mvs, Square sq0) {
    Square sqN = lft(sq0);
    while (sqN!=NSQ && manAt(sqN) == 0) {
        mvs->push(newMove(sq0,sqN,0,0));
        sqN = lft(sqN);
    }
    if ( sqN!=NSQ && color(manAt(sqN)) != color(manAt(sq0))) {
        mvs->push(newMove(sq0,sqN,manAt(sqN),0));
    }
}

static inline void slider_dfr(Movelist *mvs, Square sq0) {
    Square sqN = dfr(sq0);
    while (sqN!=NSQ && manAt(sqN) == 0) {
        mvs->push(newMove(sq0,sqN,0,0));
        sqN = dfr(sqN);
    }
    if ( sqN!=NSQ && color(manAt(sqN)) != color(manAt(sq0))) {
        mvs->push(newMove(sq0,sqN,manAt(sqN),0));
    }
}

static inline void slider_dfl(Movelist *mvs, Square sq0) {
    Square sqN = dfl(sq0);
    while (sqN!=NSQ && manAt(sqN) == 0) {
        mvs->push(newMove(sq0,sqN,0,0));
        sqN = dfl(sqN);
    }
    if ( sqN!=NSQ && color(manAt(sqN)) != color(manAt(sq0))) {
        mvs->push(newMove(sq0,sqN,manAt(sqN),0));
    }
}

static inline void slider_dbr(Movelist *mvs, Square sq0) {
    Square sqN = dbr(sq0);
    while (sqN!=NSQ && manAt(sqN) == 0) {
        mvs->push(newMove(sq0,sqN,0,0));
        sqN = dbr(sqN);
    }
    if ( sqN!=NSQ && color(manAt(sqN)) != color(manAt(sq0))) {
        mvs->push(newMove(sq0,sqN,manAt(sqN),0));
    }
}

static inline void slider_dbl(Movelist *mvs, Square sq0) {
    Square sqN = dbl(sq0);
    while (sqN!=NSQ && manAt(sqN) == 0) {
        mvs->push(newMove(sq0,sqN,0,0));
        sqN = dbl(sqN);
    }
    if ( sqN!=NSQ && color(manAt(sqN)) != color(manAt(sq0))) {
        mvs->push(newMove(sq0,sqN,manAt(sqN),0));
    }
}

// Bishop

static inline void bishopmvs(Movelist *mvs, Square sq0) {
    slider_dfr(mvs,sq0);
    slider_dbr(mvs,sq0);
    slider_dbl(mvs,sq0);
    slider_dfl(mvs,sq0);
}

// Rook

static inline void rookmvs(Movelist *mvs, Square sq0) {
    slider_fwd(mvs,sq0);
    slider_rgt(mvs,sq0);
    slider_bak(mvs,sq0);
    slider_lft(mvs,sq0);
}

// Queen

static inline void queenmvs(Movelist *mvs, Square sq0) {
    bishopmvs(mvs,sq0);
    rookmvs(mvs,sq0);
}


// Castle -- TBD

// Trial moves

// Recode with function pointer map in place of switch?
// Does the optimizing compiler does this already?
// Look at the machine code to investigate.


void trialByKind(Movelist *mvs,Square sq) {
    assert( isSquare(sq));
    
    switch (kind(manAt(sq))) {
        case KNIGHT:  knightmvs(mvs, sq); break;
        case BISHOP:  bishopmvs(mvs,sq); break;
        case ROOK:    rookmvs(mvs,sq);   break;
        case QUEEN:   queenmvs(mvs,sq);  break;
        case KING:    kingmvs(mvs,sq);   break;
        case PAWN:    pawnmvs(mvs,sq);   break;
        default:
            error("trialByKind - manAt(square) invalid\n");
    }
}

void trials(Movelist *mvs, Color colorToMove) {
    mvs->clear();
    if (colorToMove == WHITE) {
        forWhiteMen(mvs,trialByKind);
    }
    else {
        assert( colorToMove == BLACK);
        forBlackMen(mvs,trialByKind);
    }
}

void trials_test() {
    printf("---------------------------- begin trials_test\n");
    board_clear();
    Movelist mvs;  //Movelist object on the stack
    
    addMan(f3,wN);
    printBoardMen();
    trials(&mvs,WHITE);
    printf("White to move\n");
    mvs.print();
    assert(mvs.len()==8);
    assert(mvs.find(newMove(f3,g5,0,0)));
    assert(mvs.find(newMove(f3,e5,0,0)));
    assert(mvs.find(newMove(f3,h4,0,0)));
    assert(mvs.find(newMove(f3,h2,0,0)));
    assert(mvs.find(newMove(f3,g1,0,0)));
    assert(mvs.find(newMove(f3,e1,0,0)));
    assert(mvs.find(newMove(f3,d4,0,0)));
    assert(mvs.find(newMove(f3,d2,0,0)));
    assert(!mvs.find(newMove(f3,f5,0,0)));
    mvs.clear();
    
    addMan(a8,bR);
    printBoardMen();
    trials(&mvs,BLACK);
    printf("Black to move\n");
    printf("%i moves\n",mvs.len());
    mvs.print();
    mvs.clear();
    assert(mvs.len()==0);
    
    addMan(c1,wB);
    printBoardMen();
    trials(&mvs,WHITE);
    printf("White to move\n");
    printf("%i moves\n",mvs.len());
    mvs.print();
    mvs.clear();

    addMan(c6,bQ);
    printBoardMen();
    trials(&mvs,BLACK);
    printf("Black to move\n");
    printf("%i moves\n",mvs.len());
    mvs.print();
    mvs.clear();
    
    addMan(a4,wQ);
    printBoardMen();
    trials(&mvs,WHITE);
    printf("White to move\n");
    printf("%i moves\n",mvs.len());
    mvs.print();
    mvs.clear();
    
    addMan(c4,bR);
    printBoardMen();
    trials(&mvs,BLACK);
    printf("Black to move\n");
    printf("%i moves\n",mvs.len());
    mvs.print();
    mvs.clear();
    
    addMan(g1,wK);
    addMan(g2,wP);
    addMan(h2,wP);
    addMan(b5,wP);
    addMan(b7,wP);
    printBoardMen();
    trials(&mvs,WHITE);
    printf("White to move\n");
    printf("%i moves\n",mvs.len());
    mvs.print();
    mvs.clear();
    
    addMan(e7,bP);
    addMan(f4,bP);
    addMan(a6,bP);
    addMan(a2,bP);
    printBoardMen();
    trials(&mvs,BLACK);
    printf("Black to move\n");
    printf("%i moves\n",mvs.len());
    mvs.print();
    mvs.clear();
    
    board_clear();
    addMan(e1,wK);
    addMan(h1,wR);
    addMan(a1,wR);
    for (int i=a2; i<=h2; i++) addMan(i,wP);
    printBoardMen();
    trials(&mvs,WHITE);
    printf("White to move\n");
    printf("%i moves\n",mvs.len());
    mvs.print();
    mvs.clear();
    
    board_clear();
    addMan(e8,bK);
    addMan(h8,bR);
    addMan(a8,bR);
    for (int i=a7; i<=h7; i++) addMan(i,bP);
    printBoardMen();
    trials(&mvs,BLACK);
    printf("Black to move\n");
    printf("%i moves\n",mvs.len());
    mvs.print();
    mvs.clear();
    
    printf("------------------------------ end trials_test\n");
}
