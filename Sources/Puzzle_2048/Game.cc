#pragma once
#include<array>
#include<iostream>

#include <Puzzle_2048/Game.h>
#include <Puzzle_2048/Block.h>
#include<effolkronium/random.hpp>

Game::Game() : block_num(0), direction(Direction::Invalid) {
	// board배열을 block으로 초기화
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			board[i][j] = Block::MakeBlock();
		}
	}
}

//현재 direction리턴
Direction Game::GetDirection()const {
	return direction;
}

//받은 인자로 direction 설정
void Game::SetDirection(Direction dir) {
	direction = dir;
}

//한 턴이 끝난 후 Isvariable을 true로 초기화
void Game::ResetIsvariable() {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			board[i][j].SetIsvariable(true);
		}
	}
}

//새로운 블럭을 생성
void Game::MakeRandomBlock() {
	using random = effolkronium::random_static;
	int rand_x;
	int rand_y;

	//block의 총 개수가 16개가 아닐때(다 차지 않았을때)
	if (block_num != 16) {
		//블록이 없는 (빈)위치 찾기
		do {
			rand_x = random::get(0, 3);
			rand_y = random::get(0, 3);
		} while (board[rand_x][rand_y].GetScore() != 0);

		// 4:2:1의 비율로 2, 4, 8블록이 생성
		int score = random::get({ 2, 2, 2, 2, 4, 4, 8 });
		board[rand_x][rand_y].SetScore(score);
		block_num++;

	}
}

// direction에 따라 행동결정
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

//위쪽 키를 눌렀을때
void Game::Move_up() {
	int x, y, i;
	for (x = 0; x < 4; x++) {
		for (i = 3; i >= 0; i--) {
			for (y = 0; y < i; y++) {
				//이동하려는 방향에 0이 있고 이동하는 칸이 0이 아니라서 숫자가 그대로 이동하는 경우
				if (board[x][y].GetScore() == 0 && board[x][y + 1].GetScore() != 0) {
					//숫자칸을 0칸에 대입한후 원래칸 초기화(swap)
					board[x][y] = std::move(board[x][y + 1]);
					continue;
				}

				//이동하려는 방향에 있는 칸과 현재칸이 같은 숫자여서 2배하는 경우
				else if (board[x][y].GetScore() == board[x][y + 1].GetScore() && board[x][y + 1].GetIsvariable() == true) {
					board[x][y].SetScoreDouble();
					board[x][y + 1].SetScoreZero();
					//이동가능성을 불가능으로 설정(2 2 2 -> 8 을 막음)
					board[x][y].SetIsvariable(false);
					//합쳐졌으니 총 블록개수 줄임
					block_num--;
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
					board[x][y] = std::move(board[x][y - 1]);
					continue;
				}

				//이동하려는 방향에 있는 칸과 현재칸이 같은 숫자여서 2배하는 경우
				else if (board[x][y].GetScore() == board[x][y - 1].GetScore()) {
					board[x][y].SetScoreDouble();
					board[x][y - 1].SetScoreZero();
					board[x][y].SetIsvariable(false);
					block_num--;
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
					board[x][y] = std::move(board[x + 1][y]);
					continue;
				}

				//이동하려는 방향에 있는 칸과 현재칸이 같은 숫자여서 2배하는 경우
				else if (board[x][y].GetScore() == board[x + 1][y].GetScore()) {
					board[x][y].SetScoreDouble();
					board[x + 1][y].SetScoreZero();
					board[x][y].SetIsvariable(false);
					block_num--;
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
					board[x][y] = std::move(board[x - 1][y]);
					continue;
				}

				//이동하려는 방향에 있는 칸과 현재칸이 같은 숫자여서 2배하는 경우
				else if (board[x][y].GetScore() == board[x - 1][y].GetScore() && i == 0) {
					board[x][y].SetScoreDouble();
					board[x - 1][y].SetScoreZero();
					board[x][y].SetIsvariable(false);
					block_num--;
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

//게임판 출력하는 함수
void Game::Print()const {
	std::cout << "'w' : move_up" << "\n";
	std::cout << "'a' : move_left" << "\n";
	std::cout << "'s' : move_down" << "\n";
	std::cout << "'d' : move_right" << "\n\n";

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