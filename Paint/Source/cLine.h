#pragma once
#include "cHinh.h"
class cLine :
	public cHinh
{
public:
	cLine(void);
	~cLine(void);
	char* GetName();
	void Draw(HDC hdc, int x1, int y1, int x2, int y2);
	void PreDraw(HDC hdc, int x1,int y1,int &x2, int &y2, LPARAM lParam, bool is_ShiftOn);
	virtual void Save(fstream &fout);
	virtual void Open(fstream &fin, HDC hdc);
};

