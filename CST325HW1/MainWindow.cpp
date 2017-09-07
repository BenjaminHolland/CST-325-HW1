#include "MainWindow.h"
#include <windowsx.h>
#include <cmath>
#include "renderer.h"
MainWindow::MainWindow(HINSTANCE hInstance)
{
	_running = true;
	_hInstance = hInstance;
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hIcon = LoadIcon(hInstance, NULL);
	wndClass.hIconSm = LoadIcon(hInstance, NULL);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = "MainWindow";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = MainWindow::WndProc;
	ATOM classAtom = RegisterClassEx(&wndClass);
	//exit(GetLastError());
	_hWnd = CreateWindow("MainWindow", "CST325-HW1", WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, NULL, NULL, hInstance, this);
	if (_hWnd == NULL)
		exit(GetLastError());

}

MainWindow::~MainWindow()
{
}

void MainWindow::Run()
{
	SetTimer(_hWnd, 0, 20, NULL);
	ShowWindow(_hWnd, SW_SHOW);
	while (_running) {
		MSG currentMessage;
		while (PeekMessage(&currentMessage, NULL, NULL, NULL, PM_REMOVE)) {
			if (currentMessage.message == WM_QUIT) {
				_running = false;
				break;
			}
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

		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLeftMouseDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLeftMouseUp);
		HANDLE_MSG(hWnd, WM_RBUTTONDOWN, OnRightMouseDown);
		HANDLE_MSG(hWnd, WM_RBUTTONUP, OnRightMouseUp);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);
		HANDLE_MSG(hWnd, WM_TIMER, OnTimer);
	case WM_DESTROY:
		OnDestroy(hWnd);
		break;
	default: return (DefWindowProc(hWnd, uMsg, wParam, lParam));
	}
	return 0;
}



void MainWindow::OnDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}

void MainWindow::OnPaint(HWND hWnd)
{
	RECT clientRect;
	GetClientRect(_hWnd, &clientRect);
	int w = clientRect.right - clientRect.left;
	int h = clientRect.bottom - clientRect.top;
	int cx = w / 2;
	int cy = h / 2;
	int r = 100;

	double x = cx + r*cos((double)_frameIndex*0.01);
	double y = cy + r*sin((double)_frameIndex*0.01);

	Renderer renderer(hWnd);
	renderer.Clear();
	renderer.DrawLine(0, 0, 100, 100);
	renderer.PushPen(RGB(255, 0, 0), 2);
	renderer.DrawLine(MouseState.X,MouseState.Y, 200, 200);
	renderer.PushSolidBrush(RGB(210, 110, 50));
	renderer.DrawRectFill(x, y, 150, 150);
	renderer.PopBrush();
	renderer.DrawRectFrame(x, y, 150, 150);
	_frameIndex++;
}

void MainWindow::OnMouseMove(HWND hWnd, int x, int y, UINT keyFlags)
{
	MouseState.X = x;
	MouseState.Y = y;
	//ForcePaint();
}

void MainWindow::OnLeftMouseDown(HWND hWnd, BOOL isDoubleClick, int x, int y, UINT keyFlags)
{
	MouseState.X = x;
	MouseState.Y = y;
	MouseState.IsLeftButtonDown = true;
}

void MainWindow::OnLeftMouseUp(HWND hWnd, int x, int y, UINT keyFlags)
{
	MouseState.X = x;
	MouseState.Y = y;
	MouseState.IsLeftButtonDown = false;
}

void MainWindow::OnRightMouseDown(HWND hWnd, BOOL isDoubleClick, int x, int y, UINT keyFlags)
{
	MouseState.X = x;
	MouseState.Y = y;
	MouseState.IsRightButtonDown = true;
}

void MainWindow::OnRightMouseUp(HWND hWnd, int x, int y, UINT keyFlags)
{
	MouseState.X = x;
	MouseState.Y = y;
	MouseState.IsRightButtonDown = false;
}

void MainWindow::OnTimer(HWND hWnd, UINT id)
{
	switch (id) {
	case 0:
		ForcePaint();
		break;
	default:
		break;
	}
}

void MainWindow::ForcePaint()
{
	RECT clientRect;
	GetClientRect(_hWnd, &clientRect);
	InvalidateRect(_hWnd, &clientRect, FALSE);
}
