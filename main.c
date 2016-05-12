/* Project: Memory Game 2016-05-06 */

/*
 * TODO: Refactor more. The whole init routine..? (if rounds = 0, if !gameOn ...)
 * TODO: Two players?
 * TODO: AI?
 * */

#include <stdio.h>
#include "memory.h"

#define MAX_CARDS 26 // A-Z

// Main program
int main(int argc, char **argv)
{
    int i;
    int gameOn = 1; // Keep track of if the game is still active
    int rounds = 0;
    int board_x = 0;
    int board_y = 0;
    char board[MAX_CARDS * 2] = {0}; // Must hold two sets of MAX_CARDS
    int guess[4] = {-1, -1, -1, -1};
    char answer; // Used to hold y/n answers from the player
    int noOfCards = 8;
    
    while(gameOn)
    {
        // Initialize the board if new game
        if (rounds == 0)
        {
            printf("\n### M E M O R Y ###\n\n");
            printf("Current board size is %d pairs. Do you want to change the size (y/n)? ", noOfCards);

            // Get answer from player
            scanf("%c", &answer);

            // Let the player change number of cards
            if (answer == 'y')
            {
                getNoOfCards(&noOfCards, MAX_CARDS);
            }
            
            calculateBoardSize(&board_x, &board_y, noOfCards);

            init(board, board_x * board_y);
        }
        
        // Present the board
        drawBoard(board, guess, board_x, board_y);
        
        // Get input from player
        for (i = 0; i < 2; i++)
        {
            pickCard(board, guess, board_x, board_y);
            drawBoard(board, guess, board_x, board_y);
        }
        
        // Correct guess..?
        checkCards(board, guess, board_x, board_y);
        
        // Prepare for next round
        clearGuess(guess);
        rounds++;

        // See if the board is completely solved
        gameOn = !checkGame(board, board_x, board_y);
        
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
            getchar();
        }
    }
    
    // Done for today
    printf("\n\nBye bye!");
    
	return 0;
}
