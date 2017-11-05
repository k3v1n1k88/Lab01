#pragma once
#include "stdafx.h"
class cHinh
{
public:
	int StartX,StartY,EndX,EndY;
	bool isShiftOn;
	cHinh(void);
	virtual ~cHinh(void);
	virtual char* GetName()=0;
	virtual void Draw(HDC hdc, int x1, int y1, int x2, int y2)=0;
	virtual void PreDraw(HDC hdc, int x1,int y1,int &x2, int &y2, LPARAM lParam, bool is_ShiftOn)=0;
	virtual void Save(fstream &fout)=0;
	virtual void Open(fstream &fin,HDC hdc)=0;
};

