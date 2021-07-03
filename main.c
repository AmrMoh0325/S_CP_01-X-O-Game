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


/***************************** Variables ************************************/
//2D array containing game data
char game[3][3]={{IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                 {IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                 {IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL}};


/***************************** Functions ************************************/

//
void clear_board(char board[][3])
{
    for (int i=0;i<9;i++)
    {
        game[0][i]=IDLE_SYMBOL;
    }
}

void print_game(char game[][3],char turn, char x_score,char o_score)
{
    system("cls");
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





char check_win_state(char game[][3], char turn, char *x_score, char *o_score)
{
    char win_flag=0;

    if (DIAGONAL_LINE1_CHECK || DIAGONAL_LINE2_CHECK)
    {
        win_flag=1;
    }
    for (int i=0;i<3;i++)
    {
        if (win_flag)       break;

        if (HORIZONTAL_LINE_CHECK(i) || VERTICAL_LINE_CHECK(i))
        {
            win_flag=1;
        }
    }

    if (win_flag)
    {
        if (turn==X_TURN)
        {
            (*x_score)++;
            win_flag=END_P1_WIN;
        }
        else if (turn==O_TURN)
        {
            (*o_score)++;
            win_flag=END_P2_WIN;
        }
    }
    return win_flag;
}


char play_turn(char game[][3],char square_num,char turn)
{
    char x=(square_num-1)/3;
    char y=(square_num-1)%3;

    if (game[x][y] == IDLE_SYMBOL)
    {
        if (turn==X_TURN)       game[x][y]='X';
        else if (turn==O_TURN)  game[x][y]='O';
        return 1;
    }
    return 0;
}

void print_end_msg(char game_state)
{
    switch(game_state)
    {
    case END_STALEMATE:
        printf("\n\tStalemate!\n\n");
        break;
    case END_P1_WIN:
        printf("\n\tPlayer X Wins!\n\n");

        break;
    case END_P2_WIN:
        printf("\n\tPlayer O Wins!\n\n");
        break;
    }
    printf("\tPress Any Key");
    getchar();
    getchar();
}


int main()
{
    char turn=X_TURN,x_score=0,o_score=0;
    char input=0,play_flag=0,win_flag=0, move_counter=0;
    clear_board(game);
    while (1)
    {
        print_game(game,turn,x_score,o_score);
        printf("\t%s\n\n\nEnter Square Number (1~9) or (0:quit) : ",((turn== X_TURN)? "X TURN" : "O TURN"));
        fflush(stdin);
        scanf("%d", &input);

        if ((input>=1) && (input<=9))
        {
            play_flag=play_turn(game,input,turn);
            if (play_flag)
            {
                move_counter++;
                win_flag=check_win_state(game,turn,&x_score,&o_score);
            }
            else    continue;

        }
        else if(input==0)       break;
        else                    continue;

        if (win_flag || move_counter>8)
        {
            print_game(game,turn,x_score,o_score);
            print_end_msg(win_flag);
            clear_board(game);
            turn = !turn;
            move_counter=0;
            play_flag=0;
            win_flag=0;

        }
        else
        {
                play_flag=0;
                turn = !turn;
        }
    }
    return 0;
}
