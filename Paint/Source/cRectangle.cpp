#include "stdafx.h"
#include "cRectangle.h"


cRectangle::cRectangle(void)
{
}


cRectangle::~cRectangle(void)
{
}

void cRectangle::Draw(HDC hdc, int x1,int y1, int x2, int y2){
	SetROP2(hdc, R2_NOP);
	if(isShiftOn==true)
		y2=x2-x1+y1;
	Rectangle(hdc, x1,y1,x2,y2);
	StartX=x1;
	StartY=y1;
	EndX=x2;
	EndY=y2;
}
void cRectangle::PreDraw(HDC hdc, int x1,int y1, int &x2, int &y2, LPARAM lParam,bool is_ShiftOn){
	SetROP2(hdc, R2_NOTXORPEN);
	if(is_ShiftOn==true)
		y2=x2-x1+y1;
	Rectangle(hdc, x1,y1,x2,y2);
	x2=LOWORD(lParam);
	y2=HIWORD(lParam);
	if(is_ShiftOn==true)
		y2=x2-x1+y1;
	Rectangle(hdc,x1,y1,x2,y2);
}

char* cRectangle::GetName(){
	return "cRectangle";
}
void cRectangle::Save(fstream &fout){
	fout.write((char*)this,sizeof(cRectangle));
}
void cRectangle::Open(fstream &fin, HDC hdc){
	fin.read((char*)this,sizeof(cRectangle));
	this->Draw(hdc, this->StartX,this->StartY,this->EndX,this->EndY);
}