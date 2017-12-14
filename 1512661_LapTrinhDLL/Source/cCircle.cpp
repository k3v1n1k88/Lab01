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
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	Graphics* graphics=new Graphics(hdc);
	int lineWidth=3;
	Pen* pen= new Pen(Color(255,0,0,0),lineWidth);
			
	if(isShiftOn==true)
		y2=x2;
	SetROP2(hdc,R2_NOP);
	graphics->DrawEllipse(pen, x1,y1,x2,y2);
	StartX=x1;
	StartY=y1;
	EndX=x2;
	EndY=y2;
	
	delete pen;
	delete graphics;
	GdiplusShutdown(gdiplusToken);
}
void cCircle::PreDraw(HDC hdc, int x1,int y1, int &x2, int &y2, LPARAM lParam,bool is_ShiftOn){
	Drawing::Ellipses::PreDraw(hdc,x1,y1,x2,y2,lParam,is_ShiftOn);
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