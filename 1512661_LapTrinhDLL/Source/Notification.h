#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;
#pragma once

#ifndef _NOTIDLL_EXPORT_
#define NOTI_API _declspec(dllexport)
#else
#define NOTI_API _declspec(dllimport)
#endif

extern "C" NOTI_API	void GoodBye();
