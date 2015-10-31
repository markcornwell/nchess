//---------------------------------------------------------------
//  test.h
//  nchess
//
//  Created by Mark Cornwell on 7/29/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//---------------------------------------------------------------

#ifndef nchess_test_h
#define nchess_test_h

// Regression Test Framework
//
// Try to fit the entire framework in a one or two page header file.
// Strategy is to put all the test program in a linked list then walk
// the list to execute them.  We pass a bookkeeping structure into
// each test for it to update.
//
// TO DO
// * condense repetitive code with macros
// * watch out for macro capture
// * can we do this with inlines?
//

#include <stdlib.h>

typedef unsigned int status;

static const status notrun=0, passed=1, failed=2, aborted=3;

const char *statusStrings[4]= {"notrun", "passed", "failed", "aborted" };

struct test_entry {
    void (* test_function)(test_entry*);
    const char* test_name;
    const char* test_purpose;
    status test_status;
    unsigned int assertions_passed;
    unsigned int assertions_failed;
    test_entry *next;
};

#define  tfy_define(fcn)    void fcn(test_entry *te)
#define  tfy_name(name)     te->test_name=name; printf("%s\n", te->test_name);
#define  tfy_purpose(purpose) te->test_purpose = purpose;
#define  tfy_pass           { te->test_status=passed; te->assertions_passed++; }
#define  tfy_fail           { te->test_status=failed; te->assertions_failed++; }

#define  tfy_assert(cond)   if (cond) tfy_pass else tfy_fail

static test_entry *test_head = 0;
static test_entry *test_last = 0;

void test_init() {
    printf("test_init called\n");
}

// add a test to the test suite
void test_add(void (*func)(test_entry*)) {
//void test_add(void *func) {
    test_entry *te;
    te = (test_entry*) malloc(sizeof(test_entry));
    te->test_function = (void(*)(test_entry*)) func;
    te->test_status = notrun;
    te->assertions_passed = 0;
    te->assertions_failed = 0;
    te->next = 0;
    if (test_head==0) {
        // point head and last to the new node
        test_head = te;
        test_last = te;
    }
    else {
        // add the node onto the back of the test list
        test_last->next = te;
        test_last = te;
    }
}

// run all the tests in the test suite
void test_runall() {
    printf("\n******* test_runall: begin ***********\n");
    test_entry *te = test_head;
    while ( te != 0 ) {
        te->test_function(te);
        te = te->next;
    }
    printf("\n****** test_runall: end **************\n");
}

// report test results
void test_report() {
    test_entry *te = test_head;
    while (te) {
        printf("%s: p%i f%i %s\n",
               statusStrings[te->test_status],
               te->assertions_passed,
               te->assertions_failed,
               te->test_name);
        te = te->next;
    }
}

#endif
