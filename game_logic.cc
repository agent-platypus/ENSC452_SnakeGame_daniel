#include "game_logic.h"
#include "graphics_driver.h"
#include "menu.h"
#include "digits.h"
#include "xil_printf.h"
#include "cstdio"

#define STARTING_LENGTH 10

extern int* colors;
extern int colorindex;

//1 = up, 2 = down, 3 = left, 4 = right
enum Direction {
	up = 1,
	down = 2,
	left = 3,
	right = 4
};
int current_direction = 3;
int SNAKE_LENGTH = 10;
int snakeBody_X[200], snakeBody_Y[200];
int x_coord;
int y_coord;
int fruitX= 110;
int fruitY= 230;

bool GameOver = false;
int GameState = 0;
int StartOption = Start;
int OptionSelected = Volume;

int volume = 50;
int difficulty = Easy;
int score = 0;

void restart_game(){
	Draw_Map();
	score = 0;
	draw_score(score);
	x_coord = 410;
	y_coord = 530;
	SNAKE_LENGTH = STARTING_LENGTH;
	fruitX = 110;
	fruitY = 230;
	current_direction = 3;
	DrawFruit(fruitX, fruitY);
	//DrawBlock(x_coord, y_coord, false, colors[colorindex]);
	DrawSnakeHead(x_coord, y_coord, false, colors[colorindex], true);
	for(int i = 0; i<STARTING_LENGTH; i++) {
		DrawBlock(x_coord+i*20, y_coord, false,colors[colorindex]);
		snakeBody_X[i] = x_coord+i*20;
		snakeBody_Y[i] = y_coord;
	}
}

void update_block() {
	// deleting tail block
		DrawBlock(snakeBody_X[SNAKE_LENGTH-1], snakeBody_Y[SNAKE_LENGTH-1], true, colors[colorindex]);
		DrawBlock(x_coord, y_coord, false, colors[colorindex]);
		int prevX = x_coord;
		int prevY = y_coord;
		if(current_direction == 1) { //DOWN
			y_coord+=20;
		}
		else if(current_direction == 2) { //UP
			y_coord-=20;
		}
		else if(current_direction == 3) { //LEFT
			x_coord-=20;
		}
		else if(current_direction == 4) { //RIGHT
			x_coord+=20;
		}
		/*COLLISION DETECTION */
		// body collision: check if the updated coordinate of the head has any intersection
				// with the body blocks

		// checking for fruit collision
		if(y_coord == fruitY && x_coord == fruitX) {

			xil_printf("FRUIT YUMMY IN MY TUMMY\n");
			SNAKE_LENGTH++;
			clear_score(score);
			score++;
			draw_score(score);
			if(score > 10) {
				DisplayVictory();
				GameOver = true;
			}
			fruitX+=60;
			fruitY+=60;
			DrawFruit(fruitX, fruitY);
		}
		bool BodyCollisionDetected = false;
		for(int i = 0; i<SNAKE_LENGTH; i++) {
			if(x_coord == snakeBody_X[i] && y_coord == snakeBody_Y[i]) {
				xil_printf("BODY COLLISION\n");
				DisplayGameover();
				DrawSnakeHead(prevX, prevY, false, colors[colorindex], false);
				GameOver = true;
				BodyCollisionDetected = true;
				}
		}

		// border collision detection
		// keep in mind, each block is 20x20 and blocks are drawn starting from the
		// top left corner which corresponds to the pixel coordinate
		if (y_coord > 929 || y_coord < 130 ||  x_coord > 1189 || x_coord < 90) {
			xil_printf("BORDER COLLISION\n");
			DrawSnakeHead(prevX, prevY, false, colors[colorindex], false);
			DisplayGameover();
			GameOver = true;
		}
		/*COLLISION DETECTION */

		else {
		// drawing the head at the new location

			// with the current implementation, only for body collision cases, the head
			// of the "alive" snake is still drawn although the game is over
			// BodyCollisionDetected ensures only the "dead" face of the snake is drawn
			// at body collision cases
			if(!BodyCollisionDetected) {
				DrawSnakeHead(x_coord, y_coord, false, colors[colorindex], true);
			}
		DrawBlock(snakeBody_X[0], snakeBody_Y[0], false, colors[colorindex]);
		int tempX, tempY;
		// updating each coordinate of the body blocks
		tempX = snakeBody_X[0];
		tempY = snakeBody_Y[0];
		snakeBody_X[0] = prevX;
		snakeBody_Y[0] = prevY;

		for(int i = 1; i<SNAKE_LENGTH; i++) {
			int nextX = snakeBody_X[i];
			int nextY = snakeBody_Y[i];
			snakeBody_X[i] = tempX;
			snakeBody_Y[i] = tempY;
			tempX = nextX;
			tempY = nextY;
			}
		}

}

void change_direction(int direction) {
	// 1 = up, 2 = down, 3 = left, 4 = right
	// default left
	// changing direction is only valid for perpendicular directions
	// i.e. up -> left or up->right   up->down is not valid
	if(direction == left  && (current_direction ==up || current_direction == down) ) {
		current_direction = 3;
		}
	else if(direction==right  && (current_direction ==up || current_direction == down)) {
		current_direction = 4;
		}
	else if(direction==up  && (current_direction ==left || current_direction == right)) {
		current_direction = 1;
		}
	else if(direction==down  && (current_direction ==left || current_direction ==right)) {
		current_direction = 2;
		}
}

void CheckState(int btn_val) {
	switch (btn_val) {
			case 1: // CENTER
				if(GameState == StartMenu) {
						if(StartOption == Start) {
							GameState = GameStart;
							restart_game();
						}
						else if (StartOption == Options) {
							GameState = GameOptions;
							OptionScreen();
							OutlineOption(OptionSelected, false);
							DrawBlock(711, 577, false, colors[colorindex]);
							//draw_score_60x60(1, 634, 429, 0x0000FF);// 627, 429	difficulty
							//draw_score_60x60(100, 609, 309, 0x0000FF);// 617, 309   volume
							DisplayDifficulty(difficulty);
							draw_volume(volume);
						}
				}
				if(GameOver) {
					restart_game();
					GameOver = false;
				}
				break;
		    case 2:
		    	if(GameState == StartMenu) {
		    		StartOption = Options;
		    		StartMenuToggle(StartOption);
		    	}
		    	if(GameState == GameOptions) {
		    		OutlineOption(OptionSelected, true);
		    		OptionSelected++;
		    		OptionSelected = OptionSelected%3;
		    		OutlineOption(OptionSelected, false);
		    		DrawBlock(711, 577, false, colors[colorindex]);
		    	} // DOWN
		        break;
		    case 4:
		    	if(GameState == GameOptions) {
		    		GameState = StartMenu;
		    		StartMenuToggle(StartOption);
		    	} // LEFT
		    	if(GameOver) { // PSEUDO QUIT FUNCTION
		    		GameState = StartMenu;
		    		StartScreenStartGame();
		    		GameOver = false;
		    	}
		        break;
		    case 8:
		    	// RIGHT
		    	if(GameState == GameOptions){
		    		switch(OptionSelected) {
		    		case Volume:
		    			clear_volume(volume);
		    			volume++;
		    			if(volume > 100)
		    				volume = 100;
		    			draw_volume(volume);
		    			break;
		    		case Difficulty:
		    			if(difficulty == Medium) {
		    				difficulty = Easy;
		    			}
		    			else {
		    				difficulty = Medium;
		    			}
		    			DisplayDifficulty(difficulty);
		    			break;
		    		case Snake_Color:
		    			ToggleColor();
		    			DrawBlock(711, 577, false, colors[colorindex]);
		    			break;
		    		default:
		    			break;
		    		}
		    	}
		    	printf("RIGHT CARIMBA\n");
		        break;
		    case 16:
		    	if(GameState == StartMenu) {
		    		StartOption = Start;
		    		StartMenuToggle(StartOption);
		    	}
		    	if(GameState == GameOptions) {
		    		OutlineOption(OptionSelected, true);
		    		OptionSelected--;
		    		OptionSelected = OptionSelected % 3;
		    		 if (OptionSelected < 0) {
		    		      OptionSelected += 3;
		    		 }
		    		OutlineOption(OptionSelected, false);
		    		DrawBlock(711, 577, false, colors[colorindex]);
		    	}
		    	// UP
		    	break;
		    default:
		        printf("Default case is Matched.");
		        break;
		    }
}
