#ifndef XOGAME_H_
#define XOGAME_H_

#include <stdio.h>
#include <stdlib.h>

/************************ Defines *************************************/

//symbols that show up on the board
#define IDLE_SYMBOL ' '
#define P1_SYMBOL   'X'
#define P2_SYMBOL   'O'

//players turn indecators
#define X_TURN      0
#define O_TURN      1

//game states indicators
#define END_STALEMATE   0
#define END_P1_WIN      1
#define END_P2_WIN      2

// check conditions for each row, column and diagonal line
#define HORIZONTAL_LINE_CHECK(x)     ((game[x][0] !=IDLE_SYMBOL) && (game[x][0] == game[x][1]) && (game[x][1] == game[x][2]))
#define VERTICAL_LINE_CHECK(y)       ((game[0][y] !=IDLE_SYMBOL) && (game[0][y] == game[1][y]) && (game[1][y] == game[2][y]))
#define DIAGONAL_LINE1_CHECK         ((game[0][0] !=IDLE_SYMBOL) && (game[0][0] == game[1][1]) && (game[1][1] == game[2][2]))
#define DIAGONAL_LINE2_CHECK         ((game[0][2] !=IDLE_SYMBOL) && (game[0][2] == game[1][1]) && (game[1][1] == game[2][0]))




/***************************** Functions ************************************/

//clears game board
void clear_board(char board[][3]);

//prints game board
void print_game(char game[][3],char turn, char x_score,char o_score);

//checks if any player has won the game
char check_win_state(char game[][3], char turn, char *x_score, char *o_score);

//checks if the position the player selected is valid, if so, applys the move
char play_turn(char game[][3],char square_num,char turn);

//prints the ending message declaring a player win or a stalemate
void print_end_msg(char game_state);

// runs the game
void play_game(void);


#endif // XOGAME_H_
