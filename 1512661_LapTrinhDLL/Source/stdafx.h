// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include "PaintDLL.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windowsx.h>
#include <windows.h>

// C RunTime Header Files
#include <fstream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <commctrl.h>
#include <time.h>
using namespace std;

#include <ObjIdl.h>
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;


#include "Notification.h"
using namespace Drawing;
#pragma comment(lib,"Notification.lib")
#pragma comment(lib,"PaintDLL.lib")

// TODO: reference additional headers your program requires here
