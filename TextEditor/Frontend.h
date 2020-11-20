#pragma once
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <windows.h>
#include <string>
#include <atlstr.h>
#include <iostream>
#include "Backend.h"

struct Vec2 {int x, y;};

// ui elements
HWND hWnd0;
HWND hWnd1;
HWND text1;
HWND text3;
HWND text2;
HWND text4;

static std::string now_name;                          // popup window name
static std::string text = "dadadadad\nadadaadadada";  // main text

// backend class
static WgzStrings w;

static int nCmd;
static HDC hdc;
static HINSTANCE hInst;

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("da");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void AddButton(std::string, HWND, int, Vec2, Vec2 = {150, 30});
HWND AddInputText(std::string, HWND, int, Vec2, Vec2);
void RedrawWindow(HWND hWnd);
std::string GetVal(HWND);
int GetInt(HWND, int = 0);
void Start();
void SetText(std::string);
void PopUpWindow(int);
void EndInput(int);
// 
int CALLBACK WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawMain();
void DrawPopup();
void OnButtonClick(int id);