#pragma once
#include <Windows.h>
class MainWindow {
protected:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	LRESULT CALLBACK OnMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnDestroy(HWND hWnd);
	void OnPaint(HWND hWnd);
	void OnMouseMove(HWND hWnd, int x, int y, UINT keyFlags);
	void OnLeftMouseDown(HWND hWnd, BOOL isDoubleClick, int x, int y, UINT keyFlags);
	void OnLeftMouseUp(HWND hWnd, int x, int y, UINT keyFlags);
	void OnRightMouseDown(HWND hWnd, BOOL isDoubleClick, int x, int y, UINT keyFlags);
	void OnRightMouseUp(HWND hWnd, int x, int y, UINT keyFlags);
	void OnTimer(HWND hWnd, UINT id);
	void ForcePaint();

	int _frameIndex;
	bool _running;
	HINSTANCE _hInstance;
	HWND _hWnd;
	struct {
		int X, Y;
		bool IsRightButtonDown, IsLeftButtonDown;
	} MouseState;

public:
	
	MainWindow(HINSTANCE hInstance);
	~MainWindow();
	void Run();
};