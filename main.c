/* Project: Memory Game 2016-05-06 */

/*
 * TODO: Two players?
 * TODO: AI?
 * */

#include <stdio.h>
#include "memory.h"

#define MAX_CARDS 26 // A-Z

// Define and declare a game settings object
typedef struct gameSettings {
    int gameOn, rounds, noOfCards, maxCards, width, height;
} Game;
Game currentGame = {1, 0, 8, MAX_CARDS, 0, 0};
Game *game = &currentGame;

// Main program
int main(int argc, char **argv)
{
    int i;
    char board[MAX_CARDS * 2] = {0}; // Must hold two sets of MAX_CARDS
    int guess[4] = {-1, -1, -1, -1};
    char answer; // Used to hold y/n answers from the player
    
    while(game->gameOn)
    {
        // Initialize the board if new game
        if (game->rounds == 0)
        {
            printf("\n### M E M O R Y ###\n\n");
            printf("Current board size is %d pairs. Do you want to change the size (y/n)? ", game->noOfCards);

            // Get answer from player
            scanf("%c", &answer);

            // Let the player change number of cards
            if (answer == 'y')
            {
                getNoOfCards(&game->noOfCards, game->maxCards);
            }
            
            calculateBoardSize(&game->width, &game->height, game->noOfCards);

            init(board, game->width * game->height);
        }
        
        // Present the board
        drawBoard(board, guess, game->width, game->height);
        
        // Get input from player
        for (i = 0; i < 2; i++)
        {
            pickCard(board, guess, game->width, game->height);
            drawBoard(board, guess, game->width, game->height);
        }
        
        // Correct guess..?
        checkCards(board, guess, game->width, game->height);
        
        // Prepare for next round
        clearGuess(guess);
        game->rounds++;

        // See if the board is completely solved
        game->gameOn = !checkGame(board, game->width, game->height);
        
        if (!game->gameOn)
        {
            char answer;
            // We have a winner!
            printf("\n\nYou won in %d rounds!\n", game->rounds);
            printf("Want to play again (y/n)? ");
            getchar(); // Catch lingering input...
            scanf("%c", &answer);
            if (answer == 'y')  {
                game->gameOn = 1;
                game->rounds = 0;
            };
            getchar();
        }
    }
    
    // Done for today
    printf("\n\nBye bye!");
    
	return 0;
}
