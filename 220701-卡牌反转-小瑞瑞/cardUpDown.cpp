#include "game.h"
int main() {
	game game;
	game.initGame();
	ExMessage msg;
	BeginBatchDraw();
	while (1) {
		peekmessage(&msg, EM_MOUSE);
		game.showGame();
		game.mouseEvent(msg);
		FlushBatchDraw();
	}
	return 0;
}