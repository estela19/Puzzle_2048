#pragma once
class Block {
private:
//	Block() = default;
	int score;
	bool is_variable;

public:
	Block();
	Block(const Block&) = default;
	static Block MakeBlock();
	int GetScore()const;
	bool GetIsvariable()const;
	void SetScore(Block& target);
	void SetScore(int newscore);
	void SetScoreZero();
	void SetScoreDouble();
	Block& operator=(Block&& rhs);
};
