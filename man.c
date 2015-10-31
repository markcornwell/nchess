//---------------------------------------------------------------
//  man.c
//  nchess
//
//  Created by Mark Cornwell on 7/15/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//---------------------------------------------------------------

#include <stdio.h>
#include "man.h"

// Test routine

static const Man men[12]={wP,wN,wB,wR,wQ,wK,bP,bN,bB,bR,bQ,bK};

static const char* KINDSTRING[8] = {"@",  "P", "N", "K", "@", "B", "R", "Q"};
static const char *MANSTRING[16] = {"--","wP","wN","wK","@@","wB","wR","wQ",
                                    "@@","bP","bN","bK","@@","bB","bR","bQ"};
    
void describe_man(Man m) {
    printColor(color(m));
    printKind(kind(m));
    if (sliding_piece(m)) {
        printf("  slides ");
        if (slides_like_rook(m)) printf("+");
        if (slides_like_bishop(m)) printf("x");
    }
    printf("\n");
}

const char *man_string(Man m) {
    assert(0 <= m);
    assert(m <= bQ);
    return MANSTRING[m];
}

void printMan(Man m) {
    printf("%s",man_string(m));
}

void printColor(Color c) {
    switch(c) {
        case WHITE: printf("WHITE "); break;
        case BLACK: printf("BLACK "); break;
        default:
            error("bad vale to printColor");
    };
}

void printKind(Kind k) {
    printf("%s",KINDSTRING[k]);
}

void man_test() {
    printf("----------------------------------------- man test\n");
    for (int i = 0; i<12 ; i++) describe_man(men[i]);
    printf("--------------------------------------end man test\n");
}

void man_init() {
    // skip
}

