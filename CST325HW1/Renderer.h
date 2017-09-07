#pragma once
#include <Windows.h>
#include <stack>
class Renderer {
private:
	PAINTSTRUCT _paintStruct;
	HDC _immediateContext,_bufferContext;
	HBITMAP _immediateBuffer,_backBuffer;
	HWND _hWnd;
	std::stack<HPEN> _penStack;
	std::stack<HBRUSH> _brushStack;
public:
	Renderer(HWND hWnd);
	void Clear();
	void PushSolidBrush(COLORREF color);
	void PopBrush();
	void PushPen(COLORREF color, int width);
	void PopPen();
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawRectFrame(int x1, int y1, int x2, int y2);
	void DrawRectFill(int x1, int y1, int x2, int y2);
	~Renderer();
};