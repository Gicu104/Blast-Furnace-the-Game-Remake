#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <string>

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
const int numOfStrings = 27;
string STRINGS[numOfStrings];

void setCursor(bool visible, DWORD size);
void bufferWindow();
void resolution(int opt);
void gotoxy(int x, int y);
void drawBorder();
void mainMenu();
void optionsMenu();
void resolutionMenu();
void languageMenu();
int menuPointer(const int N, int PosX, int* PosY = new int[1]);
void resetOptions();
void loadOptions();
void loadStrings();
void author();

int main() {
	loadOptions();
	//cout << options[0] << options[1];
	//Sleep(1000);
	//resolution(options[0]);
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
	//STRINGS positions 2-6
	gotoxy(SCREEN_WIDTH / 2 - 6, menuPosY[0] = SCREEN_HEIGHT / 2 - 2);
	cout << STRINGS[2]; //new game
	gotoxy(SCREEN_WIDTH / 2 - 6, menuPosY[1] = SCREEN_HEIGHT / 2 - 1);
	cout << STRINGS[3]; ///load game
	gotoxy(SCREEN_WIDTH / 2 - 6, menuPosY[2] = SCREEN_HEIGHT / 2);
	cout << STRINGS[4]; //options
	gotoxy(SCREEN_WIDTH / 2 - 6, menuPosY[3] = SCREEN_HEIGHT / 2 + 1);
	cout << STRINGS[5]; //credits
	gotoxy(SCREEN_WIDTH / 2 - 6, menuPosY[4] = SCREEN_HEIGHT / 2 + 2);
	cout << STRINGS[6]; //exit
	switch (menuPointer(N, menuPosX, menuPosY))
	{
	case 3:
		optionsMenu();
	case 4:
		authors();
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
	//STRINGS positions 10-13
	gotoxy(SCREEN_WIDTH / 2 - 6, optionsPosY[0] = SCREEN_HEIGHT / 2 - 1);
	cout << STRINGS[10]; //language
	gotoxy(SCREEN_WIDTH / 2 - 6, optionsPosY[1] = SCREEN_HEIGHT / 2);
	cout << STRINGS[11]; //resolution
	gotoxy(SCREEN_WIDTH / 2 - 6, optionsPosY[2] = SCREEN_HEIGHT / 2 + 1);
	cout << STRINGS[12]; //reset
	gotoxy(SCREEN_WIDTH / 2 - 6, optionsPosY[3] = SCREEN_HEIGHT / 2 + 2);
	cout << STRINGS[13]; //return
	switch (menuPointer(N, optionsPosX, optionsPosY))
	{
	case 1:
		languageMenu();
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
	//STRINGS positions 17-20
	gotoxy(SCREEN_WIDTH / 2 - 6, resolutionPosY[0] = SCREEN_HEIGHT / 2 - 1);
	cout << STRINGS[17]; //1
	gotoxy(SCREEN_WIDTH / 2 - 6, resolutionPosY[1] = SCREEN_HEIGHT / 2);
	cout << STRINGS[18]; //2
	gotoxy(SCREEN_WIDTH / 2 - 6, resolutionPosY[2] = SCREEN_HEIGHT / 2 + 1);
	cout << STRINGS[19]; //3
	gotoxy(SCREEN_WIDTH / 2 - 6, resolutionPosY[3] = SCREEN_HEIGHT / 2 + 3);
	cout << STRINGS[20]; //return
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
void languageMenu() {
	system("cls");
	drawBorder();
	const int N = 3;
	int languagePosX = SCREEN_WIDTH / 2 - 8;
	int languagePosY[N];
	//STRINGS positions 24-26
	gotoxy(SCREEN_WIDTH / 2 - 6, languagePosY[0] = SCREEN_HEIGHT / 2 - 1);
	cout << STRINGS[24]; //english
	gotoxy(SCREEN_WIDTH / 2 - 6, languagePosY[1] = SCREEN_HEIGHT / 2);
	cout << STRINGS[25]; //polish
	gotoxy(SCREEN_WIDTH / 2 - 6, languagePosY[2] = SCREEN_HEIGHT / 2 + 2);
	cout << STRINGS[26]; //return
	int o = menuPointer(N, languagePosX, languagePosY);
	if (o != 3)
	{
		options[1] = o;
		loadStrings();
		languageMenu();
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
	//options table structure
	//table pos;	meaning;	values;
	//0; resolution; 1, 2, 3;
	//1; language, 1-english, 2-polish;

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
	loadStrings();
}
void loadStrings() {
	fstream readStrings;
	if (options[1] == 1)
	{
		readStrings.open("language/en_EN.txt", ios::in);
	}
	else
	{
		readStrings.open("language/pl_PL.txt", ios::in);
	}
	for (int i = 1; i <= numOfStrings; i++)
	{
		getline(readStrings, STRINGS[i]);
	}

	readStrings.close();
}
void author() {
}
