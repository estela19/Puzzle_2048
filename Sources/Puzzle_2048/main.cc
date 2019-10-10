#include<iostream>
#include<conio.h>

#include<Puzzle_2048/Game.h>
#include<Puzzle_2048/Block.h>

void Input(Game& game, int key);

int main() {
	char key;
	Game game;

	game.MakeRandomBlock();
	while (true) {
		//만약 입력이 유효하다면 새블록 생성, 전체 이동가능성 초기화
		if (game.GetDirection() != Direction::Invalid) {
		game.MakeRandomBlock();
		game.ResetIsvariable();
		}

		game.Print();

		//대소문자 구분없이 모두 소문자로 받음
		key = tolower(_getch());
		Input(game, key);
		game.MoveDecision();
		system("cls");
	}
}

//입력에따라 state 전달
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

	else {
		game.SetDirection(Direction::Invalid);
	}

}
