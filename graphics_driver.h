#ifndef GRAPHICS_DRIVER
#define GRAPHICS_DRIVER

void DrawBlock(int x_coord, int y_coord, bool remove, int color);
void MoveBlock();
void Init_Map();
void Draw_Map();
void DrawFruit(int x_coord, int y_coord);
void DrawSnakeHead(int x_coord, int y, bool remove, int color, bool alive);

#endif
