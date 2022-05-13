#include "Commands.h"

#include <iostream>

bool equals(const char* str1, const char* str2) {
    for (int i = 0; i < MAX_LINE_LENGTH; i++) {
        if (str1[i] != str2[i]) {
            return false;

        } else if (str1[i] == '\0' || str2[i] == '\0') {
            return true;
        }
    }
    return true;
}

char opponent(char activePlayer) {
    if (activePlayer == '1') {
        return '2';
    }
    return '1';
}

char getCell(char* board, int n, int x, int y) { return board[y * n + x]; }

bool won(char player, char* board, int n, int m, int k) {
    for (int y = 0; y < m; y++) {
        for (int x = 0; x < n; x++) {
            // check possible continuous lines in all directions
            int d = 4;
            while (d--) {
                int continuousSigns = 0;
                for (int l = 0; l < k; l++) {
                    switch (d) {
                        case 3:
                            if (x + l >= n) {
                                break;
                            }
                            if (getCell(board, n, x + l, y) == player) {
                                continuousSigns++;
                            }
                            break;
                        case 2:
                            if (x + l >= n || y + l >= m) {
                                break;
                            }
                            if (getCell(board, n, x + l, y + l) == player) {
                                continuousSigns++;
                            }
                            break;
                        case 1:
                            if (y + l >= m) {
                                break;
                            }
                            if (getCell(board, n, x, y + l) == player) {
                                continuousSigns++;
                            }
                            break;
                        case 0:
                            if (x - l < 0 || y + l >= m) {
                                break;
                            }
                            if (getCell(board, n, x - l, y + l) == player) {
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
    // n- row length, m- rows count
    // k- number of adjacent cells in continuous vertical, horizontal or
    // diagonal line required to win
    int n, m, k;
    int posMoves = 0;
    char activePlayer;
    std::cin >> n >> m >> k >> activePlayer;

    char* board = new char[n * m];
    for (int i = 0; i < n * m; i++) {
        std::cin >> board[i];
        if (board[i] == '0') {
            posMoves++;
        }
    }

    if (won(opponent(activePlayer), board, n, m, k)) {
        std::cout << 0 << std::endl;
        delete[] board;
        return;
    }

    std::cout << posMoves << std::endl;
    for (int i = 0; i < n * m; i++) {
        if (board[i] == '0') {
            board[i] = activePlayer;
            for (int y = 0; y < m; y++) {
                for (int x = 0; x < n; x++) {
                    std::cout << getCell(board, n, x, y);
                    if(x != n - 1){
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