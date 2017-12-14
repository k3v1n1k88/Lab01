#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;
#pragma once

#ifndef _PAINDLL_EXPORT_
#define PAINTDLL_API _declspec(dllexport)
#else
#define PAINTDLL_API _declspec(dllimport)
#endif

namespace Drawing{
	class Ellipses{
	public:
		// PreDraw Ellipses
        static PAINTDLL_API void PreDraw(HDC hdc, int x1,int y1, int &x2, int &y2, LPARAM lParam,bool is_ShiftOn);
	};
	class Rectangles{
	public:
		// PreDraw Rectangles
		static PAINTDLL_API void PreDraw(HDC hdc, int x1,int y1, int &x2, int &y2, LPARAM lParam,bool is_ShiftOn);
	};
	class Lines{
	public:
		//PreDraw Lines
		static PAINTDLL_API void PreDraw(HDC hdc, int x1,int y1,int &x2, int &y2, LPARAM lParam, bool is_ShiftOn);
	};
}

void PreDrawEllipses(HWND,int,int,int,int,LPARAM,bool);
void PreDrawRectangles(HWND,int,int,int,int,LPARAM,bool);
void PreDrawLines(HWND,int,int,int,int,LPARAM,bool);
