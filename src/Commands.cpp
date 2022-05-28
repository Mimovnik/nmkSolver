#include "Commands.h"

#include <iostream>

char opponent(char activePlayer) {
    if (activePlayer == '1') {
        return '2';
    }
    return '1';
}

char getCell(char* board, int rowWidth, int x, int y) {
    return board[y * rowWidth + x];
}

bool won(char player, char* board, int width, int height,
         int consecutiveToWin) {
    // for all cells
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // check possible continuous lines in all directions
            int d = 4;
            while (d--) {
                int continuousSigns = 0;
                for (int l = 0; l < consecutiveToWin; l++) {
                    switch (d) {
                        // right
                        case 3:
                            if (x + l >= width) {
                                break;
                            }
                            if (getCell(board, width, x + l, y) == player) {
                                continuousSigns++;
                            }
                            break;
                        // right down
                        case 2:
                            if (x + l >= width || y + l >= height) {
                                break;
                            }
                            if (getCell(board, width, x + l, y + l) == player) {
                                continuousSigns++;
                            }
                            break;
                        // down
                        case 1:
                            if (y + l >= height) {
                                break;
                            }
                            if (getCell(board, width, x, y + l) == player) {
                                continuousSigns++;
                            }
                            break;
                        // down left
                        case 0:
                            if (x - l < 0 || y + l >= height) {
                                break;
                            }
                            if (getCell(board, width, x - l, y + l) == player) {
                                continuousSigns++;
                            }
                            break;
                    }
                    if (continuousSigns == consecutiveToWin) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void printBoard(int width, int height, char* board) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << getCell(board, width, x, y);
            if (x != width - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

int possibleMovesCutIfGameOver(char* board, int width, int height,
                               int consecutiveToWin, char activePlayer,
                               bool cut, bool* isWinner) {
    int posMoves = 0;
    for (int i = 0; i < width * height; i++) {
        if (board[i] == '0') {
            posMoves++;
            board[i] = activePlayer;
            if (cut &&
                won(activePlayer, board, width, height, consecutiveToWin)) {
                *isWinner = true;
                return 1;
            }
            board[i] = '0';
        }
    }
    return posMoves;
}

void genAllPosMov(bool cut) {
    // consecutiveToWin- number of adjacent cells in continuous vertical,
    // horizontal or diagonal line required to win
    int width, height, consecutiveToWin;
    char activePlayer;
    std::cin >> height >> width >> consecutiveToWin >> activePlayer;

    char* board = new char[width * height];
    for (int i = 0; i < width * height; i++) {
        std::cin >> board[i];
    }

    if (won(opponent(activePlayer), board, width, height, consecutiveToWin)) {
        std::cout << 0 << std::endl;
        delete[] board;
        return;
    }
    bool isWinner = false;
    std::cout << possibleMovesCutIfGameOver(board, width, height,
                                            consecutiveToWin, activePlayer, cut,
                                            &isWinner)
              << std::endl;

    if (isWinner) {
        printBoard(width, height, board);
    }else{
        for (int i = 0; i < width * height; i++) {
            if (board[i] == '0') {
                board[i] = activePlayer;

                printBoard(width, height, board);

                board[i] = '0';
            }
        }
    }

    delete[] board;
}
