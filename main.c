#include <stdio.h>
#include <stdlib.h>
#include "XOGame.h"
#include "Testing.h"

#define    TEST

int main()
{
    #ifdef      TEST
    //run this if you want to run game tests
    testing_APP();
    #endif

    #ifdef    APP
    //run this if you want to directly play the game
    play_game();
    #endif // APP

    return 0;
}
