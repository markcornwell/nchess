//---------------------------------------------------------------
//  board.c
//  nchess
//
//  Created by Mark Cornwell on 7/16/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//
//---------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "board.h"

//------------------------------------------------------------
// A piece entry indicates the man and the square it occupies
// we can add mre stuff later
//------------------------------------------------------------

struct piece_entry {
    Man man;  // man in the square
    Square square;  // square occupied
    piece_entry *next;
};


//-----------------------------------------------------------------
// A clear recursive implementation of list insertion and deletion
// Complier should be able turn recursive calls into fast loops.
//-------------------------------------------------------------------

typedef piece_entry *list;

list add(list u, Square sq, Man m) {
    list v = (list) malloc(sizeof (piece_entry));
    v->square = sq;
    v->man = m;
    v->next = u;
    return v;
}

list del(list u, Square sq) {
    if (u==0)
        return 0;
    else if (u->square == sq) {
        list v = u->next;
        free(u);
        return v;
    }
    else {
        u->next = del(u->next, sq);
        return u;
    }
}

list clear(list u) {
    if (u==0)
        return 0;
    else {
        list v=u->next;
        free(u);
        return clear(v);
    }
}

//--------------------------------------------------------------
// If Board[sq] is non-zero it points to a piece-entry that
// points back to the square.
//
//    I1:  Board[sq]!=0  => ( Board[sq]->square == sq )
//
// and that piece_entry holds a man.
//
//    I2:   Board[sq]!=0 => (isMan(Board[sq]->man))
//---------------------------------------------------------------

static list board[64];
static list whiteMen=0;
static list blackMen=0;

void board_init() {
    for (int i=0; i<=63; i++)
        board[i]=0;
    whiteMen=clear(whiteMen);
    blackMen=clear(blackMen);
}

void board_clear() {
    board_init();
}

void board_setup() {
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
}

void addMan(Square s, Man m) {
    assert( board[s] == 0 );
    assert( isMan(m) );
    assert( isSquare( s ));
    switch ( color(m) ) {
        case WHITE:
            whiteMen = add(whiteMen, s, m);
            board[s] = whiteMen;
            break;
        case BLACK:
            blackMen = add(blackMen, s, m);
            board[s] = blackMen;
            break;
    }
}

void delMan(Square s) {
    assert( isSquare(s) );
    assert( board[s] != 0 );
    assert( isMan( board[s]->man ) );
    switch ( color( board[s]->man) ) {
        case WHITE:
            whiteMen = del(whiteMen, s);
            board[s] = 0;
            break;
        case BLACK:
            blackMen = del(blackMen, s);
            board[s] = 0;
            break;
    }
}


Man manAt(Square sq) {
    // returns 0 if sq is empty or off the board, else the man at the given square
    if (board[sq]==0 || sq==NSQ )
        return 0;
    else
        return board[sq]->man;
}

//----------------------------------------------------------
// Apply a given function to squares occupired by men
// of a given color.  This pattern keeps the callers
// from learning the secret of how to itterate down
// the list.  Didn't want ot give them random access
// into the list since it becomes O(n^2) easily.
//----------------------------------------------------------

void forWhiteMen (void fcn(Square)) {
    piece_entry *pe = whiteMen;
    while ( pe != 0 ) {
        assert( board[pe->square] != 0 );
        assert( board[pe->square] == pe );
        fcn(pe->square);
        pe = (piece_entry*) (pe->next);
    }
}

void forBlackMen (void fcn(Square)) {
    piece_entry *pe = blackMen;
    while (pe != 0) {
        fcn(pe->square);
        pe = (piece_entry*) (pe->next);
    }
}

int forWhiteMen (int fcn(Square)) {
    int result = 0;
    piece_entry *pe = whiteMen;
    while ( pe != 0 ) {
        assert( board[pe->square] != 0 );
        assert( board[pe->square] == pe );
        result = result + fcn(pe->square);
        pe = (piece_entry*) (pe->next);
    }
    return result;
}

int forBlackMen (int fcn(Square)) {
    int result = 0;
    piece_entry *pe = blackMen;
    while (pe != 0) {
        result = result + fcn(pe->square);
        pe = (piece_entry*) (pe->next);
    }
    return result;
}

void forWhiteMen (Movelist *mvs, void fcn(Movelist *,Square)) {
    piece_entry *pe = whiteMen;
    while ( pe != 0 ) {
        assert( board[pe->square] != 0 );
        assert( board[pe->square] == pe );
        fcn(mvs,pe->square);
        pe = (piece_entry*) (pe->next);
    }
}

void forBlackMen (Movelist *mvs, void fcn(Movelist *,Square)) {
    piece_entry *pe = blackMen;
    while (pe != 0) {
        fcn(mvs, pe->square);
        pe = (piece_entry*) (pe->next);
    }
}

void verifyBoard() {
    
     // verify that each piece list entry indexes a board{sq] that points back to it
    for (piece_entry *pe = whiteMen; pe!=0 ; pe = (piece_entry *)pe->next) {
        assert( board[pe->square] == pe );
    }
    
    for (piece_entry *pe = blackMen; pe!=0 ; pe = (piece_entry *)pe->next) {
        assert( board[pe->square] == pe );
    }
    
    // verify that each board[sq] points to a piece_entry that points back to it
    for (int i=0; i<=63; i++) {
        assert( board[i]==0 || board[i]->square == i ); // I2
    }
}

//------------------------------------------------------
// Printing the piece entries
//------------------------------------------------------


void printMen (piece_entry *pe) {
    printf("[ ");
    while (pe) {
        printMan(pe->man);
        printSquare(pe->square);
        pe = (piece_entry *)pe->next;
        if (pe)
            printf(" ");
    }
    printf(" ]\n");
}

void printWhiteMen () { printf("whiteMen: "); printMen(whiteMen); }
void printBlackMen () { printf("blackMen: "); printMen(blackMen); }

boolean unoccupied(Square sq) { return board[sq]==0; }
boolean occupied(Square sq) { return board[sq]!=0; }



//------------------------------- Printing and Diagnostics

void printBoard() {
    for (int r=7; r>=0; r--) {
        for (int f=0; f<=7; f++) {
            Square i = squareAt(f,r);
            //printf("r=%i f=%i i=%i\n",r,f,i);
            assert(0<=i);
            assert(i<=63);
            if (file(i)==0) printf("\n%i ",r+1);
            if (manAt(i)==0)
                printf(" --");
            else
                printf(" %s",man_string(manAt(i)));
        }
    }
    printf("\n   ");
    for (int i='a'; i<='h'; i++)
        printf("%c  ",i);
    printf("\n\n");
}


void printBoardMen () {
    printBoard();
    printWhiteMen();
    printBlackMen();
}


void board_test(){
    printf("--------------------------------------- board test\n");

    for (int i=a1; i<=h8; i++) {
        assert(manAt(i)==0);
    }
    printf("1) board initally empty\n");
    printBoardMen();
    
    printf("2) place white rook on a1\n");
    addMan(a1,wR);
    printBoardMen();
    
    printKind(manAt(a1)); printf("\n");
    assert(manAt(a1)==wR);    

    printf("3) remove the man at a1\n");
    delMan(a1);
    printBoardMen();
    
    printf("4) add 5 men to the board");
    addMan(e2,wK);
    addMan(h8,bB);
    addMan(f7,wN);
    addMan(c5,bK);
    addMan(d3,wP);
    printBoardMen();
    
    printf("5) remove the knight from f7\n");
    delMan(f7);
    printBoardMen();
    
    printf("6) remove the bishop from h8\n");
    delMan(h8);
    printBoardMen();
    
    printf("7) remove the rest\n");
    delMan(e2);
    delMan(c5);
    delMan(d3);
    printBoardMen();
    
    printf("8) setup initial position");
    board_clear();
    board_setup();
    printBoardMen();
    
    printf("------------------------------------- end board test\n");
}

