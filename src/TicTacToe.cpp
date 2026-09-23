#include "TicTacToe.h"
#include <algorithm>
#include <limits>

TicTacToe::TicTacToe(size_t boardSize, size_t winLength, size_t maxDepth)
    : board_size(boardSize),
      win_length(winLength),
      max_depth(maxDepth),
      board(boardSize * boardSize, EMPTY) {
    if (board_size == 3 && win_length == 3) {
        max_depth = 9;
    }
}

bool TicTacToe::isMoveValid(size_t row, size_t col) const {
    return row < board_size && col < board_size && board[getIndex(row, col)] == EMPTY;
}

void TicTacToe::makeMove(size_t row, size_t col, char player) {
    board[getIndex(row, col)] = player;
}

void TicTacToe::undoMove(size_t row, size_t col) {
    board[getIndex(row, col)] = EMPTY;
}

bool TicTacToe::checkWinAt(size_t row, size_t col, char player) const {
    const int dr[4] = {0, 1, 1, -1};
    const int dc[4] = {1, 0, 1, 1};

    for (size_t dir = 0; dir < 4; ++dir) {
        size_t count = 1;

        for (int step = 1; step < static_cast<int>(win_length); ++step) {
            int nr = static_cast<int>(row) + dr[dir] * step;
            int nc = static_cast<int>(col) + dc[dir] * step;
            if (nr < 0 || nr >= static_cast<int>(board_size) || nc < 0 || nc >= static_cast<int>(board_size)) {
                break;
            }
            if (board[getIndex(static_cast<size_t>(nr), static_cast<size_t>(nc))] == player) {
                count++;
            } else {
                break;
            }
        }

        for (int step = 1; step < static_cast<int>(win_length); ++step) {
            int nr = static_cast<int>(row) - dr[dir] * step;
            int nc = static_cast<int>(col) - dc[dir] * step;
            if (nr < 0 || nr >= static_cast<int>(board_size) || nc < 0 || nc >= static_cast<int>(board_size)) {
                break;
            }
            if (board[getIndex(static_cast<size_t>(nr), static_cast<size_t>(nc))] == player) {
                count++;
            } else {
                break;
            }
        }

        if (count >= win_length) {
            return true;
        }
    }
    return false;
}

bool TicTacToe::isBoardFull() const {
    for (char cell : board) {
        if (cell == EMPTY) {
            return false;
        }
    }
    return true;
}

int TicTacToe::evaluateBoard() {
    int score = 0;

    for (size_t i = 0; i < board_size; ++i) {
        size_t ai_row_count = 0, human_row_count = 0;
        size_t ai_col_count = 0, human_col_count = 0;

        for (size_t j = 0; j < board_size; ++j) {
            char row_val = board[getIndex(i, j)];
            if (row_val == AI) ai_row_count++;
            else if (row_val == HUMAN) human_row_count++;

            char col_val = board[getIndex(j, i)];
            if (col_val == AI) ai_col_count++;
            else if (col_val == HUMAN) human_col_count++;
        }

        if (ai_row_count == win_length - 1 && human_row_count == 0) score += 100;
        else if (human_row_count == win_length - 1 && ai_row_count == 0) score -= 100;

        if (ai_col_count == win_length - 1 && human_col_count == 0) score += 100;
        else if (human_col_count == win_length - 1 && ai_col_count == 0) score -= 100;
    }

    size_t ai_diag = 0, human_diag = 0;
    size_t ai_antidiag = 0, human_antidiag = 0;

    for (size_t i = 0; i < board_size; ++i) {
        char diag_val = board[getIndex(i, i)];
        if (diag_val == AI) ai_diag++;
        else if (diag_val == HUMAN) human_diag++;

        char antidiag_val = board[getIndex(i, board_size - i - 1)];
        if (antidiag_val == AI) ai_antidiag++;
        else if (antidiag_val == HUMAN) human_antidiag++;
    }

    if (ai_diag == win_length - 1 && human_diag == 0) score += 100;
    else if (human_diag == win_length - 1 && ai_diag == 0) score -= 100;

    if (ai_antidiag == win_length - 1 && human_antidiag == 0) score += 100;
    else if (human_antidiag == win_length - 1 && ai_antidiag == 0) score -= 100;

    return score;
}

int TicTacToe::minmax(size_t depth, int alpha, int beta, bool isMaximizing, size_t last_row, size_t last_col) {
    if (last_row != std::numeric_limits<size_t>::max()) {
        char last_player = isMaximizing ? HUMAN : AI;
        if (checkWinAt(last_row, last_col, last_player)) {
            return (last_player == AI) ? (10000 - static_cast<int>(depth)) : (-10000 + static_cast<int>(depth));
        }
    }

    if (isBoardFull()) {
        return 0;
    }

    if (depth >= max_depth) {
        return evaluateBoard();
    }

    if (isMaximizing) {
        int best_score = -50000;
        for (size_t r = 0; r < board_size; ++r) {
            for (size_t c = 0; c < board_size; ++c) {
                if (board[getIndex(r, c)] == EMPTY) {
                    makeMove(r, c, AI);
                    int score = minmax(depth + 1, alpha, beta, false, r, c);
                    undoMove(r, c);
                    best_score = std::max(score, best_score);
                    alpha = std::max(alpha, best_score);
                    if (beta <= alpha) {
                        return best_score;
                    }
                }
            }
        }
        return best_score;
    } else {
        int best_score = 50000;
        for (size_t r = 0; r < board_size; ++r) {
            for (size_t c = 0; c < board_size; ++c) {
                if (board[getIndex(r, c)] == EMPTY) {
                    makeMove(r, c, HUMAN);
                    int score = minmax(depth + 1, alpha, beta, true, r, c);
                    undoMove(r, c);
                    best_score = std::min(score, best_score);
                    beta = std::min(beta, best_score);
                    if (beta <= alpha) {
                        return best_score;
                    }
                }
            }
        }
        return best_score;
    }
}

std::pair<size_t, size_t> TicTacToe::findBestMove() {
    int best_score = -50000;
    std::pair<size_t, size_t> best_move = {0, 0};

    for (size_t r = 0; r < board_size; ++r) {
        for (size_t c = 0; c < board_size; ++c) {
            if (board[getIndex(r, c)] == EMPTY) {
                makeMove(r, c, AI);
                int score = minmax(0, -50000, 50000, false, r, c);
                undoMove(r, c);
                if (score > best_score) {
                    best_score = score;
                    best_move = {r, c};
                }
            }
        }
    }
    return best_move;
}

void TicTacToe::printBoard() const {
    for (size_t r = 0; r < board_size; ++r) {
        for (size_t c = 0; c < board_size; ++c) {
            std::cout << " " << board[getIndex(r, c)] << " ";
            if (c != board_size - 1) {
                std::cout << "|";
            }
        }
        std::cout << "\n";
        if (r != board_size - 1) {
            for (size_t i = 0; i < board_size; ++i) {
                std::cout << "---";
                if (i != board_size - 1) std::cout << "+";
            }
            std::cout << "\n";
        }
    }
}

void TicTacToe::playGame() {
    std::cout << "You play as 'O'. Type row and column (0 to " << board_size - 1 << ").\n";

    char current_player = HUMAN;

    while (true) {
        printBoard();

        if (current_player == HUMAN) {
            size_t row, col;
            std::cout << "Move (row col): ";
            if (!(std::cin >> row >> col)) {
                return;
            }

            if (isMoveValid(row, col)) {
                makeMove(row, col, current_player);
                if (checkWinAt(row, col, current_player)) {
                    printBoard();
                    std::cout << "You won!\n";
                    return;
                } else if (isBoardFull()) {
                    printBoard();
                    std::cout << "Tie!\n";
                    return;
                }
                current_player = AI;
            } else {
                std::cout << "Invalid move, try again.\n";
            }
        } else {
            std::pair<size_t, size_t> move = findBestMove();
            makeMove(move.first, move.second, current_player);
            std::cout << "AI placed 'X' at: " << move.first << " " << move.second << "\n";

            if (checkWinAt(move.first, move.second, current_player)) {
                printBoard();
                std::cout << "AI won!\n";
                return;
            } else if (isBoardFull()) {
                printBoard();
                std::cout << "Tie!\n";
                return;
            }
            current_player = HUMAN;
        }
    }
}