// Win32Project1.cpp : Defines the entry point for the application.
//
#pragma once
#include "stdafx.h"
#include "Win32Project1.h"
#include "HinhTron.h"
#include "cCircle.h"
#include "cRectangle.h"
#include "cLine.h"
#include <algorithm>
#pragma comment( lib, "comctl32.lib" )



#define MAX_LOADSTRING 100
#define input "input.bin"
#define output "output.bin"
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND hwndToolBar;
vector<cHinh*> myHinh;
vector<cRectangle*> myRec;
vector<cCircle*> myCir;
vector<cLine*> myLine;
TBBUTTON tbButtons[11];
fstream fin;
fstream fout;

HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
HPEN hGreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
HPEN hBluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
HPEN hBlackPen= CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

HBRUSH hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
HBRUSH hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
HBRUSH hBlackBrush= CreateSolidBrush(RGB(0, 0, 0));
HBRUSH hWhiteBrush= CreateSolidBrush(RGB(255,255,255));

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
HWND CreateStandardToolbar(HWND hParent, HINSTANCE hInst);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= 0;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	int k;
	PAINTSTRUCT ps;
	HDC hdc;
	HDC hdcTemp;
	HBITMAP hOld;
	HBITMAP hbitmapTemp;
	static bool isGet=0;
	static int StartX,StartY;
	static int EndX,EndY;
	static bool IsDrawing=false;
	static bool cShift=false;
	static int checkColor=0;
	static bool checkSolid=0;
	static cHinh *cMyHinh= new cRectangle;
	cHinh* cTemp=new cRectangle;
	static RECT rectCur;
	cRectangle myH;
	
	switch (message)
	{
	case WM_CREATE:
		hdc=GetWindowDC(hWnd);
		hwndToolBar=CreateStandardToolbar(hWnd, hInst);
		fin.open(output,ios_base::in|ios_base::binary);
		if(fin.is_open()==false){
			MessageBox(hWnd,L"Error 404!",L"File not found", MB_OK);
		}
		else{
			/*while(fin.eof()==false){
				
			}*/
		}
		fin.close();
		ReleaseDC(hWnd,hdc);
		break;
	case WM_SIZE:
		GetWindowRect(hWnd, &rectCur);
		SendMessage(hwndToolBar, WM_SIZE, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		StartX = LOWORD(lParam);
		StartY = HIWORD(lParam);
	
		EndX = LOWORD(lParam);
		EndY = HIWORD(lParam);

		IsDrawing = TRUE;
		ReleaseDC(hWnd, hdc);

		break;

	case WM_MOUSEMOVE:

		hdc = GetDC(hWnd);
		switch(checkColor){
		case 1:
			SelectObject(hdc,hRedPen);
			if(checkSolid==true)
				SelectObject(hdc,hRedBrush);
			break;
		case 2:
			SelectObject(hdc,hGreenPen);
			if(checkSolid==true)
				SelectObject(hdc,hGreenBrush);
			break;
		case 3:
			SelectObject(hdc,hBluePen);
			if(checkSolid==true)
				SelectObject(hdc,hBlueBrush);
			break;
		case 4:
			SelectObject(hdc,hBlackPen);
			if(checkSolid==true)
				SelectObject(hdc,hBlackBrush);
			break;
		default:
			if(checkSolid==true)
				SelectObject(hdc,hWhiteBrush);
			break;
		}


		if( IsDrawing == TRUE )
		{
			cMyHinh->PreDraw(hdc,StartX,StartY,EndX,EndY,lParam,cShift);
		}
		ReleaseDC(hWnd, hdc);
		break;

	case WM_LBUTTONUP:
		EndX = LOWORD(lParam);
		EndY = HIWORD(lParam);
		IsDrawing = FALSE;
		myHinh.push_back(cMyHinh);
		break;
	case WM_KEYDOWN:
		switch(wParam){
		case VK_SHIFT:
			if(IsDrawing==false)
				cShift=true;
			break;
		}
		break;
	case WM_KEYUP:
		switch(wParam){
		case VK_SHIFT:
			cShift=false;
			break;
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_LINE:
			cMyHinh= new cLine();
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_ELLIPSE, TBSTATE_ENABLED);
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_RECTANGLE, TBSTATE_ENABLED);
			break;
		case IDM_ELLIPSE:
			cMyHinh=new cCircle();
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_RECTANGLE, TBSTATE_ENABLED);
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_LINE, TBSTATE_ENABLED);
			break;
		case IDM_RECTANGLE:
			cMyHinh=new cRectangle();
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_ELLIPSE, TBSTATE_ENABLED);
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_LINE, TBSTATE_ENABLED);
			break;
		case IDM_RED:
			checkColor=1;
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_GREEN, TBSTATE_ENABLED);
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_BLUE, TBSTATE_ENABLED);
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_BLACK, TBSTATE_ENABLED);
			break;
		case IDM_BLUE:
			checkColor=2;
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_RED, TBSTATE_ENABLED);
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_GREEN, TBSTATE_ENABLED);
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_BLACK, TBSTATE_ENABLED);
			break;
		case IDM_GREEN:
			checkColor=3;
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_RED, TBSTATE_ENABLED);
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_BLUE, TBSTATE_ENABLED);
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_BLACK, TBSTATE_ENABLED);
			break;
		case IDM_BLACK:
			checkColor=4;
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_RED, TBSTATE_ENABLED);
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_BLUE, TBSTATE_ENABLED);
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_GREEN, TBSTATE_ENABLED);
		case IDM_SOLID:
			checkSolid=true;
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_UNSOLID, TBSTATE_ENABLED);
			break;
		case IDM_UNSOLID:
			checkSolid=false;
			SendMessage(hwndToolBar, TB_SETSTATE, IDM_SOLID, TBSTATE_ENABLED);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		/*fin.open("output.bin",ios_base::in|ios_base::binary);
		if(!fin.is_open())
			MessageBox(hWnd,L"Error 404",L"File not found!",0);
		while(fin){
			fin.read((char *)&myH,sizeof(cRectangle));
			myH.Draw(hdc,myH.StartX,myH.StartY,myH.EndX,myH.EndY,0);
		}
		fin.close();*/
		GetClientRect(hWnd,&rectCur);
		hdcTemp=CreateCompatibleDC(NULL);
		hbitmapTemp=CreateCompatibleBitmap(hdc, rectCur.right,rectCur.bottom);
		hOld = (HBITMAP)SelectObject(hdcTemp,hbitmapTemp);

		FillRect(hdcTemp,&rectCur,HBRUSH (GetBkColor(hdcTemp)));
		SelectObject(hdcTemp,GetStockBrush(NULL_BRUSH));

		cMyHinh->isShiftOn=cShift;
		
		cMyHinh->Draw(hdcTemp,StartX, StartY, EndX, EndY);		

		BitBlt(hdc,0,0,rectCur.right,rectCur.bottom,hdcTemp,0,0,SRCCOPY);
		
		SelectObject(hdcTemp,hOld);
		DeleteObject(hbitmapTemp);
		DeleteDC(hdcTemp);
		
		EndPaint(hWnd, &ps);
		break;
	case WM_ERASEBKGND:
		break;
	case WM_DESTROY:
		fout.open("output.bin",ios_base::out|ios_base::binary);
		for(int i=0;i<myHinh.size();i++){
			myHinh[i]->Save(fout);
		}
		/*for(int i=0;i<myHinh.size();i++){
			delete myHinh[i];
		}*/
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

HWND CreateStandardToolbar(HWND hWndParent, HINSTANCE hInst)
{
    // Declare and initialize local constants.
    const int ImageListID    = 0;
    const int numButtons     = 11;
    const int bitmapSize     = 16;
    
    const DWORD buttonStyles = BTNS_AUTOSIZE;
	InitCommonControls();


    // Create the toolbar.
    HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, 
                                      WS_CHILD | TBSTYLE_WRAPABLE | WS_BORDER , 0, 0, 0, 0, 
                                      hWndParent, NULL, hInst, NULL);
        
    if (hWndToolbar == NULL)
        return NULL;

    // Create the image list.
	SendMessage(hWndToolbar,TB_SETBITMAPSIZE,0,MAKELONG(900, 16));
    HIMAGELIST g_hImageList = ImageList_Create(16,
									16,   // Dimensions of individual bitmaps.
                                    ILC_COLOR32 | ILC_MASK,   // Ensures transparent background.
                                    numButtons, 0);
	HBITMAP hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_STANDARD));
	ImageList_AddMasked(g_hImageList, hBmp, RGB(0,0,0));
	ImageList_SetBkColor(g_hImageList, CLR_NONE);
    // Set the image list.
    SendMessage(hWndToolbar, TB_SETIMAGELIST, 
                0, 
                (LPARAM)g_hImageList);

    // Load the button images.
	/*SendMessage(hWndToolbar, TB_LOADIMAGES, 
		(WPARAM)IDB_STANDARD, 
                (LPARAM)HINST_COMMCTRL);*/

    // Initialize button info.
    // IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.
 
 
    // Initialize button info.
    // IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.
    //TBBUTTON tbButtons[numButtons] = 
  //  {
		//{ 0, IDM_RECTANGLE,  TBSTATE_ENABLED, BTNS_CHECK, {0}, 0, (INT_PTR)L"", },
		//{ 1, IDM_ELLIPSE, TBSTATE_ENABLED, BTNS_CHECK, {0}, 0, (INT_PTR)L""},
		///*{ 0, 0, TBSTATE_ENABLED, BTNS_SEP, {0}, 0, -1},
		//{ 2, 0, TBSTATE_ENABLED, BTNS_BUTTON, {0}, 0, 0}*/
  //  };
	

	tbButtons[0].iBitmap=0;
	tbButtons[0].fsStyle=BTNS_CHECK;
	tbButtons[0].fsState=TBSTATE_ENABLED;
	tbButtons[0].idCommand=IDM_RECTANGLE;

	tbButtons[1].iBitmap=1;
	tbButtons[1].fsStyle=BTNS_CHECK;
	tbButtons[1].fsState=TBSTATE_ENABLED;
	tbButtons[1].idCommand=IDM_ELLIPSE;

	tbButtons[2].iBitmap=2;
	tbButtons[2].fsStyle=BTNS_CHECK;
	tbButtons[2].fsState=TBSTATE_ENABLED;
	tbButtons[2].idCommand=IDM_LINE;

	tbButtons[3].iBitmap=0;
	tbButtons[3].fsStyle=BTNS_SEP;
	tbButtons[3].fsState=TBSTATE_CHECKED;
	tbButtons[3].idCommand=0;

	tbButtons[4].iBitmap=3;
	tbButtons[4].fsStyle=BTNS_CHECK;
	tbButtons[4].fsState=TBSTATE_ENABLED;
	tbButtons[4].idCommand=IDM_RED;

	tbButtons[5].iBitmap=4;
	tbButtons[5].fsStyle=BTNS_CHECK;
	tbButtons[5].fsState=TBSTATE_ENABLED;
	tbButtons[5].idCommand=IDM_GREEN;
			  
	tbButtons[6].iBitmap=5;
	tbButtons[6].fsStyle=BTNS_CHECK;
	tbButtons[6].fsState=TBSTATE_ENABLED;
	tbButtons[6].idCommand=IDM_BLUE;

	tbButtons[7].iBitmap=6;
	tbButtons[7].fsStyle=BTNS_CHECK;
	tbButtons[7].fsState=TBSTATE_ENABLED;
	tbButtons[7].idCommand=IDM_BLACK;

	tbButtons[8].iBitmap=0;
	tbButtons[8].fsStyle=BTNS_SEP;
	tbButtons[8].fsState=TBSTATE_CHECKED;
	tbButtons[8].idCommand=0;

	tbButtons[9].iBitmap=7;
	tbButtons[9].fsStyle=BTNS_CHECK;
	tbButtons[9].fsState=TBSTATE_ENABLED;
	tbButtons[9].idCommand=IDM_SOLID;
	tbButtons[9].iString=(INT_PTR)L"Fill";

	tbButtons[10].iBitmap=8;
	tbButtons[10].fsStyle=BTNS_CHECK;
	tbButtons[10].fsState=TBSTATE_ENABLED;
	tbButtons[10].idCommand=IDM_UNSOLID;
	tbButtons[10].iString=(INT_PTR)L"Not Fill";

    // Add buttons.
    SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
    SendMessage(hWndToolbar, TB_ADDBUTTONS,       (WPARAM)numButtons,       (LPARAM)&tbButtons);


    // Resize the toolbar, and then show it.
    SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0); 
    ShowWindow(hWndToolbar,  TRUE);
    
    return hWndToolbar;
}
