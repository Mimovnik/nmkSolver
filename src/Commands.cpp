#include "Commands.h"

#include <iostream>

void genAllPosMov() {
    // n- row length, m- rows count
    // k- number of adjacent cells in continuous vertical, horizontal or
    // diagonal line
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

    std::cout << posMoves << std::endl;
    for (int i = 0; i < n * m; i++) {
        if (board[i] == '0') {
            board[i] = activePlayer;
            for (int y = 0; y < m; y++) {
                for (int x = 0; x < n; x++) {
                    std::cout << board[n * y + x] << ' ';
                }
                std::cout << std::endl;
            }
            board[i] = '0';
            std::cout << std::endl;
        }
    }

    delete[] board;
}