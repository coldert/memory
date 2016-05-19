#ifndef MEMORY
#define MEMORY

// Define a game settings object
typedef struct gameSettings {
    int gameOn, rounds, noOfCards, maxCards, width, height;
} Game;

void getNoOfCards(Game *game);
void calculateBoardSize(Game *game);
void init(char board[], Game *game);
void drawBoard(char board[], int guess[], Game *game);
void pickCard(char board[], int guess[], Game *game);
void checkCards(char board[], int guess[], Game *game);
int checkGame(char board[], Game *game);
void clearGuess(int guess[]);

#endif