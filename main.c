/* Project: Memory Game 2016-05-06 */

/*
 * TODO: Allow player to select size of board
 *       Make sure the total size of board (X * Y) is an even number no bigger than 26 (A-Z)
 * TODO: Store board size in variables instead of #define
 *       Let's the user chose size, and let's you keep it within boundaries (even number of cards <= 26)
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
    int board_x = 4;
    int board_y = 4;
    char board[MAX_CARDS * 2] = {0}; // Must hold two sets of MAX_CARDS
    int guess[4] = {-1, -1, -1, -1};
    char answer;
    int noOfCards;
    
    while(gameOn)
    {
        // Initialize the board if new game
        if (rounds == 0)
        {
            printf("\n### M E M O R Y ###\n\n");
            printf("Board size is %d x %d. Do you want to change the size (y/n)? ", board_x, board_y);

            // Get answer from player
            scanf("%c", &answer);

            // Let the player change number of cards
            if (answer == 'y')
            {
                do
                {
                    printf("How many cards (max %d)? ", MAX_CARDS);
                    getchar(); // Catch lingering input...
                    scanf("%d", &noOfCards);
                    if (noOfCards > MAX_CARDS)
                    {
                        printf("To many cards. Max %d.", MAX_CARDS);
                        continue;
                    }
                    else
                    {
                        board_x = 2;
                        board_y = noOfCards;
                        
                        // Make a somewhat symetric board
                        while (board_y > board_x && board_y % 2 == 0)
                        {
                            board_x *= 2;
                            board_y /= 2;
                        }
                        break;
                    }
                } while(1);
            }

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
        // See if the board is completely solved
        gameOn = !checkGame(board, board_x, board_y);
        
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
            getchar();
        }
    }
    
    // Done for today
    printf("\n\nBye bye!");
    
	return 0;
}
