#include<iostream>

#include<Puzzle_2048/Block.h>

//score와 Isvariable을 대입해주고 원래것은 초기화
Block& Block::operator=(Block&& rhs) {
	score = rhs.GetScore();
	rhs.SetScoreZero();
	is_variable = rhs.GetIsvariable();
	rhs.is_variable = true;
	return *this;
}

//현재 score를 리턴
int Block::GetScore()const {
	return score;
}

//현재 isvariable 리턴
bool Block::GetIsvariable()const {
	return is_variable;
}

//입력받은 점수로 score설정
void Block::SetScore(int newscore) {
	score = newscore;
}

//점수를 0으로 설정
void Block::SetScoreZero() {
	score = 0;
}

//score를 2배로 설정
void Block::SetScoreDouble() {
	score *= 2;
}

//isvariable의 상태를 변경
void Block::SetIsvariable(bool variable) {
	is_variable = variable;
}

//Block의 인스턴스를 만듬
Block Block::MakeBlock() {
	return Block();
}

Block::Block() : score(0), is_variable(true) {};