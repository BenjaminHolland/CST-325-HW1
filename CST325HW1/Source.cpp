#include "MainWindow.h"
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) {
	MainWindow window(hInstance);
	window.Run();

}