#pragma once
#include<array>
#include<iostream>

#include <Puzzle_2048/Game.h>
#include <Puzzle_2048/Block.h>
#include<effolkronium/random.hpp>

Game::Game() : block_num(0), direction(Direction::Invalid) {
	// board�迭�� block���� �ʱ�ȭ
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			board[i][j] = Block::MakeBlock();
		}
	}
}

//���� direction����
Direction Game::GetDirection()const {
	return direction;
}

//���� ���ڷ� direction ����
void Game::SetDirection(Direction dir) {
	direction = dir;
}

//�� ���� ���� �� Isvariable�� true�� �ʱ�ȭ
void Game::ResetIsvariable() {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			board[i][j].SetIsvariable(true);
		}
	}
}

//���ο� ���� ����
void Game::MakeRandomBlock() {
	using random = effolkronium::random_static;
	int rand_x;
	int rand_y;

	//block�� �� ������ 16���� �ƴҶ�(�� ���� �ʾ�����)
	if (block_num != 16) {
		//����� ���� (��)��ġ ã��
		do {
			rand_x = random::get(0, 3);
			rand_y = random::get(0, 3);
		} while (board[rand_x][rand_y].GetScore() != 0);

		// 4:2:1�� ������ 2, 4, 8����� ����
		int score = random::get({ 2, 2, 2, 2, 4, 4, 8 });
		board[rand_x][rand_y].SetScore(score);
		block_num++;

	}
}

// direction�� ���� �ൿ����
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

//���� Ű�� ��������
void Game::Move_up() {
	int x, y, i;
	for (x = 0; x < 4; x++) {
		for (i = 3; i >= 0; i--) {
			for (y = 0; y < i; y++) {
				//�̵��Ϸ��� ���⿡ 0�� �ְ� �̵��ϴ� ĭ�� 0�� �ƴ϶� ���ڰ� �״�� �̵��ϴ� ���
				if (board[x][y].GetScore() == 0 && board[x][y + 1].GetScore() != 0) {
					//����ĭ�� 0ĭ�� �������� ����ĭ �ʱ�ȭ(swap)
					board[x][y] = std::move(board[x][y + 1]);
					continue;
				}

				//�̵��Ϸ��� ���⿡ �ִ� ĭ�� ����ĭ�� ���� ���ڿ��� 2���ϴ� ���
				else if (board[x][y].GetScore() == board[x][y + 1].GetScore() && board[x][y + 1].GetIsvariable() == true) {
					board[x][y].SetScoreDouble();
					board[x][y + 1].SetScoreZero();
					//�̵����ɼ��� �Ұ������� ����(2 2 2 -> 8 �� ����)
					board[x][y].SetIsvariable(false);
					//���������� �� ��ϰ��� ����
					block_num--;
					continue;
				}

				//���� + 0 �̰ų� 0 + 0 �̾ �ƹ��ϵ� �Ͼ�� �ʴ� ���
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
				//�̵��Ϸ��� ���⿡ 0�� �ְ� �̵��ϴ� ĭ�� 0�� �ƴ϶� ���ڰ� �״�� �̵��ϴ� ���
				if (board[x][y].GetScore() == 0 && board[x][y - 1].GetScore() != 0) {
					board[x][y] = std::move(board[x][y - 1]);
					continue;
				}

				//�̵��Ϸ��� ���⿡ �ִ� ĭ�� ����ĭ�� ���� ���ڿ��� 2���ϴ� ���
				else if (board[x][y].GetScore() == board[x][y - 1].GetScore()) {
					board[x][y].SetScoreDouble();
					board[x][y - 1].SetScoreZero();
					board[x][y].SetIsvariable(false);
					block_num--;
					continue;
				}

				//���� + 0 �̰ų� 0 + 0 �̾ �ƹ��ϵ� �Ͼ�� �ʴ� ���
				else {
					continue;
				}
			}
		}
	}
}

//����� �������� ���϶�
void Game::Move_left() {
	int x, y, i;
	for (y = 0; y < 4; y++) {
		for (i = 3; i >= 0; i--) {
			for (x = 0; x < i; x++) {
				//�̵��Ϸ��� ���⿡ 0�� �ְ� �̵��ϴ� ĭ�� 0�� �ƴ϶� ���ڰ� �״�� �̵��ϴ� ���
				if (board[x][y].GetScore() == 0 && board[x + 1][y].GetScore() != 0) {
					board[x][y] = std::move(board[x + 1][y]);
					continue;
				}

				//�̵��Ϸ��� ���⿡ �ִ� ĭ�� ����ĭ�� ���� ���ڿ��� 2���ϴ� ���
				else if (board[x][y].GetScore() == board[x + 1][y].GetScore()) {
					board[x][y].SetScoreDouble();
					board[x + 1][y].SetScoreZero();
					board[x][y].SetIsvariable(false);
					block_num--;
					continue;
				}

				//���� + 0 �̰ų� 0 + 0 �̾ �ƹ��ϵ� �Ͼ�� �ʴ� ���
				else {
					continue;
				}
			}
		}
	}

}

//����� ���������� ���϶�
void Game::Move_right() {
	int x, y, i;
	for (y = 0; y < 4; y++) {
		for (i = 0; i < 4; i++) {
			for (x = 3; x > i; x--) {
				//�̵��Ϸ��� ���⿡ 0�� �ְ� �̵��ϴ� ĭ�� 0�� �ƴ϶� ���ڰ� �״�� �̵��ϴ� ���
				if (board[x][y].GetScore() == 0 && board[x - 1][y].GetScore() != 0) {
					board[x][y] = std::move(board[x - 1][y]);
					continue;
				}

				//�̵��Ϸ��� ���⿡ �ִ� ĭ�� ����ĭ�� ���� ���ڿ��� 2���ϴ� ���
				else if (board[x][y].GetScore() == board[x - 1][y].GetScore() && i == 0) {
					board[x][y].SetScoreDouble();
					board[x - 1][y].SetScoreZero();
					board[x][y].SetIsvariable(false);
					block_num--;
					continue;
				}

				//���� + 0 �̰ų� 0 + 0 �̾ �ƹ��ϵ� �Ͼ�� �ʴ� ���
				else {
					continue;
				}
			}
		}
	}
}

//������ ����ϴ� �Լ�
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