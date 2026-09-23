#include "TicTacToe.h"

int main() {
    size_t board_size = 3;
    size_t win_length = 3;

    std::cout << "Size of the board: ";
    if (!(std::cin >> board_size) || board_size < 3) {
        std::cerr << "Board size must be >= 3.\n";
        return 1;
    }

    std::cout << "Length of winning sequence: ";
    if (!(std::cin >> win_length) || win_length < 3 || win_length > board_size) {
        std::cerr << "Win length must be between 3 and board size.\n";
        return 1;
    }

    TicTacToe game(board_size, win_length);
    game.playGame();

    return 0;
}