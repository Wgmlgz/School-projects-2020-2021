#pragma once
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>
#include <string>
#include <atlstr.h>
#include <iostream>
#include "Backend.h"
#include "Frontend.h"

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("da");
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hWnd0;
HWND hWnd1;

HWND text1;
HWND text3;
HWND text2;
HWND text4;

int nCmd;
int now_func;
std::string now_name;
std::string text = "dadadadad\nadadaadadada";

WStrings w;

HDC hdc;

struct Vec2 {
  int x, y;
};
void Start();
std::string GetVal(HWND);
int GetInt(HWND, int);
void AddButton(std::string, HWND, int, Vec2, Vec2 = {150, 30});
HWND AddInputText(std::string, HWND, int, Vec2, Vec2);
void RedrawWindow();
void RedrawWindow1();
void SetText(std::string);
void PopUpWindow(int);
void EndInput(int);