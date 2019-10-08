#include <Puzzle_2048/Game.h>


Block Block::MakeBlock(int x, int y) {
	return Block(x, y);
}

Block& Block::operator+(const Block& rhs) {
	score += rhs.score;
	return *this;
}

int Block::GetScore()const {
	return score;
}

Pos Block::GetPos()const {
	return pos;
}

void Block::SetScore(Block target) {
	score = target.GetScore();
	target.SetScoreZero();
}

void Block::SetScore(int newscore) {
	score = newscore;
}

void Block::SetScoreZero() {
	score = 0;
}

void Block::SetScoreDouble() {
	score *= 2;
}

Block::Block(int x, int y) :pos(x, y), score(0) {};

Block::Block() : pos(0, 0), score(0) {};

Game::Game() {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			board[i][j] = Block::MakeBlock(i, j);
		}
	}

	direction = Direction::Invalid;
}

void Game::SetDirection(Direction dir) {
	direction = dir;
}

//TODO
void Game::MakeRandomBlock() {

}
/*
void Game::Randomtest() {
	srand(time(NULL));
	int rand_x;
	int rand_y;
	do {
		rand_x = rand() % 4;
		rand_y = rand() % 4;
	} while (board[rand_x][rand_y].GetScore() == 0);

	int score = (rand % 3 + 1) * 2;
	board[rand_x][board_y].SetScore(score);

}
*/

void Game::MoveDecision() {
	if (direction == Direction::Up) {
		Move_up();
	}

	else if (direction == Direction::Down) {
		Move_down();
	}

	else if (direction == Direction::Left) {
		Move_left();
	}

	else if (direction == Direction::Right) {
		Move_right();
	}
}

void Game::Move_up() {
	int x, y, i;
	for (x = 0; x < 4; x++) {
		for (i = 3; i >= 0; i--) {
			for (y = 0; y < i; y++) {
				//이동하려는 방향에 0이 있고 이동하는 칸이 0이 아니라서 숫자가 그대로 이동하는 경우
				if (board[x][y].GetScore() == 0 && board[x][y + 1].GetScore() != 0) {
					board[x][y].SetScore(board[x + 1][y]);
					board[x][y + 1].SetScoreZero();
					continue;
				}

				//이동하려는 방향에 있는 칸과 현재칸이 같은 숫자여서 2배하는 경우
				else if (board[x][y].GetScore() == board[x][y + 1].GetScore()) {
					board[x][y].SetScoreDouble();
					board[x][y + 1].SetScoreZero();
					continue;
				}

				//숫자 + 0 이거나 0 + 0 이어서 아무일도 일어나지 않는 경우
				else {
					continue;
				}
			}
		}
	}
}

void Game::Move_down() {
	int x, y, i;
	for (x = 0; x < 4; x++) {
		for (i = 0; i < 4; i++) {
			for (y = 3; y > i; y--) {
				//이동하려는 방향에 0이 있고 이동하는 칸이 0이 아니라서 숫자가 그대로 이동하는 경우
				if (board[x][y - 1].GetScore() == 0 && board[x][y].GetScore() != 0) {
					board[x][y - 1].SetScore(board[x][y]);
					board[x][y].SetScoreZero();
					continue;
				}

				//이동하려는 방향에 있는 칸과 현재칸이 같은 숫자여서 2배하는 경우
				else if (board[x - 1][y].GetScore() == board[x][y].GetScore()) {
					board[x - 1][y].SetScoreDouble();
					board[x][y].SetScoreZero();
					continue;
				}

				//숫자 + 0 이거나 0 + 0 이어서 아무일도 일어나지 않는 경우
				else {
					continue;
				}
			}
		}
	}
}

//블록이 왼쪽으로 모일때
void Game::Move_left() {
	int x, y, i;
	for (y = 0; y < 4; y++) {
		for (i = 3; i >= 0; i--) {
			for (x = 0; x < i; x++) {
				//이동하려는 방향에 0이 있고 이동하는 칸이 0이 아니라서 숫자가 그대로 이동하는 경우
				if (board[x][y].GetScore() == 0 && board[x + 1][y].GetScore() != 0) {
					board[x][y].SetScore(board[x + 1][y]);
					board[x + 1][y].SetScoreZero();
					continue;
				}

				//이동하려는 방향에 있는 칸과 현재칸이 같은 숫자여서 2배하는 경우
				else if (board[x][y].GetScore() == board[x + 1][y].GetScore()) {
					board[x][y].SetScoreDouble();
					board[x + 1][y].SetScoreZero();
					continue;
				}

				//숫자 + 0 이거나 0 + 0 이어서 아무일도 일어나지 않는 경우
				else {
					continue;
				}
			}
		}
	}

}

//블록이 오른쪽으로 모일때
void Game::Move_right() {
	int x, y, i;
	for (y = 0; y < 4; y++) {
		for (i = 0; i < 4; i++) {
			for (x = 3; x > i; x--) {
				//이동하려는 방향에 0이 있고 이동하는 칸이 0이 아니라서 숫자가 그대로 이동하는 경우
				if (board[x - 1][y].GetScore() == 0 && board[x][y].GetScore() != 0) {
					board[x - 1][y].SetScore(board[x][y]);
					board[x][y].SetScoreZero();
					continue;
				}

				//이동하려는 방향에 있는 칸과 현재칸이 같은 숫자여서 2배하는 경우
				else if (board[x - 1][y].GetScore() == board[x][y].GetScore()) {
					board[x - 1][y].SetScoreDouble();
					board[x][y].SetScoreZero();
					continue;
				}

				//숫자 + 0 이거나 0 + 0 이어서 아무일도 일어나지 않는 경우
				else {
					continue;
				}
			}
		}
	}
}

void Game::Print()const {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (board[i][j].GetScore() == 0) {
				printf("   -");
			}

			else {
				printf("%4d ", board[i][j].GetScore());
			}
		}
		printf("\n");
	}
}