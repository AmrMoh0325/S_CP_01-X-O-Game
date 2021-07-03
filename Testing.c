#include "Testing.h"

test_t TEST_H_LINE_WIN (void)
{
    char test_game[3][3]={{P1_SYMBOL,P1_SYMBOL,P1_SYMBOL},
                          {IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                          {IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL}};


    char x_score=0, o_score=0;
    char t=check_win_state(test_game,X_TURN,&x_score,&o_score);
    if (t==END_P1_WIN&& x_score==1 && o_score==0)    return G_OK;
    return G_ERROR;
}

test_t TEST_V_LINE_WIN (void)
{
    char test_game[3][3]={{P1_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                          {P1_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                          {P1_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL}};


    char x_score=0, o_score=0;
    char t=check_win_state(test_game,X_TURN,&x_score,&o_score);
    if (t==END_P1_WIN && x_score==1 && o_score==0)    return G_OK;
    return G_ERROR;
}

test_t TEST_D_LINE_WIN (void)
{
    char test_game[3][3]={{P1_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                          {IDLE_SYMBOL,P1_SYMBOL,IDLE_SYMBOL},
                          {IDLE_SYMBOL,IDLE_SYMBOL,P1_SYMBOL}};


    char x_score=0, o_score=0;
    char t=check_win_state(test_game,X_TURN,&x_score,&o_score);
    if (t==END_P1_WIN && x_score==1 && o_score==0)    return G_OK;
    return G_ERROR;
}

test_t TEST_X_PLAYER_WIN (void)
{
    char test_game[3][3]={{P1_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                          {IDLE_SYMBOL,P1_SYMBOL,IDLE_SYMBOL},
                          {IDLE_SYMBOL,IDLE_SYMBOL,P1_SYMBOL}};


    char x_score=0, o_score=0;
    char t=check_win_state(test_game,X_TURN,&x_score,&o_score);
    if (t==END_P1_WIN && x_score==1 && o_score==0)    return G_OK;
    return G_ERROR;
}


test_t TEST_O_PLAYER_WIN (void)
{
    char test_game[3][3]={{P2_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                          {IDLE_SYMBOL,P2_SYMBOL,IDLE_SYMBOL},
                          {IDLE_SYMBOL,IDLE_SYMBOL,P2_SYMBOL}};


    char x_score=0, o_score=0;
    char t=check_win_state(test_game,O_TURN,&x_score,&o_score);
    if (t==END_P2_WIN && x_score==0 && o_score==1)    return G_OK;
    return G_ERROR;
}

test_t TEST_STALEMATE (void)
{
    char test_game[3][3]={{P2_SYMBOL,P1_SYMBOL,P1_SYMBOL},
                          {P1_SYMBOL,P2_SYMBOL,P2_SYMBOL},
                          {P1_SYMBOL,P2_SYMBOL,P1_SYMBOL}};


    char x_score=0, o_score=0;
    char t=check_win_state(test_game,X_TURN,&x_score,&o_score);
    if (t==END_STALEMATE && x_score==0 && o_score==0)    return G_OK;
    return G_ERROR;
}

test_t TEST_VALID_MOVE (void)
{
    char test_game[3][3]={{IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                          {IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                          {IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL}};


    char x_score=0, o_score=0;
    char t1=play_turn(test_game,1,X_TURN);
    char t2=play_turn(test_game,2,O_TURN);


    if (t1==1 && t2==1 && test_game[0][0]==P1_SYMBOL && test_game[0][1]==P2_SYMBOL)    return G_OK;
    return G_ERROR;
}

test_t TEST_INVALID_MOVE (void)
{
    char test_game[3][3]={{P1_SYMBOL,P2_SYMBOL,IDLE_SYMBOL},
                          {IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL},
                          {IDLE_SYMBOL,IDLE_SYMBOL,IDLE_SYMBOL}};


    char x_score=0, o_score=0;
    char t1=play_turn(test_game,1,X_TURN);
    char t2=play_turn(test_game,2,X_TURN);


    if (t1==0 && t2==0 && test_game[0][0]==P1_SYMBOL && test_game[0][1]==P2_SYMBOL)    return G_OK;
    return G_ERROR;
}





void testing_APP(void)
{
    int input;
    test_t (*arr[9])(void)={TEST_H_LINE_WIN,
                            TEST_V_LINE_WIN,
                            TEST_D_LINE_WIN,
                            TEST_X_PLAYER_WIN,
                            TEST_O_PLAYER_WIN,
                            TEST_STALEMATE,
                            TEST_VALID_MOVE,
                            TEST_INVALID_MOVE,
                            play_game};

    system("cls");
    printf("\tTESTING XO GAME\n\n1-TEST HORIZONTAL LINE WIN\n2-TEST VERTICAL LINE WIN\n3-TEST DIAGONAL LINE WIN\n4-TEST X PLAYER WIN\n5-TEST O PLAYER WIN\n6-TEST STALEMATE\n7-TEST VALID MOVE\n8-TEST INVALID MOVE\n9-RUN ALL TESTS\n10-Run Game\n0-EXIT\n\n\n");


    while (1)
    {
        printf("Enter Number: ");
        scanf("%d",&input);

        if (input==0)   break;
        else if (input>0 && input <9)
        {
            printf("%s\n\n",((arr[input-1]())? "PASS":"FAIL"));
        }
        else if (input == 9)
        {
            for (int i=0;i<8;i++)
            {
                printf("%s\n",((arr[i]())? "PASS":"FAIL"));
            }
            printf("\n");
        }
        else if (input == 10)
        {
            arr[8]();
            break;
        }
        else
        {
            printf("Wrong input\n\n");
        }

    }
}

