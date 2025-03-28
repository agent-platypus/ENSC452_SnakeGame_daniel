#include "graphics_driver.h"
#include <unistd.h>
#include <cstring>
#include <time.h>

int black_screen[1280*1024];
int* image_buffer_pointer = (int *)0x00900000;
//int* buffer2_pointer = (int *)0x018D2008;
int NUM_BYTES_BUFFER = 5242880;
extern int currentcolor;
extern int* colors;
void MatrixRotate() {
	// transpose matrix then reverse order of columns to rotate 90 degrees clockwise
	// to implement the snake head direction

}
void DrawFruit(int x_coord, int y_coord) {
	for(int y = y_coord; y<y_coord+20; y++) {
		for(int x = x_coord; x<x_coord+20; x++) {
			if(y == y_coord || y == y_coord + 19) // drawing an outline on each block
				image_buffer_pointer[y*1280+x] = 0x000000;
			else if(x == x_coord || x == x_coord + 19)
				image_buffer_pointer[y*1280+x] = 0x000000;
			else
				image_buffer_pointer[y*1280+x] = 0x0000FF;
		}
	}
}

void DrawBlock(int x_coord, int y_coord, bool remove, int color) {
	// I want to make DrawBlock not have buffer_pointer as a parameter
	// TODO: reorganize code
	// x = which column
	// y = which row
	// each block is 20 by 20 pixels
	for(int y = y_coord; y<y_coord+20; y++) {
		for(int x = x_coord; x<x_coord+20; x++) {
			if(!remove){
				if(y == y_coord || y == y_coord + 19) // drawing an outline on each block
					image_buffer_pointer[y*1280+x] = 0x000000;
				else if(x == x_coord || x == x_coord + 19)
					image_buffer_pointer[y*1280+x] = 0x000000;
				else
					image_buffer_pointer[y*1280+x] = color;
			}
			else
				image_buffer_pointer[y*1280+x] = 0xFF00FF;
		}
	}
}

void DrawSnake(int size, int x, int y) {
	for(int i = 0; i < size; i++) { //size = length of snake
		DrawBlock(x+i*20, y, false, colors[currentcolor]);
		//usleep(50000);
	}
}

void Init_Map() {
	for(int y = 0; y<1024; y++) {
			for(int x = 0; x<1280; x++) {
				black_screen[y*1280 + x] = 0xFF00FF;
			}
		}

		// Drawing horizontal lines
		for(int y = 112; y<115; y++) {
				for(int x = 87; x < 1194; x++) {
					black_screen[y*1280 + x] = 0x000000;
				}
			}

		for(int y = 127; y<130; y++) {
			for(int x = 87; x < 1194; x++) {
				black_screen[y*1280 + x] = 0x000000;
			}
		}

		for(int y = 931; y<934; y++) {
			for(int x = 87; x < 1194; x++) {
				black_screen[y*1280 + x] = 0x000000;
			}
		}

		// Drawing vertical lines
		for(int y = 127; y<934; y++){
			for(int x = 87; x<90; x++){
				black_screen[y*1280 + x] = 0x000000;
			}
		}
		for(int y = 127; y<934; y++){
			for(int x = 1191; x< 1194; x++){
				black_screen[y*1280 + x] = 0x000000;
			}
		}
}

void Draw_Map() {
	memcpy(image_buffer_pointer, black_screen, NUM_BYTES_BUFFER);
}
