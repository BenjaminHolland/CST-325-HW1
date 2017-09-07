#include "MainWindow.h"
#include <windowsx.h>
MainWindow::MainWindow(HINSTANCE hInstance)
{
	_running = true;
	_hInstance = hInstance;
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hIcon=LoadIcon(hInstance, NULL);
	wndClass.hIconSm = LoadIcon(hInstance, NULL);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = "MainWindow";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = MainWindow::WndProc;
	ATOM classAtom=RegisterClassEx(&wndClass);
	//exit(GetLastError());
	_hWnd=CreateWindow("MainWindow", "CST325-HW1", WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, NULL, NULL, hInstance, this);
	if (_hWnd == NULL)
		exit(GetLastError());
}
MainWindow::~MainWindow()
{
}
void MainWindow::Run()
{
	ShowWindow(_hWnd, SW_SHOW);
	while (_running) {
		MSG currentMessage;
		while (PeekMessage(&currentMessage, _hWnd, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&currentMessage);
			DispatchMessage(&currentMessage);
		}
	}
}
LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MainWindow* currentWindow;
	if (uMsg == WM_CREATE) {
		currentWindow = static_cast<MainWindow*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetWindowLongPtr(hWnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(currentWindow));
		return TRUE;
	}
	else {
		currentWindow = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWL_USERDATA));
		return currentWindow->OnMessage(hWnd, uMsg, wParam, lParam);
	}
}

LRESULT MainWindow::OnMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		HANDLE_MSG(hWnd, WM_QUIT, OnQuit);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		default: return (DefWindowProc(hWnd, uMsg, wParam, lParam));
	}
}

void MainWindow::OnQuit(HWND hWnd, int exitCode)
{
	_running = false;
}

void MainWindow::OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}

void MainWindow::OnPaint(HWND hWnd)
{
}
