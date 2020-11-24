#pragma once
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>
#include <string>
#include <atlstr.h>
#include <iostream>
#include "Backend.h"

// for positon and size
struct Vec2 {int x, y;};

// ui elements
HWND hWnd0;
HWND hWnd1;
HWND text1;
HWND text3;
HWND text2;
HWND text4;

// strings
static TCHAR szWindowClass[] = _T("DesktopApp"); // i don't know what it is
static TCHAR szTitle[] = _T("da");              // main window title
static std::string now_name;                   // popup window name
static std::string text;                      // main text

// backend class
static WgzStrings w;

// windows.h stuff
static int nCmd;
static HDC hdc;
static HINSTANCE hInst;



// windows liblary methods
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int CALLBACK WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// add ui elements
void AddButton(std::string, HWND, int, Vec2, Vec2 = {150, 30});
HWND AddInputText(std::string, HWND, int, Vec2, Vec2);

// get text box values
std::string GetVal(HWND);
int GetInt(HWND, int = 1);

// uptate ui
void RedrawWindow(HWND hWnd);
void SetText(std::string);
void DrawMain();

// popup window
void PopUpWindow(int);
void EndInput(int);
void DrawPopup();

// events
void Start();
void OnButtonClick(int id);
