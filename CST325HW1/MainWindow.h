#pragma once
#include <Windows.h>
class MainWindow {
private:

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnQuit(HWND hWnd, int exitCode);
	void OnDestroy(HWND hWnd);
	void OnPaint(HWND hWnd);
	
	bool _running;
	HINSTANCE _hInstance;
	HWND _hWnd;
public:
	MainWindow(HINSTANCE hInstance);
	~MainWindow();

	void Run();
};