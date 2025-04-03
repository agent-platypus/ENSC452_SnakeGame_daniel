#include "graphics_driver.h"
#include <unistd.h>
#include <cstring>
#include <time.h>

int black_screen[1280*1024];
int* image_buffer_pointer = (int *)0x00900000;
int NUM_BYTES_BUFFER = 5242880;
extern int currentcolor;
extern int* colors;

int SnakeFaceTemp[20][20];
int SnakeAliveFace[20][20] = {

		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1},
		{1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1},
		{1,0,0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,2,2,2,2,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int SnakeDeadFace[20][20] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
		{1,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
		{1,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1},
		{1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void DrawSnakeHead(int x_coord, int y_coord, bool remove, int color, bool alive) {
	int SnakeFaceSelect;
	for(int y = 0; y<20; y++) {
		for(int x = 0; x<20; x++) {
			int pixel_color;
			if(!remove){
				if(alive){
					SnakeFaceSelect = SnakeAliveFace[y][x];
				}
				else {
					SnakeFaceSelect = SnakeDeadFace[y][x];
				}
				switch(SnakeFaceSelect){
					case 0:
						pixel_color = color;
						break;
					case 1:
						pixel_color = 0x000000; // black
						break;
					case 2:
						pixel_color = 0x0000FF; // tongue color = red
						break;
					default:
						pixel_color = color;
						break;
					}
				image_buffer_pointer[(y_coord+y)*1280+(x_coord+x)] = pixel_color;
			//		image_buffer_pointer[y*1280+x] = color;
			}
			else
				image_buffer_pointer[(y_coord+y)*1280+(x_coord+x)] = 0xFF00FF;
		}
	}
}
//void Rotate90DegClockWise(int mat[20][20]) {
//	// transpose matrix then reverse order of columns to rotate 90 degrees clockwise
//	// to implement the snake head direction
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//        	SnakeFaceTemp[j][N - i - 1] = mat[i][j];
//        }
//    }
//}
//
//void Rotate90DegCounterClockWise() {
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < N; j++) {
//        	SnakeFaceTemp[N - i - 1][i] = mat[i][j];
//        }
//    }
//}

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
