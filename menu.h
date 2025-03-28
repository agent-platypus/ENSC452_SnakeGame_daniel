#ifndef MENU
#define MENU

void StartScreen();
void StartScreenStartGame();
void StartScreenOptions();
void StartMenuToggle(int option);
void OptionScreen();
void OutlineOption(int select, bool remove);
void DrawOutline(int x1, int y1, int x2, int y2, bool remove);
void ToggleColor();
void DisplayDifficulty(int difficulty);
void DisplayEasy();
void DisplayMedium();
void ClearDifficulty();
void DisplayGameover();
#endif
