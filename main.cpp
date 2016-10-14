#include "ops.h"

void main() {
	ifstream starter;
	starter.open("starter.wld");
	string game;
	getline(starter, game);
	if (game == "started!") {
		startTheGame();
	}
	else {
		initiateGame();
	}
	starter.close();
	system("pause");
}

