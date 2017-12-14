#pragma once
#include "stdafx.h"
#include "cLine.h"


cLine::cLine(void)
{
}


cLine::~cLine(void)
{
}

void cLine::Draw(HDC hdc, int x1, int y1, int x2, int y2){
	SetROP2(hdc, R2_NOP);
	if(isShiftOn==true)
		y2=y1;
	MoveToEx(hdc, x1, y1,0);
	LineTo(hdc,x2,y2);
	StartX=x1;
	StartY=y1;
	EndX=x2;
	EndY=y2;
}
void cLine::PreDraw(HDC hdc, int x1,int y1,int &x2, int &y2, LPARAM lParam, bool is_ShiftOn){
	Lines::PreDraw(hdc,x1,y1,x2,y2,lParam,is_ShiftOn);
}

char* cLine::GetName(){
	return "Line";
}

void cLine::Save(fstream &fout){
	fout.write((char*)this,sizeof(cLine));
}
void cLine::Open(fstream &fin, HDC hdc){
	fin.read((char*)this,sizeof(cLine));
	this->Draw(hdc, this->StartX,this->StartY,this->EndX,this->EndY);
}