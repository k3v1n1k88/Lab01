#include "stdafx.h"
#include "cSPLASH.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cSPLASH::cSPLASH()
{

}

cSPLASH::~cSPLASH()
{
 DestroyWindow(hSplashWnd);
}

void cSPLASH::Init(HWND hWnd,HINSTANCE hInst,int resid)
{
 hParentWindow=hWnd;
 hSplashWnd=CreateWindowEx(WS_EX_LAYOUTRTL,
							L"STATIC",L"",
							WS_POPUP|SS_BITMAP,
							CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
							hWnd,
							NULL,
							hInst,
							NULL);
 SendMessage(hSplashWnd,
			STM_SETIMAGE,IMAGE_BITMAP,
			(LPARAM)LoadBitmap(hInst,MAKEINTRESOURCE(resid)));
 this->SHOWING = FALSE;
}

void cSPLASH::Show()
{
  //get size of hSplashWnd (width and height)
  int x,y;
  int pwidth,pheight;
  int tx,ty;
  HDWP windefer;
  RECT rect,prect;
  GetClientRect(hSplashWnd,&rect);
  x=rect.right;y=rect.bottom;
  //get parent screen coordinates
  HWND hdDesktop=GetDesktopWindow();
  GetWindowRect(hdDesktop,&prect);
  //center splash window on parent window
  pwidth=prect.right-prect.left;
  pheight=prect.bottom - prect.top;



  tx=(pwidth/2) - (x/2);
  ty=(pheight/2) - (y/2);

  tx+=prect.left;
  ty+=prect.top;


  windefer=BeginDeferWindowPos(1);
  DeferWindowPos(windefer,
				hSplashWnd,
				HWND_NOTOPMOST,
				tx,ty,50,50,
				SWP_NOSIZE|SWP_SHOWWINDOW|SWP_NOZORDER);

  EndDeferWindowPos(windefer);

  ShowWindow(hSplashWnd,SW_SHOWNORMAL);
  UpdateWindow(hSplashWnd);
  this->SHOWING = TRUE;
}

void cSPLASH::Hide()
{
  ShowWindow(hSplashWnd,SW_HIDE);
  this->SHOWING = FALSE;
}