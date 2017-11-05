#pragma once
#include "stdafx.h"
#include "cCircle.h"


cCircle::cCircle(void)
{
}

cCircle::~cCircle(void)
{
}


void cCircle::Draw(HDC hdc, int x1,int y1, int x2, int y2){
	if(isShiftOn==true)
		y2=x2;
	SetROP2(hdc,R2_NOP);
	Ellipse(hdc, x1,y1,x2,y2);
	StartX=x1;
	StartY=y1;
	EndX=x2;
	EndY=y2;
}
void cCircle::PreDraw(HDC hdc, int x1,int y1, int &x2, int &y2, LPARAM lParam,bool is_ShiftOn){
	SetROP2(hdc, R2_NOTXORPEN);
	if(isShiftOn==true)
		y2=x2-x1+y1;
	Ellipse(hdc, x1,y1,x2,y2);
	x2=LOWORD(lParam);
	y2=HIWORD(lParam);
	if(isShiftOn==true)
		y2=x2-x1+y1;
	Ellipse(hdc,x1,y1,x2,y2);
}

char* cCircle::GetName(){
	return "Circle";
}

void cCircle::Save(fstream &fout){
	fout.write((char*)this,sizeof(cCircle));
}
void cCircle::Open(fstream &fin, HDC hdc){
	fin.read((char*)this,sizeof(cCircle));
	this->Draw(hdc, this->StartX,this->StartY,this->EndX,this->EndY);
}