//------------------------------------------------------------
//  control.c
//  nchess
//
//  Created by Mark Cornwell on 8/12/14.
//  Copyright (c) 2014 Mark R Cornwell. All rights reserved.
//------------------------------------------------------------

#include <iostream>
#include <string>
#include "move.h"
#include "movelist.h"
#include "board.h"
#include "trials.h"
#include "alphabeta.h"
#include "control.h"

Move parseMove(std::string s, Movelist *mvs) {
    if (s.length()!=4) return 0;
    else if (s[0]<'a' || s[0]>'h') return 0;
    else if (s[1]<'0' || s[1]>'9') return 0;
    else if (s[2]<'a' || s[2]>'h') return 0;
    else if (s[3]<'0' || s[3]>'9') return 0;
    else {
        Square sq0 = squareAt(s[0]-'a', s[1]-'1');
        Square sq1 = squareAt(s[2]-'a', s[3]-'1');
        return mvs->findMove(sq0,sq1);
    }
}

// Unthreaded toplevel.  Waits until search returns.


int toplevel() {
    std::string command;
    boolean verbose = 1;
    
    std::cout << "I am Groot" << std::endl;
    std::cout << "> ";

    std::cin >> command;
    while( command != "quit") {
        if (command=="help") {
            std::cout <<
            "new         ~ start a new game" << std::endl <<
            "show        ~ print the board" << std::endl <<
            "move e2e4   ~ move man from e2 to e4" << std::endl <<
            "move e7e8q  ~ promote to any of q,n,r,b" << std::endl <<
            "move e1g1   ~ castle-short" << std::endl <<
            "resign      ~ ends the game" << std::endl <<
            "moves       ~ prints list of potential moves)" << std::endl <<
            "history     ~ prints moves made so far" << std::endl <<
            "flags       ~ summary of castling flags" << std::endl <<
            "depth n     ~ set the search depth" << std::endl <<
            "takeback    ~ takeback last 2 halfmoves)" << std::endl <<
            "help        ~ this summary of commands" << std::endl <<
            "quit        ~ ends the game" << std::endl;
        }
        if (command=="new") {
            new_game();
            if (verbose) printBoard();
        }
        else if (command=="show")
            printBoard();
        else if (command=="history") {
            show_history();
            if (verbose) printBoard();
        }
        else if (command=="moves") {
            
            trials(&toplevel_mvs,colorToMove());
            toplevel_mvs.print();
            if (verbose) printBoard();
        }
        else if (command=="move") {   // <<--- needs to reject illegal moves
            std::string arg;
            std::cin >> arg;
            
            trials(&toplevel_mvs,colorToMove());

            // parseMove returns 0 on illegal moves
            Move mv = parseMove(arg, &toplevel_mvs);

            if (mv==0) {
                printf("illegal move");
            }
            else {
                // make the player move
                std::cout << "move: ";
                printMove(mv);
                std::cout << std::endl;
                mv_make(mv);
                if (verbose) printBoard();
            }
        }
        else if (command=="best") {
            
            // find an print out the best move
            Move mv = bestMove();
            std::cout << "best: ";
            printMove(mv);
            std::cout << std::endl;
            if (verbose) printBoard();
            
        }
        else if (command=="go") {
            
            // find the best move
            Move mv = bestMove();
            std::cout << "move: ";
            printMove(mv);
            std::cout << std::endl;
            
            // play the best move
            mv_make(mv);
            
            // if verbose print the new board
            if (verbose) printBoard();
        }
        else if (command=="flags") {
            switch (colorToMove()) {
                case WHITE: printf("white to move "); break;
                case BLACK: printf("black to move "); break;
                default:
                    assert(0);
            };
            printf(",depth=%i  ",depth);
            if (!whiteOO) printf("K");
            if (!whiteOOO) printf("Q");
            if (!blackOO) printf("k");
            if (!blackOOO) printf("q");
            printf("\n");
        }
        else if (command=="depth") {
            unsigned int n;
            std::cin >> n;
            if (n < config_depth_hard_limit)
                depth = n;
            else
                std::cout << "bad parameter" << n << "ignored" << std::endl;
        }
        else if (command=="takeback") {
            std::cout << "takeback not implemented" << std::endl;
        }
        else{
            std::cout
                << "new|quit|history|moves|move e2e4|best|to|takeback" << std::endl
                << "type help for list of commands" << std::endl;
        }
     
        // fetch next command
        std::cout << "> ";
        std::cin >> command;
    }
    return 0;
}
