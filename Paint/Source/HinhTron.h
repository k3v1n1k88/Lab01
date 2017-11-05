#pragma once
#include "stdafx.h"

void Draw(HDC hdc, int x1, int y1, int x2, int y2){
	Rectangle(hdc, x1, y1, x2, y2);
}

void PreDraw(HDC hdc,int  x1,int y1, int &x2, int &y2, LPARAM lParam, bool Shift){
	SetROP2(hdc,R2_NOTXORPEN);
	Draw(hdc,x1,y1,x2,y2);
	x2 = LOWORD(lParam);
	y2 = HIWORD(lParam);
	Draw(hdc,x1,y1,x2,y2);
}