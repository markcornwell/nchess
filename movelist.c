//----------------------------------------------------------------
//  movelist.c
//  nchess
//
//  Created by Mark Cornwell on 7/26/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//----------------------------------------------------------------

#include <stdio.h>
#include "movelist.h"


void movelist_test() {
    printf("--------------------------------begin movelist test\n");
    Movelist mvs;
    
    mvs.init();
    
    assert(mvs.len()==0);
    assert(mvs.empty());
    
    mvs.push(newMove(e2,e4,0,0));
    
    assert(mvs.len()==1);
    assert(mvs.get(0)==newMove(e2,e4,0,0));
    assert(!mvs.empty());
    
    mvs.push(newMove(e7,e5,0,0));
    mvs.push(newMove(g1,f3,0,0));
    mvs.push(newMove(b8,c6,0,0));
    
    assert(!mvs.empty());
    assert(mvs.len()==4);
    assert(mvs.get(0)==newMove(e2,e4,0,0));
    assert(mvs.get(1)==newMove(e7,e5,0,0));
    assert(mvs.get(2)==newMove(g1,f3,0,0));
    assert(mvs.get(3)==newMove(b8,c6,0,0));
    
    Move mv3 = mvs.pop();
    
    assert(!mvs.empty());
    assert(mvs.len()==3);
    assert(mv3 == newMove(b8,c6,0,0));
    
    mvs.push(mv3);
    
    assert(mvs.len()==4);
    assert(mvs.get(3)==mv3);
    
    for (int i=0; i< mvs.len(); i++) {
        printf("M[%i]: ",i);
        printMove(mvs.get(i));
        printf("\n");
    }
    
    assert(mvs.len()==4);
    assert(mvs.get(3)==mv3);
    
    while (mvs.len() > 0) {
        mvs.pop();
    }
    
    assert(mvs.empty());
    assert(mvs.len() == 0);
    
    printf("mvlist_test passed\n");
    printf("--------------------------------- end movelist test\n");
}


