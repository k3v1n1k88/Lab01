// MidTerm.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MidTerm.h"
#include <winuser.h>
#include <wchar.h>
#include <vector>
#include <gdiplus.h>
#include <ObjIdl.h>
#include <gdiplus.h>
#include <iostream>
#include <fstream>
#include <codecvt>
#include "cSPLASH.h"
using namespace Gdiplus;

using namespace std;

#pragma comment( lib, "comctl32.lib" )
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "gdiplus.lib")

//------------------------------------------------------------------------------
std::wostream& wendl(std::wostream& out) 
{
    // needed for binary mode files to retain Windows-style newline "\x0D\x0A"
    return out.put(L'\r').put(L'\n').flush();
}//wendl

//------------------------------------------------------------------------------

const std::codecvt_mode le_bom = 
    static_cast<std::codecvt_mode>(std::little_endian | 
                                   std::generate_header | 
                                   std::consume_header);

typedef std::codecvt_utf16<wchar_t, 0x10ffff, le_bom> wcvt_utf16le_bom;

wchar_t buffer[] = L"\u0111\u0107\u010D";

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HWND hwndContentText;
HWND hwndMoneyText;
HWND hwndCombo;
HWND hwndButton;
HWND hwndButton2;
HWND hwndListView;

static float iTotalAnUong		=	0;
static float iTotalDiChuyen		=	0;
static float iTotalNhaCua		=	0;
static float iTotalXeCo			=	0;
static float iTotalNhuYeuPham	=	0;
static float iTotalDichVu		=	0;
static float iTotal				=	1;
static int	iSoluong			=	0;

// Bang mau
static Color color[6]={ Color(	255,	255,	0,		0),		// An uong
						Color(	255,	0,		255,	0),		// Di chuyen
						Color(	255,	0,		0,		255),	// Nha cua
						Color(	255,	255,	255,	0),		// Xe co
						Color(	255,	0,		255,	255),	// Nhu yeu pham
						Color(	255,	255,	0,		255),	// Dich vu
				};



int index=0;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void OnCreate(HWND);
void PaintDiagram(HWND);

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
	LoadString(hInstance, IDC_MIDTERM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MIDTERM));
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	GdiplusShutdown(gdiplusToken);
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MIDTERM));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+0);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MIDTERM);
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,400,20, 500, 660, NULL, NULL, hInstance, NULL);

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
	PAINTSTRUCT ps;
	HDC hdc;
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
	lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
	lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
	lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
	lf.lfPitchAndFamily, lf.lfFaceName);

	// Vung ve do thi
	Rect ellipseRect(230, 430 ,180 , 180); // Create region to draw diagram

	// Cac bien dung de luu tong cua tung loai
	

	switch (message)
	{
	case WM_CREATE:{
		cSPLASH plash;
		plash.Init(hWnd,hInst,IDB_BITMAP1);
		plash.Show();
		OnCreate(hWnd);

		// Read file
		wcvt_utf16le_bom cvt(1);
		wfstream fin;
		locale wloc(fin.getloc(), &cvt);
		fin.imbue(wloc);
		fin.open("output.txt",ios_base::in|ios_base::binary);
		wchar_t item[20],subitem1[20],subitem2[20];
		int i=0;
		if(fin.is_open()){
			while(!fin.eof()){
				fin.getline(item,20,';');
				fin.getline(subitem1,20,';');
				fin.getline(subitem2,20);
				if(fin.eof()==true)
					break;
				fin.clear();

				///Nap vao list view
				// Set cho cot dau tien
				LVITEM lv;
				lv.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
				lv.iItem=i;
				lv.iSubItem=0;
			
				lv.pszText=item;
				lv.cchTextMax=40;

				ListView_InsertItem(hwndListView, &lv);

				//Set cho cot thu 2
				lv.mask = LVIF_TEXT;
				lv.iSubItem=1;
				lv.pszText=subitem1;
				ListView_SetItem(hwndListView,&lv);

				//Set cot thu 3
				lv.iSubItem=2;
				lv.pszText=subitem2;
				ListView_SetItem(hwndListView,&lv);

				//Add vao cac iTotal
				if(wcscmp(item,L"Ăn uống")==0)
					iTotalAnUong+=_wtoi(subitem2);
				if(wcscmp(item,L"Di chuyển")==0)
					iTotalDiChuyen+=_wtoi(subitem2);
				if(wcscmp(item,L"Nhà cửa")==0)
					iTotalNhaCua+=_wtoi(subitem2);
				if(wcscmp(item,L"Xe cộ")==0)
					iTotalXeCo+=_wtoi(subitem2);
				if(wcscmp(item,L"Nhu yếu phẩm")==0)
					iTotalNhuYeuPham+=_wtoi(subitem2);
				if(wcscmp(item,L"Dịch vụ")==0)
					iTotalDichVu+=_wtoi(subitem2);

				i++;
			}
			iTotal = iTotalAnUong + iTotalDiChuyen + iTotalNhaCua + iTotalXeCo + iTotalNhuYeuPham + iTotalDichVu;
			if(iTotal ==0)
				iTotal=1;
			//PaintDiagram(hWnd);
			
		}
		Sleep(4000);
		plash.Hide();
	}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_BUTTON2:
		{
			int selectedIndex = ListView_GetNextItem(hwndListView, -1, LVNI_ALL | LVNI_SELECTED);
			if (selectedIndex != -1){
				
				//ListView_SetItemState(hwndListView,0,LVIS_FOCUSED | LVIS_SELECTED|LVIS_GLOW,0x000F);
				wchar_t item[512], subitem1[512], subitem2[512];

				// Get item chosen deleted

				LVITEM lvi;
				lvi.cchTextMax=512;
				lvi.iSubItem=0;
				lvi.pszText=item;
				SendMessage(hwndListView, LVM_GETITEMTEXT, (WPARAM)selectedIndex, (LPARAM)&lvi);
		
				lvi.iSubItem=1;
				lvi.pszText=subitem1;
				SendMessage(hwndListView, LVM_GETITEMTEXT, (WPARAM)selectedIndex, (LPARAM)&lvi);

				lvi.iSubItem=2;
				lvi.pszText=subitem2;
				SendMessage(hwndListView, LVM_GETITEMTEXT, (WPARAM)selectedIndex, (LPARAM)&lvi);

				// Cap nhat lai cac iTotal
				if(wcscmp(item,L"Ăn uống")==0)
						iTotalAnUong-=_wtoi(subitem2);
				if(wcscmp(item,L"Di chuyển")==0)
					iTotalDiChuyen-=_wtoi(subitem2);
				if(wcscmp(item,L"Nhà cửa")==0)
					iTotalNhaCua-=_wtoi(subitem2);
				if(wcscmp(item,L"Xe cộ")==0)
					iTotalXeCo-=_wtoi(subitem2);
				if(wcscmp(item,L"Nhu yếu phẩm")==0)
					iTotalNhuYeuPham-=_wtoi(subitem2);
				if(wcscmp(item,L"Dịch vụ")==0)
					iTotalDichVu-=_wtoi(subitem2);
				iTotal = iTotalAnUong + iTotalDiChuyen + iTotalNhaCua + iTotalXeCo + iTotalNhuYeuPham + iTotalDichVu;
				if(iTotal ==0)
					iTotal=1;
				//Delete item
				ListView_DeleteItem(hwndListView, selectedIndex);
				InvalidateRect (hWnd, NULL, TRUE);
				UpdateWindow (hWnd);
			}
		}
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDC_BUTTON1:{
			int size1, size2;

			size1 = GetWindowTextLengthW(hwndContentText);
			size2 = GetWindowTextLength(hwndMoneyText);
			
			int index = ComboBox_GetCurSel(hwndCombo);
			char *buffer1, *buffer2;
			buffer1= new char[20];
			buffer2= new char[20];

			if(index==-1){
				MessageBox(hWnd,L"Thông tin loại dịch vụ không thể để trống", L"Error",0);
				return 0;
			}

			if(size1==0){
				MessageBox(hWnd,L"Nội dung không thể để trống", L"Error",0);
				return 0;
			}
			if(size2==0){
				MessageBox(hWnd,L"Số tiền không thể để trống", L"Error",0);
				return 0;
			}

			
			
			ComboBox_GetLBText(hwndCombo,index,buffer1);
			
			
			//PaintDiagram(hWnd);
			hdc=GetWindowDC(hWnd);
			Graphics graphics(hdc);

		   // Create a SolidBrush object.
		   SolidBrush blackBrush(color[0]);

			
			// Set cho cot dau tien
			LVITEM item;
			item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
			item.iItem=iSoluong;
			item.iSubItem=0;

			item.pszText=(LPWSTR)buffer1;
			item.cchTextMax=40;

			ListView_InsertItem(hwndListView, &item);

			//Set cho cot thu 2
			GetWindowTextW(hwndContentText,(LPWSTR)buffer1,20);
			item.mask = LVIF_TEXT;
			item.iSubItem=1;
			item.pszText=(LPWSTR)buffer1;
			ListView_SetItem(hwndListView,&item);

			//Set cot thu 3
			GetWindowText(hwndMoneyText,(LPWSTR)buffer2,20);
			item.iSubItem=2;
			item.pszText=(LPWSTR)buffer2;
			ListView_SetItem(hwndListView,&item);
			
			

			// Fill the pie.
			float angleStart = 0;
			int iMoney = _wtoi((LPCWSTR)buffer2);
			// Add to each total
			switch(index){
			case 0:
				iTotalAnUong+=iMoney;
				break;
			case 1:
				iTotalDiChuyen+=iMoney;
				break;
			case 2:
				iTotalNhaCua+=iMoney;
				break;
			case 3:
				iTotalXeCo+=iMoney;
				break;
			case 4:
				iTotalNhuYeuPham+=iMoney;
				break;
			case 5:
				iTotalDichVu+=iMoney;
				break;
			default:
				break;
			}
			iTotal = iTotalAnUong + iTotalDiChuyen + iTotalNhaCua + iTotalXeCo + iTotalNhuYeuPham + iTotalDichVu;
			if(iTotal ==0)
				iTotal=1;

			int percent;

			//-------------------- An uong ----------------------------
			graphics.FillPie(&blackBrush, ellipseRect, angleStart , iTotalAnUong/iTotal*360);
			
			//Hien thi thong tin ti le
			wchar_t buf[20];

			angleStart+=iTotalAnUong/iTotal*360;			// Tinh goc
			percent = iTotalAnUong/iTotal*100;			// Tinh phan tram

			_itow_s(percent,buf,10);
			wcscat_s(buf,L"%  ");

			SelectObject(hdc,hFont);
			SetBkColor(hdc,RGB(240,240,240));
			TextOut(hdc,150,437,(LPCWSTR)buf,wcslen(buf));

			//-----------------Di chuyen------------------------------
		   blackBrush.SetColor(color[1]);
		   graphics.FillPie(&blackBrush, ellipseRect, angleStart , iTotalDiChuyen/iTotal*360);
		   angleStart+=iTotalDiChuyen/iTotal*360;
		   //Hien thi thong tin ti le
			percent = (int)iTotalDiChuyen/iTotal*100;			// Tinh phan tram
			
			_itow_s(percent,buf,10);
			wcscat_s(buf,L"%  ");
			
			SelectObject(hdc,hFont);
			SetBkColor(hdc,RGB(240,240,240));
			TextOut(hdc,150,467,(LPCWSTR)buf,wcslen(buf));

			//-------------- Nha cua ---------------------------------------------
			blackBrush.SetColor(color[2]);
			graphics.FillPie(&blackBrush, ellipseRect, angleStart , iTotalNhaCua/iTotal*360);
			angleStart+=iTotalNhaCua/iTotal*360;
			//Hien thi thong tin ti le
			percent = (int)iTotalNhaCua/iTotal*100;			// Tinh phan tram
			
			_itow_s(percent,buf,10);
			wcscat_s(buf,L"%  ");
			
			SelectObject(hdc,hFont);
			SetBkColor(hdc,RGB(240,240,240));
			TextOut(hdc,150,497,(LPCWSTR)buf,wcslen(buf));

			//-------------- Xe co ------------------------------------
		   blackBrush.SetColor(color[3]);
		   graphics.FillPie(&blackBrush, ellipseRect, angleStart , iTotalXeCo/iTotal*360);
		   angleStart+=iTotalXeCo/iTotal*360;
		   //Hien thi thong tin ti le
			percent = (int)iTotalXeCo/iTotal*100;			// Tinh phan tram
			
			_itow_s(percent,buf,10);
			wcscat_s(buf,L"%  ");
			
			SelectObject(hdc,hFont);
			SetBkColor(hdc,RGB(240,240,240));
			TextOut(hdc,150,527,(LPCWSTR)buf,wcslen(buf));

		   //--------------Nhu Yeu Pham-----------------------------------
		   blackBrush.SetColor(color[4]);
		   graphics.FillPie(&blackBrush, ellipseRect, angleStart , iTotalNhuYeuPham/iTotal*360);
		   angleStart+=iTotalNhuYeuPham/iTotal*360;

		   //Hien thi thong tin ti le
			percent = (int)iTotalNhuYeuPham/iTotal*100;			// Tinh phan tram
			
			_itow_s(percent,buf,10);
			wcscat_s(buf,L"%  ");
			
			SelectObject(hdc,hFont);
			SetBkColor(hdc,RGB(240,240,240));
			TextOut(hdc,150,557,(LPCWSTR)buf,wcslen(buf));

		   //---------------Dich vu---------------------------------------
		   blackBrush.SetColor(color[5]);
		   graphics.FillPie(&blackBrush, ellipseRect, angleStart , iTotalDichVu/iTotal*360);
		   angleStart+=iTotalDichVu/iTotal*360;

		   //Hien thi thong tin ti le
			percent = (int)iTotalDichVu/iTotal*100;			// Tinh phan tram
			
			_itow_s(percent,buf,10);
			wcscat_s(buf,L"%  ");
			
			SelectObject(hdc,hFont);
			SetBkColor(hdc,RGB(240,240,240));
			TextOut(hdc,150,587,(LPCWSTR)buf,wcslen(buf));
			iSoluong++;
		   ReleaseDC(hWnd,hdc);
		   //delete buffer;
		}
		break;
		
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:{
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here..
		RECT rect={0,20,480,200};
		HFONT font = CreateFont(25, 0, 0, 0, 550, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Times New Roman");
		SelectObject(hdc,font);
		SetTextColor(hdc, 0x00000000);
		SetBkMode(hdc,TRANSPARENT);
		DeleteObject(font);

		
		DrawText(hdc,L"QUẢN LÍ CHI TIÊU", -1, &rect,DT_CENTER);

		// An uong
		SelectObject(hdc,CreatePen(PS_SOLID,1,RGB(255,0,0)));
		SelectObject(hdc,CreateSolidBrush(RGB(255,0,0)));
		Rectangle(hdc,38, 388, 50, 400);
		
		// Di chuyen
		SelectObject(hdc,CreatePen(PS_SOLID,1,RGB(0,255,0)));
		SelectObject(hdc,CreateSolidBrush(RGB(0,255,0)));
		Rectangle(hdc,38, 418, 50, 430);
		//SetROP2(hdc,R2_MASKPEN);
		/*Pie(hdc,200,385,375,560,600,600,500,500);*/
		//Pie(hdc,,

		// Nha
		SelectObject(hdc,CreatePen(PS_SOLID,1,RGB(0,0,255)));
		SelectObject(hdc,CreateSolidBrush(RGB(0,0,255)));
		Rectangle(hdc,38, 448, 50, 460);//
		
		// Xe
		SelectObject(hdc,CreatePen(PS_SOLID,1,RGB(255,255,0)));
		SelectObject(hdc,CreateSolidBrush(RGB(255,255,0)));
		Rectangle(hdc,38, 478, 50, 490);
		
		// Nhu 
		SelectObject(hdc,CreatePen(PS_SOLID,1,RGB(0,255,255)));
		SelectObject(hdc,CreateSolidBrush(RGB(0,255,255)));
		Rectangle(hdc,38, 508, 50, 520);

		// Dich
		SelectObject(hdc,CreatePen(PS_SOLID,1,RGB(255,0,255)));
		SelectObject(hdc,CreateSolidBrush(RGB(255,0,255)));
		Rectangle(hdc,38, 538, 50, 550);
		PaintDiagram(hWnd);
		EndPaint(hWnd, &ps);
		//////////////////////////////
		
		/////////////////////////////
	}
		break;
	case WM_CLOSE:
		{
			const int result=MessageBox(hWnd, L"Bạn có muốn lưu lại hay không?",L"Notify",MB_YESNOCANCEL);
			if(result==IDYES){
				std::wfstream fout;
				wcvt_utf16le_bom cvt(1);

				std::locale wloc(fout.getloc(), &cvt);
				fout.imbue(wloc);
				fout.open("output.txt", std::ios::out | std::ios::binary);

				int count=(int)SendMessage(hwndListView, LVM_GETITEMCOUNT, 0, 0);
				int i;

				wchar_t item[512], subitem1[512], subitem2[512];

				/* Shove all items of listview into item and subitem
				   and print out one by one. */

				LVITEM lvi;
				lvi.cchTextMax=512;

				for(i=0; i<count; i++) {
					lvi.iSubItem=0;
					lvi.pszText=item;
					SendMessage(hwndListView, LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)&lvi);
			
					lvi.iSubItem=1;
					lvi.pszText=subitem1;
					SendMessage(hwndListView, LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)&lvi);

					lvi.iSubItem=2;
					lvi.pszText=subitem2;
					SendMessage(hwndListView, LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)&lvi);

					fout<<item<<";"<<subitem1<<";"<<subitem2<<endl;
				}
				fout.close();
				DestroyWindow(hWnd);
			}
			if(result==IDNO){
				DestroyWindow(hWnd);
			}
			break;
		}
	case WM_DESTROY:
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

void OnCreate(HWND hWnd){
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);
	
	// Lấy font hệ thống
	LOGFONT lf;
	HWND hwnd = NULL;
	//HDC hdc=GetWindowDC(hWnd);
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
	lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
	lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
	lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
	lf.lfPitchAndFamily, lf.lfFaceName);

	//-----------------
	hwnd=CreateWindow(TEXT("STATIC"), L"Loại chi tiêu",
					WS_CHILD | WS_VISIBLE | SS_LEFT,
					40, 70, 100, 15,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont),TRUE);


	//-----------------
	hwnd=CreateWindow(TEXT("static"), L"Nội dung",
					WS_CHILD | WS_VISIBLE | SS_LEFT,
					170, 70, 100, 15,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont),TRUE);
	//-----------------
	hwnd=CreateWindow(TEXT("static"), L"Số tiền",
					WS_CHILD | WS_VISIBLE | SS_LEFT,
					300, 70, 100, 15,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont),TRUE);
	////////////////////////////
	hwndCombo=CreateWindow(L"combobox", L"", 
							CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
							40, 90, 100, 20, 
							hWnd,(HMENU) IDR_MENU1, hInst, NULL);
	TCHAR Planets[6][15] =  
    {
        TEXT("Ăn uống"), TEXT("Di chuyển"), TEXT("Nhà cửa"), TEXT("Xe cộ"), 
        TEXT("Nhu yếu phẩm"), TEXT("Dịch vụ") 
    };
	TCHAR A[16]; 
    int  k = 0; 

    memset(&A,0,sizeof(A));       
    for (k = 0; k <= 5; k += 1)
    {
        wcscpy_s(A, sizeof(A)/sizeof(TCHAR),  (TCHAR*)Planets[k]);

        // Add string to combobox.
        SendMessage(hwndCombo,(UINT) CB_ADDSTRING,(WPARAM) 0,(LPARAM) A); 
    }
      
    // Send the CB_SETCURSEL message to display an initial item 
    //  in the selection field  
	SendMessage(hwndCombo, WM_SETFONT, WPARAM(hFont),TRUE);

	
    // Send the CB_SETCURSEL message to display an initial item 
    //  in the selection field  
    SendMessage(hwnd, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);

	////////////////////////////
	hwndContentText=CreateWindow(TEXT("edit"),L"",
							WS_CHILD|WS_VISIBLE|WS_BORDER,
							170, 90, 100, 20,
							hWnd, 0, hInst, NULL);
	SendMessage(hwndContentText, WM_SETFONT, WPARAM(hFont),TRUE);
	////////////////////////////
	hwndMoneyText=CreateWindowEx(0,TEXT("edit"),L"",
							ES_NUMBER|WS_CHILD|WS_VISIBLE|WS_BORDER,
							300, 90, 100, 20,
							hWnd, 0, hInst, NULL);
	SendMessage(hwndMoneyText, WM_SETFONT, WPARAM(hFont),TRUE);
	///////////////////////////
	hwndButton=CreateWindow(TEXT("button"),L" Thêm ",
							WS_CHILD|WS_VISIBLE,
							320,115,80,25,
							hWnd, (HMENU)IDC_BUTTON1,hInst,NULL);
	SendMessage(hwndButton, WM_SETFONT, WPARAM(hFont),TRUE);
	/////////////////////////////////
	hwnd=CreateWindow(TEXT("button"), L"Danh sách chi tiêu",
					WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
					30, 160, 410, 200,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont),TRUE);

	////////////////////////
	//Begin create listview
	hwndListView=CreateWindowEx(0,WC_LISTVIEWW, L"",
		WS_CHILD | WS_VISIBLE |WS_VSCROLL | LVS_REPORT | WS_BORDER|LVS_SHOWSELALWAYS,
					40, 180, 390, 170,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwndListView, WM_SETFONT, WPARAM(hFont),TRUE);
	ListView_SetExtendedListViewStyle(hwndListView,LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	LVCOLUMN lvCol;
	lvCol.mask= LVCF_FMT|LVCF_TEXT|LVCF_WIDTH;
	lvCol.fmt=LVCFMT_LEFT;

	lvCol.cx= 200;
	lvCol.pszText= L"Số tiền";
	ListView_InsertColumn(hwndListView,0,&lvCol);

	lvCol.cx= 150;
	lvCol.pszText= L"Nội dung";
	ListView_InsertColumn(hwndListView,0,&lvCol);

	lvCol.cx= 120;
	lvCol.pszText= L"Loại";
	ListView_InsertColumn(hwndListView,0,&lvCol);
	//end create list view

	///////////////////////
	hwnd=CreateWindow(TEXT("button"), L"Thống kê",
					WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
					30, 360, 410, 220,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont),TRUE);
	///////////
	hwnd=CreateWindow(TEXT("static"), L"Ăn uống",
					WS_CHILD | WS_VISIBLE | SS_LEFT,
					55, 387, 60, 15,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont),TRUE);
	//////////////
	hwnd=CreateWindow(TEXT("static"), L"Ăn uống",
					WS_CHILD | WS_VISIBLE | SS_LEFT,
					55, 387, 60, 15,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont),TRUE);
	//////////////
	hwnd=CreateWindow(TEXT("static"), L"Di chuyển",
					WS_CHILD | WS_VISIBLE | SS_LEFT,
					55, 417, 60, 15,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont),TRUE);
	///////////////
	hwnd=CreateWindow(TEXT("static"), L"Nhà cửa",
					WS_CHILD | WS_VISIBLE | SS_LEFT,
					55, 447, 60, 15,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont),TRUE);
	///////////////
	hwnd=CreateWindow(TEXT("static"), L"Xe cộ",
					WS_CHILD | WS_VISIBLE | SS_LEFT,
					55, 477, 60, 15,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont),TRUE);
	///////////////
	hwnd=CreateWindow(TEXT("static"), L"Nhu yếu phẩm",
					WS_CHILD | WS_VISIBLE | SS_LEFT,
					55, 507, 80, 15,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont),TRUE);
	///////////////
	hwnd=CreateWindow(TEXT("static"), L"Dịch vụ",
					WS_CHILD | WS_VISIBLE | SS_LEFT,
					55, 537, 60, 15,
					hWnd, (HMENU) 0, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont),TRUE);
	ListView_SetItemText(hwndListView, 0, 1, TEXT("12345"));

	///////////////////////
	hwndButton=CreateWindow(TEXT("button"),L"Xóa ",
							WS_CHILD|WS_VISIBLE,
							443,180,40,20,
							hWnd, (HMENU)IDC_BUTTON2,hInst,NULL);
	SendMessage(hwndButton, WM_SETFONT, WPARAM(hFont),TRUE);
}

void PaintDiagram(HWND hWnd){
	HDC hdc=GetWindowDC(hWnd);
	Graphics graphics(hdc);
	SolidBrush blackBrush(color[0]);
	Rect ellipseRect(230, 430 ,180 , 180);
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
	lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
	lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
	lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
	lf.lfPitchAndFamily, lf.lfFaceName);
	int angleStart=0;
	int percent;

	//-------------------- An uong ----------------------------
	graphics.FillPie(&blackBrush, ellipseRect, angleStart , iTotalAnUong/iTotal*360);
	
	//Hien thi thong tin ti le
	wchar_t buf[20];

	angleStart+=iTotalAnUong/iTotal*360;			// Tinh goc
	percent = (int)iTotalAnUong/iTotal*100;			// Tinh phan tram

	_itow_s(percent,buf,10);
	wcscat_s(buf,L"%     ");

	SelectObject(hdc,hFont);
	SetBkColor(hdc,RGB(240,240,240));
	TextOut(hdc,150,437,(LPCWSTR)buf,wcslen(buf));

	//-----------------Di chuyen------------------------------
	blackBrush.SetColor(color[1]);
	graphics.FillPie(&blackBrush, ellipseRect, angleStart , iTotalDiChuyen/iTotal*360);
	angleStart+=iTotalDiChuyen/iTotal*360;
	//Hien thi thong tin ti le
	percent = (int)iTotalDiChuyen/iTotal*100;			// Tinh phan tram
	
	_itow_s(percent,buf,10);
	wcscat_s(buf,L"%     ");
	
	SelectObject(hdc,hFont);
	SetBkColor(hdc,RGB(240,240,240));
	TextOut(hdc,150,467,(LPCWSTR)buf,wcslen(buf));

	//-------------- Nha cua ---------------------------------------------
	blackBrush.SetColor(color[2]);
	graphics.FillPie(&blackBrush, ellipseRect, angleStart , iTotalNhaCua/iTotal*360);
	angleStart+=iTotalNhaCua/iTotal*360;
	//Hien thi thong tin ti le
	percent = (int)iTotalNhaCua/iTotal*100;			// Tinh phan tram
	
	_itow_s(percent,buf,10);
	wcscat_s(buf,L"%     ");
	
	SelectObject(hdc,hFont);
	SetBkColor(hdc,RGB(240,240,240));
	TextOut(hdc,150,497,(LPCWSTR)buf,wcslen(buf));

	//-------------- Xe co ------------------------------------
	 blackBrush.SetColor(color[3]);
	 graphics.FillPie(&blackBrush, ellipseRect, angleStart , iTotalXeCo/iTotal*360);
	 angleStart+=iTotalXeCo/iTotal*360;
	 //Hien thi thong tin ti le
	percent = (int)iTotalXeCo/iTotal*100;			// Tinh phan tram
	
	_itow_s(percent,buf,10);
	wcscat_s(buf,L"%     ");
	
	SelectObject(hdc,hFont);
	SetBkColor(hdc,RGB(240,240,240));
	TextOut(hdc,150,527,(LPCWSTR)buf,wcslen(buf));

	 //--------------Nhu Yeu Pham-----------------------------------
	 blackBrush.SetColor(color[4]);
	 graphics.FillPie(&blackBrush, ellipseRect, angleStart , iTotalNhuYeuPham/iTotal*360);
	 angleStart+=iTotalNhuYeuPham/iTotal*360;

	 //Hien thi thong tin ti le
	percent = (int)iTotalNhuYeuPham/iTotal*100;			// Tinh phan tram
	
	_itow_s(percent,buf,10);
	wcscat_s(buf,L"%     ");
	
	SelectObject(hdc,hFont);
	SetBkColor(hdc,RGB(240,240,240));
	TextOut(hdc,150,557,(LPCWSTR)buf,wcslen(buf));

	 //---------------Dich vu---------------------------------------
	 blackBrush.SetColor(color[5]);
	 graphics.FillPie(&blackBrush, ellipseRect, angleStart , iTotalDichVu/iTotal*360);
	 angleStart+=iTotalDichVu/iTotal*360;
	 //Hien thi thong tin ti le
	 percent = (int)iTotalDichVu/iTotal*100;			// Tinh phan tram
	 
	 _itow_s(percent,buf,10);
	 wcscat_s(buf,L"%     ");
	 
	 SelectObject(hdc,hFont);
	 SetBkColor(hdc,RGB(240,240,240));
	 TextOut(hdc,150,587,(LPCWSTR)buf,wcslen(buf));

	 ReleaseDC(hWnd,hdc);
}