#pragma once
#include<array>

enum class Direction {
	Invalid,
	Left,
	Right,
	Up,
	Down
};

struct Pos {
	int x, y;
	Pos(int x_, int y_) :x(x_), y(y_) {};
};

class Block {
private:
	Block(int x, int y);
	int score;
	Pos pos;

public:
	Block();
	int GetScore()const;
	Pos GetPos()const;
	void SetScore(Block target);
	void SetScore(int newscore);
	void SetScoreZero();
	void SetScoreDouble();
	Block& operator+(const Block& rhs);
	static Block MakeBlock(int x, int y);
};

class Game {
private:
	using board_array = std::array<std::array<Block, 4>, 4>;
	board_array board;
	Direction direction;

public:
	Game();
	void SetDirection(Direction dir);
	void MakeRandomBlock();
	void MoveDecision();
	void Move_up();
	void Move_down();
	void Move_left();
	void Move_right();
	void Print()const;
	void Randomtest();
};