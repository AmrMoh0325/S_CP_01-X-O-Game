
#ifndef TESTING_H_
#define TESTING_H_

#include <stdio.h>
#include <stdlib.h>
#include "XOGame.h"



typedef enum{G_ERROR,G_OK}test_t;

/***************************** Functions ************************************/

//tests if a horizontal line of only X or O leads to a player win
test_t TEST_H_LINE_WIN (void);

//tests if a vertical line of only X or O leads to a player win
test_t TEST_V_LINE_WIN (void);

//tests if a diagonal line of only X or O leads to a player win
test_t TEST_D_LINE_WIN (void);

//tests if 3 consecutive x's can lead x player to win
test_t TEST_X_PLAYER_WIN (void);

//tests if 3 consecutive x's can lead o player to win
test_t TEST_O_PLAYER_WIN (void);

//tests if the board is full and no one won can lead to stalemate
test_t TEST_STALEMATE (void);

//tests if a move in a valid location can apply
test_t TEST_VALID_MOVE (void);

//tests if a move in an invalid location can not apply
test_t TEST_INVALID_MOVE (void);

//an api that manages and runs the above test cases and provides a simple UI to the tester for easy testing
void testing_APP(void);



#endif // TESTING_H_
