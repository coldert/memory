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

#define BOARD_X 4
#define BOARD_Y 4

// Main program
int main(int argc, char **argv)
{
    int i;
    int gameOn = 1;
    int rounds = 0;
    char board[BOARD_X * BOARD_Y] = {0};
    int guess[4] = {-1, -1, -1, -1};
    
    init(board, BOARD_X * BOARD_Y);
    
    printf("### M E M O R Y ###\n");

    while(gameOn)
    {
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
    }
    
    // We have a winner!
    printf("\n\nYou won in %d rounds!", rounds);
    
	return 0;
}
