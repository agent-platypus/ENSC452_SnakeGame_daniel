#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

enum StartMenuOption {
	Start = 1,
	Options = 2
};
enum OptionSelection {
	Volume = 0,
	Difficulty = 1,
	Snake_Color = 2
};

enum State {
	StartMenu = 0,
	GameStart = 1,
	GameOptions = 2
};

enum Difficulty {
	Easy = 1,
	Medium = 2
};

void restart_game();
void update_block();
void change_direction(int direction);
void CheckState(int btn_val);

#endif
