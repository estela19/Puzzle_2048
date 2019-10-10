#include<iostream>

#include<Puzzle_2048/Block.h>


Block& Block::operator=(Block&& rhs) {
	score = rhs.GetScore();
	rhs.SetScoreZero();
	rhs.is_variable = true;
	is_variable = false;
	return *this;
}

int Block::GetScore()const {
	return score;
}

bool Block::GetIsvariable()const {
	return is_variable;
}

void Block::SetScore(Block& target) {
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

Block Block::MakeBlock() {
	return Block();
}

Block::Block() : score(0), is_variable(true) {};