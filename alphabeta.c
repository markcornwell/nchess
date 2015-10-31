//---------------------------------------------------------------
//  alphabeta.c
//  nchess
//
//  Created by Mark Cornwell on 8/6/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//
//---------------------------------------------------------------
// By convention we stay away from C++ iostream and use stdio
// at this level and below.  Rationale: keep the engine lean
//---------------------------------------------------------------

#include <stdio.h>
#include <mach/mach_time.h>
#include "man.h"
#include "square.h"
#include "move.h"
#include "board.h"
#include "movelist.h"
#include "trials.h"
#include "alphabeta.h"

//--------------------------------------------------------------
//  extern
//--------------------------------------------------------------
struct Movelist toplevel_mvs;
unsigned int toplevel_score[MVLISTMAX];
unsigned int depth = config_depth_default;


//------------------------------------------------------------------------
// This is the appropriate level to introduce history -- a moves that
// have been made.  Trials only generated potential moves, it did not make
// moves on the board.  So mv_make and mv_unmake are different in that they
// enter the moves into the history of moves and manipulate flags such
// as castling allowed, the half move count, the side to move
//------------------------------------------------------------------------

// these get updated whenever a move is made or unmade
unsigned int hmv = 0;          // half move count
unsigned int history[300];     // history of all move made

// records moves in the history
static inline void record(Move mv) { history[hmv++] = mv; }
static inline void unrecord() { hmv--; }


// initiate new game
void new_game() {
    hmv = 0;
    whiteOO = 0;
    whiteOOO = 0;
    blackOO = 0;
    blackOOO = 0;
    board_clear();
    board_setup();
}


// Displaying the game history in a human friendly way


static inline Color colorToMove(unsigned int hm) {
    if (odd(hm)) return BLACK;
    else return WHITE;
}

Color colorToMove() {
    return colorToMove(hmv);
}

static inline unsigned int moveNumber(unsigned int hmv) { return hmv/2 + 1; }

static inline boolean whiteToMove(unsigned int hmv) { return !odd(hmv); }
static inline boolean blackToMove(unsigned int hmv) { return odd(hmv);  }


void show_history() {
    for (int i=0; i<hmv; i++) {
        if (whiteToMove(i)) {
            printf("%i ",moveNumber(i));
            printMove(history[i]);
        }
        else {
            assert(blackToMove(i));
            printf(" ");
            printMove(history[i]);
            printf("\n");
        }
    }
    printf("\n");
}


// Castling

void mv_make_castle(Move mv, Color c) {
    switch ( c ) {
        case WHITE:
            if (isCastleKingside(mv)) {
                delMan(e1);
                addMan(f1,wR);
                addMan(g1,wK);
                delMan(h1);
                assert(whiteOO==0);
                whiteOO = hmv;
                if (!whiteOOO) whiteOOO = hmv;
            }
            else {
                assert( isCastleQueenside(mv) );
                delMan(a1);
                addMan(c1,wK);
                addMan(d1,wR);
                delMan(e1);
                assert(whiteOOO==0);
                whiteOOO = hmv;
                if (!whiteOO) whiteOO = hmv;
            }
            break;
        case BLACK:
            if (isCastleKingside(mv)) {
                delMan(e8);
                addMan(f8,bR);
                addMan(g8,bK);
                delMan(h8);
                assert(blackOO==0);
                blackOO = hmv;
                if (!blackOOO) blackOOO = hmv;
                
            }
            else {
                assert( isCastleQueenside(mv) );
                delMan(a8);
                addMan(c8,bK);
                addMan(d8,bR);
                delMan(e8);
                assert(blackOOO==0);
                blackOOO = hmv;
                if (!blackOO) blackOO = hmv;
            }
            break;
    }
}

void mv_unmake_castle(Move mv,Color c) {
    switch ( c ) {
        case WHITE:
            if (isCastleKingside(mv)) {
                addMan(e1,wK);
                delMan(f1);
                delMan(g1);
                addMan(h1,wR);
                whiteOO = 0;
                
            }
            else {
                assert( isCastleQueenside(mv) );
                addMan(a1,wR);
                delMan(c1);
                delMan(d1);
                addMan(e1,wK);
                whiteOOO = 0;
            }
            break;
        case BLACK:
            if (isCastleKingside(mv)) {
                addMan(e8,bK);
                delMan(f8);
                delMan(g8);
                addMan(h8,bR);
                blackOO = 0;
            }
            else {
                assert( isCastleQueenside(mv) );
                addMan(a8,bR);
                delMan(c8);
                delMan(d8);
                addMan(e8,bK);
                blackOOO = 0;
            }
            break;
    }
}

void mv_make(Move mv) {
    
    assert( isSquare(sqFrom(mv)) );
    assert( manAt(sqFrom(mv)) );  // always have man in sqFrom
    assert( !isCapture(mv) || manAt(sqTo(mv)) );
    assert( !isCapture(mv) || manCaptured(mv)!=0);
    
    record(mv);
        
    Color c = color(sqFrom(mv));
    if (isCastle(mv))
        mv_make_castle(mv,c);
    else {
        // get the man to move
        Man m = manAt(sqFrom(mv));
        
        // update castling flags
        switch (c) {
            case WHITE:
                if (sqFrom(mv)==e1 && m==wK) {
                    if (whiteOO==0) whiteOO = hmv;
                    if (whiteOOO==0) whiteOOO = hmv;
                }
                if (sqFrom(mv)==h1 && m==wR) {
                    if (whiteOO==0) whiteOO = hmv;
                }
                if (sqFrom(mv)==a1 && m==wR) {
                    if (whiteOOO==0) whiteOOO = hmv;
                }
                if (sqTo(mv)==h1 && manCaptured(mv)==wR) {
                    if (whiteOO==0) whiteOO = hmv;
                }
                if (sqTo(mv)==a1 && manCaptured(mv)==wR) {
                    if (whiteOOO==0) whiteOOO = hmv;
                }
                break;
            case BLACK:
                if (sqFrom(mv)==e8 && m==bK) {
                    if (blackOO==0) blackOO = hmv;
                    if (blackOOO==0) blackOOO = hmv;
                }
                if (sqFrom(mv)==h8 && m==bR) {
                    if (blackOO==0) blackOO = hmv;
                }
                if (sqFrom(mv)==a8 && m==bR) {
                    if (blackOOO==0) blackOOO = hmv;
                }
                if (sqTo(mv)==h8 && manCaptured(mv)==bR) {
                    if (blackOO==0) blackOO = hmv;
                }
                if (sqTo(mv)==a8 && manCaptured(mv)==bR) {
                    if (blackOOO==0) blackOOO = hmv;
                }
                break;
            default:
                assert(0);
        }
        
        // set the to square
        if (isCapture(mv))
            delMan(sqTo(mv));

        if (isPromote(mv))
            addMan(sqTo(mv),kindPromotedTo(mv)|c);
        else
            addMan(sqTo(mv),m);
        
        // set the from square
        delMan(sqFrom(mv));
    }
}

void mv_unmake(Move mv) {
    assert( isSquare(sqFrom(mv)) );
    assert( isSquare(sqTo(mv)) );
    assert( manAt(sqFrom(mv))==0 );
    assert( isCastle(mv) || manAt(sqTo(mv)) );
    
    // reset castling flags if it is the hmv when they were set
    if (whiteOO==hmv) whiteOO = 0;
    if (whiteOOO==hmv) whiteOOO = 0;
    if (blackOO==hmv) blackOO = 0;
    if (blackOOO==hmv) blackOOO = 0;
    
    Color c = color(sqFrom(mv));
    if (isCastle(mv)) {
        mv_unmake_castle(mv,c);
    }
    else {
        // get the man to unmove
        Man m = manAt(sqTo(mv));
        
        // reset the to square
        if (isCapture(mv)) {
            delMan(sqTo(mv));
            addMan(sqTo(mv),manCaptured(mv));
        }
        else
            delMan(sqTo(mv));
        
        // reset the from square
        if (isPromote(mv))
            addMan(sqFrom(mv),PAWN|c);
        else
            addMan(sqFrom(mv),m);
    }
    
    unrecord();
}

//----------------------------------------------------------
//                 position evaluation
//----------------------------------------------------------

//int PLUS_INFINITY  =  99999;
//int MINUS_INFINITY = -99999;

int inf = 99999;
unsigned int evaluation_count  = 0;    // DEBUG

int evaluate_white(Square sq) {  // OPTIMIZE
    assert( isMan(manAt(sq)) );
    int score=0;
    switch (manAt(sq)) {
        case wK: score = score + 99999; break;
        case wQ: score = score + 9; break;
        case wR: score = score + 5; break;
        case wB: score = score + 3; break;
        case wN: score = score + 3; break;
        case wP: score = score + 1; break;
        default: assert( 0 );
    }
    return score;
}

int evaluate_black(Square sq) {   // OPTIMIZE
    assert( isMan(manAt(sq)) );
    int score=0;
    switch (manAt(sq)) {
        case bK: score = score - 99999; break;
        case bQ: score = score - 9; break;
        case bR: score = score - 5; break;
        case bB: score = score - 3; break;
        case bN: score = score - 3; break;
        case bP: score = score - 1; break;
        default: assert( 0 );
    }
    return score;
}

int evaluate() {
    int score = 0;
    score = score + forBlackMen(evaluate_black);
    score = score + forWhiteMen(evaluate_white);
    evaluation_count++;
    return score;
}


//---------------------------------------------------------------------
//                      alpha-beta search
//---------------------------------------------------------------------


int alphabetaMax(int alpha, int beta, int depthleft) {
    if (depthleft==0) return evaluate();
    struct Movelist mvs;
    trials(&mvs,WHITE);
    for (int i=0; i<mvs.len() ; i++) {
        Move mv = mvs.get(i);
        // king capture terminates search
        if (manCaptured(mv)==bK)
            return +inf;
        mv_make(mv);
        int score = alphabetaMin( alpha, beta, depthleft-1 );
        mv_unmake(mv);
        if (score >= beta)
            return beta;  // fail hard beta-cutoff
        if( score > alpha )
            alpha = score; // alpha acts like max in minimax
    }
    return alpha;
}


int alphabetaMin(int alpha, int beta, int depthleft){
    if (depthleft==0) return -evaluate();
    struct Movelist mvs;
    trials(&mvs,BLACK);
    for (int i=0; i<mvs.len() ; i++) {
        Move mv = mvs.get(i);
        // king capture terminates search
        if ( manCaptured(mv)==wK)
            return -inf;
        mv_make(mv);
        int score = alphabetaMax( alpha, beta, depthleft-1 );
        mv_unmake(mv);
        if (score <= alpha)
            return alpha;  // fail hard alpha-cutoff
        if( score < beta )
            beta = score; // beta acts like min in minimax
    }
    return beta;
}

void alphabeta_init(){}


//---------------------------------------------------
//              best move selection
//---------------------------------------------------

Move bestMove() {
    Move best=0;
    switch(colorToMove(hmv)) {
        case WHITE: {
            printf("white to move\n");
            trials(&toplevel_mvs,WHITE);
            int max = -inf;
            for (int i=0; i<toplevel_mvs.len() ; i++) {
                Move mv = toplevel_mvs.get(i);
                mv_make(mv);
                int score = alphabetaMin( -inf, +inf, depth);
                toplevel_score[i] = score;
                mv_unmake(mv);
                if (score > max) {
                    max=score;
                    best=mv;
                    //printf("max[%i]:",max); printMove(best); printf("\n");
                }
                printMove(mv);
                printf(" [%i]\n",score);
            }
            break;
        }
        case BLACK: {
            printf("black to move\n");
            trials(&toplevel_mvs,BLACK);
            int min = inf;
            for (int i=0; i<toplevel_mvs.len() ; i++) {
                Move mv = toplevel_mvs.get(i);
                mv_make(mv);
                int score = alphabetaMax( -inf, +inf, depth);
                toplevel_score[i] = score;
                mv_unmake(mv);
                if (score < min) {
                    min=score;
                    best=mv;
                    //printf("min[%i]:",min); printMove(best); printf("\n");
                }
                printMove(mv);
                printf(" [%i]\n",score);
            }
            break;
        }
    }
    return best;
}


void alphabeta_test() {
    printf("------------------------------- begin alphabeta test\n");
    board_clear();
    board_setup();
    printBoardMen();
    Movelist mvs;
    trials(&mvs,WHITE);
    mvs.print();
    
    mv_make(mvs.get(0));
    printf("after "); printMove(mvs.get(0)); printf("\n");
    printBoardMen();
    mv_unmake(mvs.get(0));
    printf("unmake "); printMove(mvs.get(0)); printf("\n");
    printBoardMen();
    
    printf("evaluation=%i\n", evaluate());
    Move m1 = newMove(e2,e4,0,0);
    mv_make(m1);
    Move m2 = newMove(d7,d5,0,0);
    mv_make(m2);
    printBoardMen();
    
    Move m3 = newMove(e4,d5,bP,0);
    mv_make(m3);
    printf("after "); printMove(m3); printf("\n");
    printBoardMen();
    printf("evaluation=%i\n", evaluate());
    
    mv_unmake(m3);
    printf("unmake "); printMove(m3); printf("\n");
    printBoardMen();
    printf("evaluation=%i\n", evaluate());
    
    mv_make(m3);
    printf("after "); printMove(m3); printf("\n");
    printBoardMen();
    printf("evaluation=%i\n", evaluate());
    
    Move m4 = newMove(g8,f6,0,0);
    mv_make(m4);
    printf("after "); printMove(m4); printf("\n");
    printBoardMen();
    printf("evaluation=%i\n", evaluate());
    
    Move m5 = newMove(d1,g4,0,0);
    mv_make(m5);
    printf("after "); printMove(m5); printf("\n");
    printBoardMen();
    printf("evaluation=%i\n", evaluate());

    trials(&mvs,BLACK);
    mvs.print();
    
    for (int d=3; d<5; d++) {
        //time_t start = time(NULL);
        unsigned long long start = mach_absolute_time();
        
        int val= alphabetaMin(-inf,+inf,d);
        //time_t stop = time(NULL);
        unsigned long long stop = mach_absolute_time();
        
        float elapsed_ms = abs_to_milliseconds(stop-start);
        float kilonodes_per_sec = evaluation_count / elapsed_ms;
        
        printf("depth: %i | score: %i  | %i positions | %f ms | %f kN/sec\n",
               d, val, evaluation_count, elapsed_ms, kilonodes_per_sec);
    }
    
    printf("--------------------------------- end alphabeta test\n");
}


