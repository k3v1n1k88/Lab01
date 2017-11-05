#pragma once
#include "chinh.h"
class cRectangle :
	public cHinh
{
public:
	cRectangle(void);
	~cRectangle(void);
	char* GetName();
	void Draw(HDC hdc, int x1, int y1, int x2, int y2);
	void PreDraw(HDC hdc, int x1,int y1,int &x2, int &y2, LPARAM lParam,bool is_ShiftOn);
	void Save(fstream &fout);
	void Open(fstream &fin, HDC hdc);
};

