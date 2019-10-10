#pragma once
#include<array>
#include<iostream>

#include <Puzzle_2048/Game.h>
#include <Puzzle_2048/Block.h>
#include<effolkronium/random.hpp>

Game::Game() {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			board[i][j] = Block::MakeBlock();
		}
	}

	direction = Direction::Invalid;
}

void Game::SetDirection(Direction dir) {
	direction = dir;
}

//TODO
void Game::MakeRandomBlock() {
	using random = effolkronium::random_static;
	int rand_x;
	int rand_y;

	do {
		rand_x = random::get(0, 3);
		rand_y = random::get(0, 3);
	} while (board[rand_x][rand_y].GetScore() != 0);
	//TODO: score random하게 결정
	
	board[rand_x][rand_y].SetScore(2);

}

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
//					board[x][y].SetScore(board[x][y + 1]);
//					board[x][y + 1].SetScoreZero();
					board[x][y] = std::move(board[x][y + 1]);
					continue;
				}

				//이동하려는 방향에 있는 칸과 현재칸이 같은 숫자여서 2배하는 경우
				else if (board[x][y].GetScore() == board[x][y + 1].GetScore() && board[x][y].GetIsvariable() == true) {
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
				if (board[x][y].GetScore() == 0 && board[x][y - 1].GetScore() != 0) {
					board[x][y].SetScore(board[x][y - 1]);
					board[x][y - 1].SetScoreZero();
					continue;
				}

				//이동하려는 방향에 있는 칸과 현재칸이 같은 숫자여서 2배하는 경우
				else if (board[x][y].GetScore() == board[x][y - 1].GetScore()) {
					board[x][y].SetScoreDouble();
					board[x][y - 1].SetScoreZero();
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
	int flag = 0;
	for (y = 0; y < 4; y++) {
		flag = 0;
		for (i = 3; i >= 0; i--) {
			for (x = 0; x < i; x++) {
				//이동하려는 방향에 0이 있고 이동하는 칸이 0이 아니라서 숫자가 그대로 이동하는 경우
				if (board[x][y].GetScore() == 0 && board[x + 1][y].GetScore() != 0) {
					board[x][y].SetScore(board[x + 1][y]);
					board[x + 1][y].SetScoreZero();
					continue;
				}

				//이동하려는 방향에 있는 칸과 현재칸이 같은 숫자여서 2배하는 경우
				else if (board[x][y].GetScore() == board[x + 1][y].GetScore()
					) {
					board[x][y].SetScoreDouble();
					board[x + 1][y].SetScoreZero();
					flag = 1;
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
				if (board[x][y].GetScore() == 0 && board[x - 1][y].GetScore() != 0) {
					board[x][y].SetScore(board[x - 1][y]);
					board[x - 1][y].SetScoreZero();
					continue;
				}

				//이동하려는 방향에 있는 칸과 현재칸이 같은 숫자여서 2배하는 경우
				else if (board[x][y].GetScore() == board[x - 1][y].GetScore() && i == 0) {
					board[x][y].SetScoreDouble();
					board[x - 1][y].SetScoreZero();
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
	char zero_shape = '-';
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (board[j][i].GetScore() == 0) {
				printf("%4c", zero_shape);
			}

			else {
				printf("%4d", board[j][i].GetScore());
			}
		}
		printf("\n");
	}
}