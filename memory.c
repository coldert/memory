#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Populate and randomize the board
void init(char board[], int size)
{
    srand(time(NULL));
    
    int i;
    int p = size/2;
    char tmp_c;
    int tmp_i;

    // Fill the board with two sets of letters from A-Z (how far you go depends on board size)
    for (i = 0; i < p; i++)
    {
        board[i] = board[i + p] = (char)('a' + i);
    }

    // Randomize the board
    for (i = 0; i < size; i++)
    {
        tmp_c = board[i];
        tmp_i = rand() % size;
        board[i] = board[tmp_i];
        board[tmp_i] = tmp_c;
    }
}

// Print the current board
void drawBoard(char board[], int guess[], int x, int y)
{
    int i, j;
    printf("\n   "); // Give numbers to the columns
    for (i = 0; i < y; printf("%3d", ++i));
    printf("\n");
    for (i = 0; i < x; i++)
    {
        printf("%2d ", i+1); // Give number to the rows
        for (j = 0; j < y; j++)
        {
            // Check what each "card" should be (a, A or #)
            if (board[i*y + j] < 'a')
                // A correct card
                printf(" %2c", board[i*y+j]);
            else if ((guess[0] == i && guess[1] == j) || (guess[2] == i && guess[3] == j))
                // A currently guessed card
                printf(" %2c", board[i*y+j] - ('a'-'A'));
            else
                // Card with backside up
                printf("  #");
        }
        printf("\n");
    }
}

// Let the player pick a card
void pickCard(char board[], int guess[], int x, int y)
{
    // Check if this is the first or second card to pick
    int row = (guess[0] == -1) ? 0 : 2;
    int col = (guess[1] == -1) ? 1 : 3;
    
    do
    {
        // Subtle indication as to where in the process we're at
        if (row == 0)
            printf("\nPick a card (row col): ");
        else
            printf("\nPick a second card: ");
        
        // Take input from player
        scanf("%d %d", &guess[row], &guess[col]);
        // Convert player's choice to zero based array index
        guess[row] -= 1;
        guess[col] -= 1;
        
        // Handle incorrect input from the player
        if (guess[0] == guess[2] && guess[1] == guess[3]) {
            printf("Can't pick same card twice.");
            continue;
        }
        else if (guess[0] >= x || guess[1] >= y || guess[2] >= x || guess[3] >= y) {
            printf("Card outside of board.");
            continue;
        }
        else if (guess[0] > -1 && board[(guess[0]) * y + guess[1]] < 'a') {
            printf("Card already solved.");
            continue;
        }
        else if (guess[2] > -1 && board[(guess[2]) * y + guess[3]] < 'a') {
            printf("Card already solved.");
            continue;
        }
        else
            break;
    } while (1);
}

// Check if the player picked two identical cards
void checkCards(char board[], int guess[], int x, int y)
{
    if (board[guess[0] * y + guess[1]] == board[guess[2] * y + guess[3]])
    {
        // If the guess is correct, convert to upper case letter
        board[guess[0] * y + guess[1]] -= ('a'-'A');
        board[guess[2] * y + guess[3]] -= ('a'-'A');
        printf("\nCorrect!\n");
    }
    else
    {
        printf("\nSorry. Try again.\n");
    }
}
    
// Check if there are any cards left (unsolved are lower case letters)
int checkGame(char board[], int x, int y)
{
    int i;
    for (i = 0; i < x*y; i++)
    {
        // If there are any lowercase letters left, continue game
        if (board[i] >= 'a')
            return 0;
    }
    return 1;
}

// Clear the current guess
void clearGuess(int guess[])
{
    int i;
    for (i = 0; i < 4; i++)
    {
        guess[i] = -1;
    }
}