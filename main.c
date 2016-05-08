/* Project: Memory Game 2016-05-06 */

/*
 * TODO: Allow player to select size of board
 * TODO: Make sure the total size of board (X * Y) is an even number no bigger than 26 (A-Z)
 * TODO: Allow player to "PLAY AGIN"
 * TODO: Two players?
 * TODO: AI?
 * */

#include <stdio.h>

#include "memory.h"

#define BOARD_X 2
#define BOARD_Y 2

// Main program
int main(int argc, char **argv)
{
    int i;
    int gameOn = 1;
    int rounds = 0;
    char board[BOARD_X * BOARD_Y] = {0};
    int guess[4] = {-1, -1, -1, -1};
    
    while(gameOn)
    {
        // Initialize the board if on the first round
        if (rounds == 0)
        {
            printf("\n### M E M O R Y ###\n");
            init(board, BOARD_X * BOARD_Y);
        }
        
        // Present the board
        drawBoard(board, guess, BOARD_X, BOARD_Y);
        
        // Get input from player
        for (i = 0; i < 2; i++)
        {
            pickCard(board, guess, BOARD_X, BOARD_Y);
            drawBoard(board, guess, BOARD_X, BOARD_Y);
        }
        
        // Correct guess..?
        checkCards(board, guess, BOARD_X, BOARD_Y);
        // See if the board is completely solved
        gameOn = !checkGame(board, BOARD_X, BOARD_Y);
        
        // Prepare for next round
        clearGuess(guess);
        rounds++;
        
        if (!gameOn)
        {
            char answer;
            // We have a winner!
            printf("\n\nYou won in %d rounds!\n", rounds);
            printf("Want to play again (y/n)? ");
            getchar(); // Catch lingering input...
            scanf("%c", &answer);
            if (answer == 'y')  {
                gameOn = 1;
                rounds = 0;
            };
        }
    }
    
    // Done for today
    printf("\n\nBye bye!");
    
	return 0;
}
