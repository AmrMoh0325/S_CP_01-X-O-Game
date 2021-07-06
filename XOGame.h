/*****************************************************************************
* Task: X-O Game
* File Name: XOGame.h
* Description: Source file for X-O Game Task
* Author: Amr Mohamed
* Date: 3/7/2021
******************************************************************************/


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
#define IN_PROGRESS     0
#define END_P1_WIN      1
#define END_P2_WIN      2
#define END_DRAW        3

// check conditions for each row, column and diagonal line
#define HORIZONTAL_LINE_CHECK(x)     ((game[x][0] !=IDLE_SYMBOL) && (game[x][0] == game[x][1]) && (game[x][1] == game[x][2]))
#define VERTICAL_LINE_CHECK(y)       ((game[0][y] !=IDLE_SYMBOL) && (game[0][y] == game[1][y]) && (game[1][y] == game[2][y]))
#define DIAGONAL_LINE1_CHECK         ((game[0][0] !=IDLE_SYMBOL) && (game[0][0] == game[1][1]) && (game[1][1] == game[2][2]))
#define DIAGONAL_LINE2_CHECK         ((game[0][2] !=IDLE_SYMBOL) && (game[0][2] == game[1][1]) && (game[1][1] == game[2][0]))




/***************************** Functions ************************************/

/************************************************************************************
* Parameters (in): Game board
* Parameters (out): void
* Return value: void
* Description: Clears game board for a new game
************************************************************************************/
void clear_board(char board[][3]);

/************************************************************************************
* Parameters (in): Game board - current player turn - score for x player - score for o player
* Parameters (out): void
* Return value: void
* Description: draws the current game board
************************************************************************************/
void print_game(char game[][3],char turn, char x_score,char o_score);

/************************************************************************************
* Parameters (in): Game board - current player turn - score for x player - score for o player
* Parameters (out): a value indicating who has won the game
* Return value: (IN_PROGRESS) if no one has won - (END_P1_WIN) if x player won - (END_P2_WIN) if o player won - (END_DRAW) if the game ended with no wins.
* Description: checks if someone has won the game
************************************************************************************/
char check_win_state(char game[][3], char turn, char *x_score, char *o_score);

/************************************************************************************
* Parameters (in): Game board - cell number the player selected - current player turn
* Parameters (out): a value indicated if the move was successful or not
* Return value: 1 if move was successful or 0 if not
* Description: applies a move with the player symbol in the cell he selected
************************************************************************************/
char play_turn(char game[][3],char square_num,char turn);

/************************************************************************************
* Parameters (in): a flag with current Game state
* Parameters (out): void
* Return value: void
* Description: prints ending message if the game has ended
************************************************************************************/
void print_end_msg(char game_state);

/************************************************************************************
* Parameters (in): void
* Parameters (out): void
* Return value: void
* Description: user calls this function to play a game of XO game
************************************************************************************/
void play_game(void);


#endif // XOGAME_H_
