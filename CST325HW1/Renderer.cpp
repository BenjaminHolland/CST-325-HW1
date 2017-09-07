#include "Renderer.h"

Renderer::Renderer(HWND hWnd)
{
	_hWnd = hWnd;
	_immediateContext = BeginPaint(hWnd, &_paintStruct);
	_bufferContext = CreateCompatibleDC(_immediateContext);
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	_backBuffer = CreateCompatibleBitmap(_immediateContext, clientRect.right - clientRect.left, 2000);
	_immediateBuffer = (HBITMAP)SelectObject(_bufferContext, _backBuffer);
	PushSolidBrush(RGB(127, 127, 127));
	PushPen(RGB(0, 0, 0), 1);
}

void Renderer::Clear()
{
	RECT clientRect;
	GetClientRect(_hWnd, &clientRect);
	FillRect(_bufferContext, &clientRect, _brushStack.top());
}

void Renderer::PushSolidBrush(COLORREF color)
{
	HBRUSH newBrush = CreateSolidBrush(color);
	SelectObject(_bufferContext, newBrush);
	_brushStack.push(newBrush);
}

void Renderer::PopBrush()
{
	if (_brushStack.size() > 1) {
		DeleteObject(_brushStack.top());
		_brushStack.pop();
		SelectObject(_bufferContext, _brushStack.top());
	}
}

void Renderer::PushPen(COLORREF color, int width)
{
	HPEN newPen = CreatePen(PS_SOLID, width, color);
	SelectObject(_bufferContext, newPen);
	_penStack.push(newPen);
}

void Renderer::PopPen()
{
	if (_penStack.size() > 1) {
		DeleteObject(_penStack.top());
		_penStack.pop();
		SelectObject(_bufferContext,_penStack.top());
	}
}


void Renderer::DrawLine(int x1, int y1, int x2, int y2)
{
	MoveToEx(_bufferContext, x1, y1, NULL);
	LineTo(_bufferContext, x2, y2);

}

void Renderer::DrawRectFrame(int x1, int y1, int x2, int y2)
{
	DrawLine(x1, y1, x2, y1);
	DrawLine(x1, y1, x1, y2);
	DrawLine(x2, y1, x2, y2);
	DrawLine(x1, y2, x2, y2);
}

void Renderer::DrawRectFill(int x1, int y1, int x2, int y2)
{
	RECT dst;
	dst.left = x1;
	dst.top = y1;
	dst.bottom = y2;
	dst.right = x2;
	FillRect(_bufferContext, &dst, _brushStack.top());
}

Renderer::~Renderer()
{
	while (_brushStack.size() > 0) {
		DeleteObject(_brushStack.top());
		_brushStack.pop();
	}
	while (_penStack.size() > 0) {
		DeleteObject(_penStack.top());
		_penStack.pop();
	}
	RECT clientRect;
	GetClientRect(_hWnd,&clientRect);
	BitBlt(_immediateContext, clientRect.left, clientRect.top, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, _bufferContext, 0, 0, SRCCOPY);
	SelectObject(_bufferContext, _immediateBuffer);
	DeleteObject(_backBuffer);
	DeleteDC(_bufferContext);
	EndPaint(_hWnd,&_paintStruct);
}
