#pragma once
#include<array>

#include<Puzzle_2048/Block.h>

enum class Direction {
	Invalid,
	Left,
	Right,
	Up,
	Down
};



class Game {
private:
	using board_array = std::array<std::array<Block, 4>, 4>;
	board_array board;
	Direction direction;
	int block_num;

public:
	Game();
	Direction GetDirection()const;
	void SetDirection(Direction dir);
	void ResetIsvariable();
	void MakeRandomBlock();
	void MoveDecision();
	void Move_up();
	void Move_down();
	void Move_left();
	void Move_right();
	void Print()const;
	void Randomtest();
};