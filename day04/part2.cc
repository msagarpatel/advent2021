#include <iostream>
#include <array>
#include <sstream>
#include <vector>

// This class should really be factored out since it's the same as part1.cc.
class BingoBoard {
public:
	// assume boards are square
	static const uint dim = 5;

private:
	std::array<std::array<uint, dim>, dim> board;
	// we could avoid this bool array by storing -1 for found tokens
	// lower memory usage would also help with CPU cache pressure
	std::array<std::array<bool, dim>, dim> bool_board;
	bool _won;

	bool check_win(const uint row, const uint col) {
		// check vertical
		bool flag = true;
		for (uint i = 0; i < dim; i++) {
			if (!bool_board[row][i]) {
				// don't return here since we can still check horizontal
				flag = false;
				break;
			}
		}
		if (flag) {
			_won = true;
			return flag;
		}

		// check horizontal
		for (uint i = 0; i < dim; i++) {
			if (!bool_board[i][col])
				return false;
		}

		_won = true;
		return true;
	}

public:
	BingoBoard() : board{},
	               bool_board{},
	               _won(false) {
		for (uint i = 0; i < dim; i++) {
			for (uint j = 0; j < dim; j++) {
				uint tile;
				if (std::cin >> tile)
					board[i][j] = tile;
				else
					throw std::invalid_argument( "ran out of input");
			}
		}
	}

	/*
	 * Is it more efficient to:
	 *   1. check for a win in one row and one column each time a token matches, or
	 *   2. check for a win in the entre board at the end of the function?
	 *
	 * If the board can have multiple tiles with the same number, then it depends on the
	 * probability of a token matching.
	 *
	 * If tiles are unique on a given board, then (1) is always more efficient for boards larger
	 * than 1x1.
	 */
	bool play_token(const uint token) {
		for (uint i = 0; i < dim; i++) {
			for (uint j = 0; j < dim; j++) {
				if (board[i][j] == token) {
					bool_board[i][j] = true;
					// check for win
					if (check_win(i, j))
						return true;
					// TODO: can only return if a given token can only occur once on a board.
					// return check_win(i, j);
				}
			}
		}

		return false;
	}

	// If we were using bool_board, we still couldn't use using std::accumulate here since the
	// sentinel can't be 0.
	uint score() {
		uint score = 0;
		for (uint i = 0; i < dim; i++) {
			for (uint j = 0; j < dim; j++) {
				if (!bool_board[i][j])
					score += board[i][j];
			}
		}
		return score;
	}

	void print() {
		// print board
		std::cout << "BOARD" << std::endl;
		for (uint i = 0; i < dim; i++) {
			for (uint j = 0; j < dim; j++)
				std::cout << board[i][j] << "\t";
			std::cout << std::endl;
		}

		// print bool_board
		std::cout << "BOOL BOARD" << std::endl;
		for (uint i = 0; i < dim; i++) {
			for (uint j = 0; j < dim; j++)
				std::cout << bool_board[i][j] << "\t";
			std::cout << std::endl;
		}
	}

	bool won() const {
		return _won;
	}
};

int main() {
	// read bingo tokens line
	std::string line;
	std::cin >> line;
	std::stringstream tokens(line);

	// read and instantiate bingo boards
	std::vector<BingoBoard> boards;
	try {
		while (true)
			boards.push_back(BingoBoard());
	} catch (...) {
		// ignore assuming we've reached the end of input
	}

	// iterate over tokens
	for (uint cur; tokens >> cur;) {
		// eat the comma
		tokens.get();

		// play tokens in boards
		// This assumes that only one board can possibly win in a single drawing. If multiple
		// boards could win, then the first in the input order wins.
		for (auto i = boards.begin(); i != boards.end();) {
			if (i->play_token(cur)) {
				if (boards.size() == 1)
					break;
				i = boards.erase(i);
			}
			else
				i++;
		}

		// found the last board to win
		if (boards.size() == 1 && boards.front().won()) {
			boards.front().print();
			std::cout << "Last score = " << boards.front().score() * cur << std::endl;
			break;
		}
	}

	return EXIT_SUCCESS;
}
