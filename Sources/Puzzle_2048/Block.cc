#include<iostream>

#include<Puzzle_2048/Block.h>

//score�� Isvariable�� �������ְ� �������� �ʱ�ȭ
Block& Block::operator=(Block&& rhs) {
	score = rhs.GetScore();
	rhs.SetScoreZero();
	is_variable = rhs.GetIsvariable();
	rhs.is_variable = true;
	return *this;
}

//���� score�� ����
int Block::GetScore()const {
	return score;
}

//���� isvariable ����
bool Block::GetIsvariable()const {
	return is_variable;
}

//�Է¹��� ������ score����
void Block::SetScore(int newscore) {
	score = newscore;
}

//������ 0���� ����
void Block::SetScoreZero() {
	score = 0;
}

//score�� 2��� ����
void Block::SetScoreDouble() {
	score *= 2;
}

//isvariable�� ���¸� ����
void Block::SetIsvariable(bool variable) {
	is_variable = variable;
}

//Block�� �ν��Ͻ��� ����
Block Block::MakeBlock() {
	return Block();
}

Block::Block() : score(0), is_variable(true) {};