/*****************************************************************************
* Task: X-O Game
* File Name: XOGame.c
* Description: Source file for X-O Game Task
* Author: Amr Mohamed
* Date: 3/7/2021
******************************************************************************/


#include "XOGame.h"

/***************************** Variables ************************************/

//2D array containing game data
static char game[3][3]={{IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                        {IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                        {IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL}};


/***************************** Functions ************************************/

/************************************************************************************
* Parameters (in): Game board
* Parameters (out): void
* Return value: void
* Description: Clears game board for a new game
************************************************************************************/
void clear_board(char board[][3])
{
    //loop on each element of the game board
    for (int i=0;i<9;i++)
    {
        //set each element to the initial symbol (' ')
        game[0][i]=IDLE_SYMBOL;
    }
}


/************************************************************************************
* Parameters (in): Game board - current player turn - score for x player - score for o player
* Parameters (out): void
* Return value: void
* Description: draws the current game board
************************************************************************************/
void print_game(char game[][3],char turn, char x_score,char o_score)
{
    //clear console
    system("cls");
    //draw the game board with current X/O values
    printf (" _______________________\n");
    printf ("|7      |8      |9      |\n");
    printf ("|   %c   |   %c   |   %c   |\n",game[2][0],game[2][1],game[2][2]);
    printf ("|_______|_______|_______|\n");
    printf ("|4      |5      |6      |\n");
    printf ("|   %c   |   %c   |   %c   |\n",game[1][0],game[1][1],game[1][2]);
    printf ("|_______|_______|_______|\n");
    printf ("|1      |2      |3      |\n");
    printf ("|   %c   |   %c   |   %c   |\n",game[0][0],game[0][1],game[0][2]);
    printf ("|_______|_______|_______|\n");
    printf ("\n X  =  %2d  ||  O  =  %2d\t\n\n",x_score,o_score);
}




/************************************************************************************
* Parameters (in): Game board - current player turn - score for x player - score for o player
* Parameters (out): a value indicating who has won the game
* Return value: (IN_PROGRESS) if no one has won - (END_P1_WIN) if x player won - (END_P2_WIN) if o player won - (END_DRAW) if the game ended with no wins.
* Description: checks if someone has won the game
************************************************************************************/
char check_win_state(char game[][3], char turn, char *x_score, char *o_score)
{
    char win_flag=0,Empty_flag=0;

    //first check both diagonal lines and check if some one has won
    if (DIAGONAL_LINE1_CHECK || DIAGONAL_LINE2_CHECK)
    {
        //set that someone has won flag
        win_flag=1;
    }
    //loop on all rows and columns and check if someone has won
    for (int i=0;i<3;i++)
    {
        //if we know someone has won, no need to continue searching, exit the search
        if (win_flag)       break;

        //continue to check vertical and horizontal lines if someone has won
        if (HORIZONTAL_LINE_CHECK(i) || VERTICAL_LINE_CHECK(i))
        {
            //if someone has won set the winning flag
            win_flag=1;
        }
    }

    //if no one has won yet
    if (!win_flag)
    {
        //check if there is any more empty cells left
        for (int i=0;i<9;i++)
        {
            //if yes, set the empty flag
            if (game[0][i] == IDLE_SYMBOL)
            {
                Empty_flag=1;
                break;
            }
        }
    }

    //if no one has won and the game board is full declare a draw
    if (!win_flag && !Empty_flag)
    {
        win_flag = END_DRAW;
    }

    //if someone has won the game
    else if (win_flag)
    {
        //if it's x player turn
        if (turn==X_TURN)
        {
            //increase his score and declare him a winner
            (*x_score)++;
            win_flag=END_P1_WIN;
        }
        //if it's o player turn
        else if (turn==O_TURN)
        {
            //increase his score and declare him a winner
            (*o_score)++;
            win_flag=END_P2_WIN;
        }
    }
    //return the game state
    return win_flag;
}


/************************************************************************************
* Parameters (in): Game board - cell number the player selected - current player turn
* Parameters (out): a value indicated if the move was successful or not
* Return value: 1 if move was successful or 0 if not
* Description: applies a move with the player symbol in the cell he selected
************************************************************************************/
char play_turn(char game[][3],char square_num,char turn)
{
    //calculate row and column coordinates from cell number
    int x=(square_num-1)/3;
    int y=(square_num-1)%3;
    //if the selected cell is empty
    if (game[x][y] == IDLE_SYMBOL)
    {
        //check who's turn is it and apply the move with his symbol
        if (turn==X_TURN)       game[x][y]=P1_SYMBOL;
        else if (turn==O_TURN)  game[x][y]=P2_SYMBOL;
        //return a success flag
        return 1;
    }
    ////if cell is preoccupied, return a fail flag
    return 0;
}


/************************************************************************************
* Parameters (in): a flag with current Game state
* Parameters (out): void
* Return value: void
* Description: prints ending message if the game has ended
************************************************************************************/
void print_end_msg(char game_state)
{
    //check on the received game state and print out the appropriate message
    switch(game_state)
    {
    case END_P1_WIN:
        printf("\n    Player X Wins!\n\n");
        break;
    case END_P2_WIN:
        printf("\n    Player O Wins!\n\n");
        break;
    case END_DRAW:
        printf("\n\tDarw!\n\n");
        break;
    default:
        break;
    }
    printf("    Press Any Key");
    getchar();
    getchar();
}


/************************************************************************************
* Parameters (in): void
* Parameters (out): void
* Return value: void
* Description: user calls this function to play a game of XO game
************************************************************************************/
void play_game(void)
{
    //create and initialize needed variables
    char turn=X_TURN,x_score=0,o_score=0;
    char play_flag=0,end_flag=0,error_flag=0;
    int input=0;

    //clear the game board
    clear_board(game);
    while (1)
    {
        //print the current game state on the console
        print_game(game,turn,x_score,o_score);

        //if the user had previously tried to add his symbol to an invalid location, print him a message and require him to try again
        if (error_flag)
        {
            printf("\nInvalid location, Try again\n\n ");
            //clear the error flag
            error_flag=0;
        }

        //print the player instructions for the game
        printf("\t%s\n\n\nEnter Square Number (1~9) or (0:quit) : ",((turn== X_TURN)? "X TURN" : "O TURN"));
        //clean input stream
        fflush(stdin);
        //receive player input
        scanf("%d", &input);

        //if his input is within game boundries
        if ((input>=1) && (input<=9))
        {
            //attempt to make the move
            play_flag=play_turn(game,input,turn);
            if (play_flag)      //if move was successful
            {
                //check if anyone has won
                end_flag=check_win_state(game,turn,&x_score,&o_score);
            }
            else
            {
                //set the error flag and skip to the next loop iteration
                error_flag=1;
                continue;
            }
        }

        //if player has entered 0, leave the game
        else if(input==0)       break;
        //if player has entered an invalid location
        else
        {
            //set the error flag and skip to the next loop iteration
            error_flag=1;
            continue;
        }

        //if the game has ended
        if (end_flag)
        {
            //print the last game status
            print_game(game,turn,x_score,o_score);
            //print the ending message declaring who won
            print_end_msg(end_flag);
            //reset game parameters for next game
            clear_board(game);
            turn = !turn;
            play_flag=0;
            end_flag=0;
        }
        //if the game is still in progress
        else
        {
            //reset the move successful flag and flip the turn to the other player
            play_flag=0;
            turn = !turn;
        }
    }
}
