class Block {
private:
	Block() = default;
	int score;

public:
	static Block MakeBlock();
	int GetScore()const;
	void SetScore(Block target);
	void SetScore(int newscore);
	void SetScoreZero();
	void SetScoreDouble();
	//Block& operator+(const Block& rhs);
};
