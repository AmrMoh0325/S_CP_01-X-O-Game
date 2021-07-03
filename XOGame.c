#include "XOGame.h"

/***************************** Variables ************************************/

//2D array containing game data
static char game[3][3]={{IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                        {IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                        {IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL}};


/***************************** Functions ************************************/
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
    char win_flag=0,Empty_flag=0;

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

    if (!win_flag)
    {
        for (int i=0;i<9;i++)
        {
            if (game[0][i] == IDLE_SYMBOL)
            {
                Empty_flag=1;
                break;
            }
        }
    }

    if (!win_flag && !Empty_flag)
    {
        win_flag = END_STALEMATE;
    }
    else if (win_flag)
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
    int x=(square_num-1)/3;
    int y=(square_num-1)%3;

    if (game[x][y] == IDLE_SYMBOL)
    {
        if (turn==X_TURN)       game[x][y]=P1_SYMBOL;
        else if (turn==O_TURN)  game[x][y]=P2_SYMBOL;
        return 1;
    }
    return 0;
}

void print_end_msg(char game_state)
{
    switch(game_state)
    {
    case END_P1_WIN:
        printf("\n\tPlayer X Wins!\n\n");
        break;
    case END_P2_WIN:
        printf("\n\tPlayer O Wins!\n\n");
        break;
    case END_STALEMATE:
        printf("\n\tStalemate!\n\n");
        break;
    default:
        break;



    }
    printf("\tPress Any Key");
    getchar();
    getchar();
}


void play_game(void)
{
    char turn=X_TURN,x_score=0,o_score=0;
    char play_flag=0,end_flag=0;
    int input=0;
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
                end_flag=check_win_state(game,turn,&x_score,&o_score);
            }
            else    continue;

        }
        else if(input==0)       break;
        else                    continue;

        if (end_flag)
        {
            print_game(game,turn,x_score,o_score);
            print_end_msg(end_flag);
            clear_board(game);
            turn = !turn;
            play_flag=0;
            end_flag=0;
        }
        else
        {
            play_flag=0;
            turn = !turn;
        }
    }
}
