#ifndef COMMANDS_H
#define COMMANDS_H

void genAllPosMov(bool cut);

void solveGame();

int minimax(char* board, int width, int height, int consecutiveToWin, int depth,
            int alpha, int beta, bool isMaximizing);

int* getScore(char* board, int width, int height, int consecutiveToWin);

char getWinner(char* board, int width, int height, int consecutiveToWin);

char opponent(char activePlayer);

char getCell(char* board, int width, int x, int y);

void printBoard(int width, int height, char* board);

int countMovesAndCheckIfWinner(char* board, int width, int height,
                               int consecutiveToWin, char activePlayer,
                               bool cut, bool* isWinner);

void printAllPosMov(char* board, int width, int height, char activePlayer);

char getConsecutive(char* arr, int stepCount, int amount, int stepSize);

#endif