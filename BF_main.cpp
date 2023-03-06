#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <conio.h>
#include <cstdlib>

using namespace std;
CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
HWND consoleWin = GetConsoleWindow();
COORD CursorPosition;
COORD newSize;
RECT ConsoleRect;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int options[2];

void setCursor(bool visible, DWORD size);
void bufferWindow();
void resolution(int opt);
void gotoxy(int x, int y);
void drawBorder();
void mainMenu();
void optionsMenu();
void resolutionMenu();
int menuPointer(const int N, int PosX, int* PosY = new int[1]);
void resetOptions();
void loadOptions();

int main() {
	loadOptions();
	//cout << options[0] << options[1];
	//Sleep(1000);
	resolution(options[0]);
	mainMenu();
	return 0;
}

void setCursor(bool visible, DWORD size) {
	if (size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}
void bufferWindow() {
	system("cls");
	// retrieve screen buffer info
	GetConsoleScreenBufferInfo(console, &scrBufferInfo);

	// current window size
	short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
	short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

	// current screen buffer size
	short scrBufferWidth = scrBufferInfo.dwSize.X;
	short scrBufferHeight = scrBufferInfo.dwSize.Y;

	// to remove the scrollbar, make sure the window height matches the screen buffer height
	newSize.X = scrBufferWidth;
	newSize.Y = winHeight;

	// set the new screen buffer dimensions
	SetConsoleScreenBufferSize(console, newSize);

	//hide cursor
	setCursor(0, 0);
}
void resolution(int opt) {
	system("cls");
	int o = opt;
	//screen width(px), screen height(px),
	//screen width(letters), screen height(letters),
	int res[3][4] = {
		473, 424, 54, 23,
		873, 664, 104, 38,
		1153, 1016, 139, 60
	};

	SCREEN_WIDTH = res[o - 1][2];
	SCREEN_HEIGHT = res[o - 1][3];
	SetWindowPos(consoleWin, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	GetWindowRect(consoleWin, &ConsoleRect);
	MoveWindow(consoleWin, ConsoleRect.left, ConsoleRect.top, res[opt - 1][0], res[opt - 1][1], TRUE);

	bufferWindow();
}
void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void drawBorder() {
	system("cls");
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		gotoxy(i, 0);
		cout << (char)177;
		gotoxy(i, SCREEN_HEIGHT);
		cout << (char)177;
	}
	for (int i = 0; i < SCREEN_HEIGHT + 1; i++)
	{
		gotoxy(0, i);
		cout << (char)177;
		gotoxy(SCREEN_WIDTH, i);
		cout << (char)177;
	}
	gotoxy(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}
void mainMenu() {
	system("cls");
	drawBorder();
	const int N = 5;
	int menuPosX = SCREEN_WIDTH / 2 - 8;
	int menuPosY[N];
	gotoxy(SCREEN_WIDTH / 2 - 6, menuPosY[0] = SCREEN_HEIGHT / 2 - 2);
	cout << "New Game";
	gotoxy(SCREEN_WIDTH / 2 - 6, menuPosY[1] = SCREEN_HEIGHT / 2 - 1);
	cout << "Load Game";
	gotoxy(SCREEN_WIDTH / 2 - 6, menuPosY[2] = SCREEN_HEIGHT / 2);
	cout << "Options";
	gotoxy(SCREEN_WIDTH / 2 - 6, menuPosY[3] = SCREEN_HEIGHT / 2 + 1);
	cout << "Credits";
	gotoxy(SCREEN_WIDTH / 2 - 6, menuPosY[4] = SCREEN_HEIGHT / 2 + 2);
	cout << "Exit";
	switch (menuPointer(N, menuPosX, menuPosY))
	{
	case 3:
		optionsMenu();
	case 5:
		system("cls");
		exit(1);
	default:
		break;
	}
}
void optionsMenu() {
	system("cls");
	drawBorder();
	const int N = 4;
	int optionsPosX = SCREEN_WIDTH / 2 - 8;
	int optionsPosY[N];
	gotoxy(SCREEN_WIDTH / 2 - 6, optionsPosY[0] = SCREEN_HEIGHT / 2 - 1);
	cout << "Language";
	gotoxy(SCREEN_WIDTH / 2 - 6, optionsPosY[1] = SCREEN_HEIGHT / 2);
	cout << "Resolution";
	gotoxy(SCREEN_WIDTH / 2 - 6, optionsPosY[2] = SCREEN_HEIGHT / 2 + 1);
	cout << "Reset options";
	gotoxy(SCREEN_WIDTH / 2 - 6, optionsPosY[3] = SCREEN_HEIGHT / 2 + 2);
	cout << "Save and return";
	switch (menuPointer(N, optionsPosX, optionsPosY))
	{
	case 1:
		//languageMenu();
	case 2:
		resolutionMenu();
	case 3:
		resetOptions();
		optionsMenu();
	case 4:
		fstream saveOptions;
		saveOptions.open("options.txt", ios::out);
		for (int i = 0; i < 2; i++)
		{
			saveOptions << options[i] << endl;
		}
		saveOptions.close();
		mainMenu();
		/*default:
			break;*/
	}
}
void resolutionMenu() {
	system("cls");
	drawBorder();
	const int N = 4;
	int resolutionPosX = SCREEN_WIDTH / 2 - 8;
	int resolutionPosY[N];
	gotoxy(SCREEN_WIDTH / 2 - 6, resolutionPosY[0] = SCREEN_HEIGHT / 2 - 1);
	cout << "Small";
	gotoxy(SCREEN_WIDTH / 2 - 6, resolutionPosY[1] = SCREEN_HEIGHT / 2);
	cout << "Medium";
	gotoxy(SCREEN_WIDTH / 2 - 6, resolutionPosY[2] = SCREEN_HEIGHT / 2 + 1);
	cout << "Big";
	gotoxy(SCREEN_WIDTH / 2 - 6, resolutionPosY[3] = SCREEN_HEIGHT / 2 + 2);
	cout << "Return";
	int o = menuPointer(N, resolutionPosX, resolutionPosY);
	if (o != 4)
	{
		options[0] = o;
		resolution(o);
		Sleep(50);
		resolutionMenu();
	}
	else {
		optionsMenu();
	}
}
int menuPointer(const int N, int PosX, int* PosY = int[1]) {
	gotoxy(PosX, PosY[0]);
	cout << (char)175;
	int n = 0;
	int t0 = 0;
	bool pointerVisible = true;
	while (true)
	{
		if (_kbhit())
		{
			char ch = _getch();
			if (ch == 115)
			{
				if (n < N - 1)
				{
					gotoxy(PosX, PosY[n]);
					cout << " ";
					n++;
					gotoxy(PosX, PosY[n]);
					cout << (char)175;
				}
			}
			if (ch == 119)
			{
				if (n > 0)
				{
					gotoxy(PosX, PosY[n]);
					cout << " ";
					n--;
					gotoxy(PosX, PosY[n]);
					cout << (char)175;
				}
			}
			if (ch == 13 || ch == 32)
			{
				return n + 1;
			}
		}
	}
}
void resetOptions() {
	fstream resetOptions;
	resetOptions.open("options.txt", ios::out);
	//resolution
	resetOptions << 2 << endl;
	//language
	resetOptions << 0 << endl;
	resetOptions.close();
	loadOptions();
}
void loadOptions() {
	//load options to table
	fstream loadOptions;
	loadOptions.open("options.txt", ios::in);
	if (loadOptions.good() == false)
	{
		resetOptions();
	}
	for (int i = 0; i < 2; i++)
	{
		loadOptions >> options[i];
	}
	loadOptions.close();

	//apply loaded options
	resolution(options[0]);
}