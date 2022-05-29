#include "Commands.h"

#include <algorithm>
#include <iostream>

#define EMPTY_CELL '0'
#define PLAYER1 '1'
#define PLAYER2 '2'
#define INFINITY 100

char opponent(char activePlayer) {
    if (activePlayer == PLAYER1) {
        return PLAYER2;
    }
    return PLAYER1;
}

char getCell(char* board, int width, int x, int y) {
    return board[y * width + x];
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

int countMovesAndCheckIfWinner(char* board, int width, int height,
                               int consecutiveToWin, char activePlayer,
                               bool cut, bool* isWinner) {
    int posMoves = 0;
    for (int i = 0; i < width * height; i++) {
        if (board[i] == EMPTY_CELL) {
            posMoves++;
            board[i] = activePlayer;
            if (cut && getWinner(board, width, height, consecutiveToWin) ==
                           activePlayer) {
                *isWinner = true;
                return 1;
            }
            board[i] = EMPTY_CELL;
        }
    }
    return posMoves;
}

void printAllPosMov(char* board, int width, int height, char activePlayer) {
    for (int i = 0; i < width * height; i++) {
        if (board[i] == EMPTY_CELL) {
            board[i] = activePlayer;
            printBoard(width, height, board);
            board[i] = EMPTY_CELL;
        }
    }
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

    if (getWinner(board, width, height, consecutiveToWin) ==
        opponent(activePlayer)) {
        std::cout << 0 << std::endl;
        delete[] board;
        return;
    }
    bool isWinner = false;
    std::cout << countMovesAndCheckIfWinner(board, width, height,
                                            consecutiveToWin, activePlayer, cut,
                                            &isWinner)
              << std::endl;

    if (isWinner) {
        printBoard(width, height, board);
    } else {
        printAllPosMov(board, width, height, activePlayer);
    }

    delete[] board;
}

char getConsecutive(char* arr, int stepCount, int amount, int stepsize) {
    if (stepCount < amount) {
        return NULL;
    }
    char last = NULL;
    int count = 0;
    for (int i = 0, x = 0; i < stepCount; i++, x += stepsize) {
        if (arr[x] != last || arr[x] == EMPTY_CELL) {
            last = arr[x];
            count = 0;
        }
        count += 1;
        if (amount <= count) {
            return arr[x];
        }
    }
    return NULL;
}

char getWinner(char* board, int width, int height, int consecutiveToWin) {
    // horizontal
    // ---
    // 000
    // 000
    for (int y = 0; y < height; y++) {
        char win =
            getConsecutive(board + y * width, width, consecutiveToWin, 1);
        if (win != NULL) {
            return win;
        }
    }
    // vertical
    // |00
    // |00
    // |00
    for (int x = 0; x < width; x++) {
        char win = getConsecutive(board + x, height, consecutiveToWin, width);
        if (win != NULL) {
            return win;
        }
    }
    /* ---\\\backslash diagonals\\\--- */
    // longest diagonals
    // \\\00
    // 0\\\0
    // 00\\\

    for (int d = 0; d < std::abs(width - height) + 1; d++) {
        char win = getConsecutive(
            width > height ? board + d : board + d * width,
            std::min(width, height), consecutiveToWin, width + 1);
        if (win != NULL) {
            return win;
        }
    }
    // shorter diagonals
    // 000\\
    // \000\
    // \\000
    int leftBotAdd = std::abs(width - height);
    int rightTopAdd = 0;
    if (width > height) {
        leftBotAdd = 0;
        rightTopAdd = std::abs(width - height);
    }
    for (int s = 1; s <= (std::min(width, height) - consecutiveToWin); s++) {
        // left bottom diagonals
        // 00000
        // \0000
        // \\000
        char win = getConsecutive(board + width * (s + leftBotAdd),
                                  std::min(width, height) - s, consecutiveToWin,
                                  width + 1);
        if (win != NULL) {
            return win;
        }
        // right top diagonals
        // 000\\
        // 0000\
        // 00000
        win =
            getConsecutive(board + s + rightTopAdd, std::min(width, height) - s,
                           consecutiveToWin, width + 1);
        if (win != NULL) {
            return win;
        }
    }
    /* ---///slash diagonals///--- */
    // longest diagonals
    // 00///
    // 0///0
    // ///00
    for (int d = 0; d < std::abs(width - height) + 1; d++) {
        char win = getConsecutive(
            width > height ? board + width - 1 - d
                           : board + width - 1 + d * width,
            std::min(width, height), consecutiveToWin, width - 1);
        if (win != NULL) {
            return win;
        }
    }
    // shorter diagonals
    // //000
    // /000/
    // 000//
    int leftTopAdd = 0;
    int rightBotAdd = std::abs(width - height);
    if (width > height) {
        leftTopAdd = std::abs(width - height);
        rightBotAdd = 0;
    }
    for (int s = 1; s <= (std::min(width, height) - consecutiveToWin); s++) {
        // left top diagonals
        // //000
        // /0000
        // 00000
        char win = getConsecutive(board + width - 1 - (s + leftTopAdd),
                                  std::min(width, height) - s, consecutiveToWin,
                                  width - 1);
        if (win != NULL) {
            return win;
        }
        // right bottom diagonals
        // 00000
        // 0000/
        // 000//
        win = getConsecutive(board + width - 1 + width * (s + rightBotAdd),
                             std::min(width, height) - s, consecutiveToWin,
                             width - 1);
        if (win != NULL) {
            return win;
        }
    }
    return NULL;
}

int* getScore(char* board, int width, int height, int consecutiveToWin) {
    char winner = getWinner(board, width, height, consecutiveToWin);

    switch (winner) {
        case NULL:
            for (int i = 0; i < width * height; i++) {
                if (board[i] == EMPTY_CELL) {
                    return nullptr;
                }
            }
            return new int(0);
        case '1':
            return new int(-1);
        case '2':
            return new int(1);
        default:
            throw "There is no such winner! There is a bug in getWinner()";
    }
    return nullptr;
}

int minimax(char* board, int width, int height, int consecutiveToWin, int depth,
            int alpha, int beta, bool isMaximizing) {
    int* result = getScore(board, width, height, consecutiveToWin);
    if (result != nullptr) {
        int score = *result;
        delete result;
        return score;
    }
    if (isMaximizing) {
        int bestScore = -INFINITY;
        for (int i = 0; i < width * height; i++) {
            if (board[i] == EMPTY_CELL) {
                board[i] = PLAYER2;
                int score = minimax(board, width, height, consecutiveToWin,
                                    depth + 1, alpha, beta, false);
                board[i] = EMPTY_CELL;
                bestScore = std::max(score, bestScore);
                alpha = std::max(alpha, score);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = INFINITY;
        for (int i = 0; i < width * height; i++) {
            if (board[i] == EMPTY_CELL) {
                board[i] = PLAYER1;
                int score = minimax(board, width, height, consecutiveToWin,
                                    depth + 1, alpha, beta, true);
                board[i] = EMPTY_CELL;
                bestScore = std::min(score, bestScore);
                beta = std::min(beta, score);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        return bestScore;
    }
}

void solveGame() {
    int width, height, consecutiveToWin;
    char activePlayer;
    std::cin >> height >> width >> consecutiveToWin >> activePlayer;

    bool isMaximizing = true;
    if (activePlayer == '1') {
        isMaximizing = false;
    }

    char* board = new char[width * height];
    for (int i = 0; i < width * height; i++) {
        std::cin >> board[i];
    }

    int score = minimax(board, width, height, consecutiveToWin, 0, -INFINITY, INFINITY,
                        isMaximizing);
    switch (score) {
        case 0:
            std::cout << "BOTH_PLAYERS_TIE" << std::endl;
            break;
        case -1:
            std::cout << "FIRST_PLAYER_WINS" << std::endl;
            break;
        case 1:
            std::cout << "SECOND_PLAYER_WINS" << std::endl;
            break;
        default:
            throw "There is no such score! minimax() has a bug";
    }

    delete[] board;
}
