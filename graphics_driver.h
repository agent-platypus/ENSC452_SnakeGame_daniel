#ifndef GRAPHICS_DRIVER
#define GRAPHICS_DRIVER

void DrawBlock(int x_coord, int y_coord, bool remove, int color);
void DrawSnake(int size, int x_coord, int y_coord);
void MoveBlock();
void Init_Map();
void Draw_Map();
void DrawFruit(int x_coord, int y_coord);
#endif
