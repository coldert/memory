#ifndef MEMORY
#define MEMORY

void init(char board[], int size);
void drawBoard(char board[], int guess[], int x, int y);
void pickCard(char board[], int guess[], int x, int y);
void checkCards(char board[], int guess[], int x, int y);
int checkGame(char board[], int x, int y);
void clearGuess(int guess[]);

#endif