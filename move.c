//---------------------------------------------------------------
//  move.c
//  nchess
//
//  Created by Mark Cornwell on 7/22/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
////---------------------------------------------------------------
#include <stdio.h>
#include "util.h"
#include "square.h"
#include "move.h"

void move_test() {
    
    Move M[100];
    printf("------------------------------------ begin move_test\n");
    
    // build a sample of test moves
    M[0]=newMove(e2,e4,0,0);
    M[1]=newMove(e7,e5,0,0);
    M[2]=newMove(0,0,0,MV_CASTLE_KINGSIDE);
    M[3]=newMove(0,0,0,MV_CASTLE_QUEENSIDE);
    M[4]=newMove(a7,a8,0,MV_PROMOTE_QUEEN);
    M[5]=newMove(a7,a8,0,MV_PROMOTE_ROOK);
    M[6]=newMove(a7,a8,0,MV_PROMOTE_BISHOP);
    M[7]=newMove(a7,a8,0,MV_PROMOTE_KNIGHT);
    M[8]=newMove(e4,d5,bP,0);
    M[9]=newMove(e5,f3,bP,MV_ENPASSANT);
    M[10]=newMove(g2,a8,bR,MV_CHECK);
    M[11]=newMove(e1,e8,bR,MV_MATE);
    M[12]=newMove(f3,f7,bP,MV_CHECK);
    M[13]=0;
    
    // print all the sample moves
    for (int i=0; M[i]!=0; i++) {
        printf("M[%i]: ",i);
        printMove(M[i]);
        printf("\n");
    }
    printf("------------------------------------ end move test\n");
}

void printMove(Move mv) {
    if (isCastleKingside(mv))
        printf("O-O");
    else if (isCastleQueenside(mv))
        printf("O-O-O");
    else {
        printSquare(sqFrom(mv));
        
        if (isCapture(mv)) {
            printf("x");
            printKind(kind(manCaptured(mv)));
        }
        else
            printf("-");
        
        printSquare(sqTo(mv));
        
        if (isEnPassant(mv))
            printf(" ep");
        
        if (isPromote(mv)) {
            //printf("%x",kindPromotedTo(mv));
            switch (kindPromotedTo(mv)) {
                case KNIGHT: printf("/N"); break;
                case BISHOP: printf("/B"); break;
                case ROOK:   printf("/R"); break;
                case QUEEN:  printf("/Q"); break;
                default:  printf("*** ERROR bad kind ***");
            }
        }
        
        if (isCheck(mv))
            printf("+");
        else if (isMate(mv))
            printf("++");
        else if (isStalemate(mv))
            printf("=");
    }
}
