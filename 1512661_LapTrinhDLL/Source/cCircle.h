#pragma once
#include "chinh.h"
class cCircle :
	public cHinh
{
public:
	cCircle(void);
	~cCircle(void);
	char* GetName();
	void Draw(HDC hdc, int x1, int y1, int x2, int y2);
	void PreDraw(HDC hdc, int x1,int y1,int &x2, int &y2, LPARAM lParam, bool is_ShiftOn);
	virtual void Save(fstream &fout);
	virtual void Open(fstream &fin, HDC hdc);
};

