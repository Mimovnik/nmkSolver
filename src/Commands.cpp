#include "Commands.h"

#include <iostream>

char opponent(char activePlayer) {
    if (activePlayer == '1') {
        return '2';
    }
    return '1';
}

char getCell(char* board, int rowWidth, int x, int y) { return board[y * rowWidth + x]; }

bool won(char player, char* board, int width, int height, int k) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // check possible continuous lines in all directions
            int d = 4;
            while (d--) {
                int continuousSigns = 0;
                for (int l = 0; l < k; l++) {
                    switch (d) {
                        case 3:
                            if (x + l >= width) {
                                break;
                            }
                            if (getCell(board, width, x + l, y) == player) {
                                continuousSigns++;
                            }
                            break;
                        case 2:
                            if (x + l >= width || y + l >= height) {
                                break;
                            }
                            if (getCell(board, width, x + l, y + l) == player) {
                                continuousSigns++;
                            }
                            break;
                        case 1:
                            if (y + l >= height) {
                                break;
                            }
                            if (getCell(board, width, x, y + l) == player) {
                                continuousSigns++;
                            }
                            break;
                        case 0:
                            if (x - l < 0 || y + l >= height) {
                                break;
                            }
                            if (getCell(board, width, x - l, y + l) == player) {
                                continuousSigns++;
                            }
                            break;
                    }
                    if (continuousSigns == k) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void genAllPosMov() {
    // k- number of adjacent cells in continuous vertical, horizontal or
    // diagonal line required to win
    int width, height, k;
    int posMoves = 0;
    char activePlayer;
    std::cin >> height >> width >> k >> activePlayer;

    char* board = new char[height * width];
    for (int i = 0; i < height * width; i++) {
        std::cin >> board[i];
        if (board[i] == '0') {
            posMoves++;
        }
    }

    if (won(opponent(activePlayer), board, width, height, k)) {
        std::cout << 0 << std::endl;
        delete[] board;
        return;
    }

    std::cout << posMoves << std::endl;
    for (int i = 0; i < height * width; i++) {
        if (board[i] == '0') {
            board[i] = activePlayer;
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    std::cout << getCell(board, width, x, y);
                    if(x != width - 1){
                        std::cout << " ";
                    }
                }
                std::cout << std::endl;
            }
            board[i] = '0';
        }
    }

    delete[] board;
}