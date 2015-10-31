//---------------------------------------------------------------
//  test-example.c
//  nchess
//
//  Created by Mark Cornwell on 7/29/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//---------------------------------------------------------------

#include <stdio.h>

//---------------------------------------------------------------------
//  Example use of framework
//  This file needs to be type C++ Header inside XCode IDE
//---------------------------------------------------------------------


#include "test.h"

// test cases

tfy_define(null_test) {
    tfy_name("null test always passes");
    tfy_pass;
}
tfy_define(infinity_test) {
    tfy_name("infinity test always fails");
    tfy_fail;
}

tfy_define(test_plus) {
    tfy_name("two plus two is four");
    tfy_assert(2+2 == 4);
}

// test main

void test_example_main() {
    test_init();
    test_add(null_test);
    test_add(infinity_test);
    test_add(test_plus);
    test_runall();
    test_report();
}

