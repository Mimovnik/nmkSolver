#include "Commands.h"

#include <iostream>

#define EMPTY_CELL '0'
#define PLAYER1 '1'
#define PLAYER2 '2'

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

int* getScore(char* board, int width, int height, int consecutiveToWin) {
    if (won('1', board, width, height, consecutiveToWin)) {
        return new int(1);
    } else if (won('2', board, width, height, consecutiveToWin)) {
        return new int(-1);
    } else {
        int posMoves = 0;
        for (int i = 0; i < width * height; i++) {
            if (board[i] == '0') {
                posMoves++;
            }
        }
        if (posMoves == 0) {
            return new int(0);
        }
    }
    return nullptr;
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

void printAllPosMov(char* board, int width, int height, char activePlayer) {
    for (int i = 0; i < width * height; i++) {
        if (board[i] == '0') {
            board[i] = activePlayer;
            printBoard(width, height, board);
            board[i] = '0';
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

    if (won(opponent(activePlayer), board, width, height, consecutiveToWin)) {
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

int minimax(char* board, int width, int height, int consecutiveToWin, int depth,
            bool isMaximizing) {
    int* result = getScore(board, width, height, consecutiveToWin);
    if (result != nullptr) {
        int score = *result;
        delete result;
        return score;
    }
    if (isMaximizing) {
        int bestScore = -100;
        for (int i = 0; i < width * height; i++) {
            if (board[i] == EMPTY_CELL) {
                board[i] = PLAYER1;
                int score = minimax(board, width, height, consecutiveToWin,
                                    depth + 1, false);
                board[i] = EMPTY_CELL;
                bestScore = std::max(score, bestScore);
            }
        }
        return bestScore;
    } else {
        int bestScore = 100;
        for (int i = 0; i < width * height; i++) {
            if (board[i] == EMPTY_CELL) {
                board[i] = PLAYER2;
                int score = minimax(board, width, height, consecutiveToWin,
                                    depth + 1, true);
                board[i] = EMPTY_CELL;
                bestScore = std::min(score, bestScore);
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
    if (activePlayer == '2') {
        isMaximizing = false;
    }

    char* board = new char[width * height];
    for (int i = 0; i < width * height; i++) {
        std::cin >> board[i];
    }


            int score = minimax(board, width, height, consecutiveToWin, 0,
                                isMaximizing);
            switch (score) {
                case 0:
                    std::cout << "BOTH_PLAYERS_TIE" << std::endl;
                    break;
                case 1:
                    std::cout << "FIRST_PLAYER_WINS" << std::endl;
                    break;
                case 2:
                    std::cout << "SECOND_PLAYER_WINS" << std::endl;
                    break;
            }

    // for (int i = 0; i < width * height; i++) {
    //     if (board[i] == '0') {
    //         board[i] = activePlayer;
    //         int score = minimax(board, width, height, consecutiveToWin, 0,
    //                             isMaximizing);
    //         switch (score) {
    //             case 0:
    //                 std::cout << "BOTH_PLAYERS_TIE" << std::endl;
    //                 break;
    //             case 1:
    //                 std::cout << "FIRST_PLAYER_WINS" << std::endl;
    //                 break;
    //             case 2:
    //                 std::cout << "SECOND_PLAYER_WINS" << std::endl;
    //                 break;
    //         }
    //         board[i] = '0';
    //     }
    // }
}
