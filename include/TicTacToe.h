#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <vector>
#include <utility>

class TicTacToe {
private:
    static constexpr char EMPTY = ' ';
    static constexpr char HUMAN = 'O';
    static constexpr char AI = 'X';

    size_t board_size;
    size_t win_length;
    size_t max_depth;
    std::vector<char> board;

    inline size_t getIndex(size_t row, size_t col) const {
        return row * board_size + col;
    }

    int evaluateBoard();
    int minmax(size_t depth, int alpha, int beta, bool isMaximizing, size_t last_row, size_t last_col);

public:
    TicTacToe(size_t boardSize, size_t winLength, size_t maxDepth = 6);
    void playGame();
    bool isMoveValid(size_t row, size_t col) const;
    void makeMove(size_t row, size_t col, char player);
    void undoMove(size_t row, size_t col);
    bool checkWinAt(size_t row, size_t col, char player) const;
    bool isBoardFull() const;
    std::pair<size_t, size_t> findBestMove();
    void printBoard() const;
};

#endif // TICTACTOE_H