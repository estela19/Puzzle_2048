#include<iostream>
#include<conio.h>

#include<Puzzle_2048/Game.h>
#include<Puzzle_2048/Block.h>

void Input(Game& game, int key);

int main() {
	char key;
	Game game;

	while (true) {
		game.MakeRandomBlock();
		game.Print();

		key = tolower(_getch());
		Input(game, key);
		game.MoveDecision();
		system("cls");
	}
}

void Input(Game& game, int key) {
	if (key == 'w') {
		game.SetDirection(Direction::Up);
	}

	else if (key == 'a') {
		game.SetDirection(Direction::Left);
	}

	else if (key == 'd') {
		game.SetDirection(Direction::Right);
	}

	else if (key == 's') {
		game.SetDirection(Direction::Down);
	}
}