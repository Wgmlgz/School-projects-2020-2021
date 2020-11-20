#include "Frontend.h"

// windows liblary methods
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

  if (!RegisterClassEx(&wcex)) {
    MessageBox(NULL, _T("Call to RegisterClassEx failed!"),
               _T("Windows Desktop Guided Tour"), NULL);

    return 1;
  }

  hInst = hInstance;

  hWnd0 =
      CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                   CW_USEDEFAULT, 1200, 720, NULL, NULL, hInstance, NULL);

  Start();

  if (!hWnd0) {
    MessageBox(NULL, _T("Call to CreateWindow failed!"),
               _T("Windows Desktop Guided Tour"), NULL);

    return 1;
  }

  nCmd = nCmdShow;
  ShowWindow(hWnd0, nCmdShow);
  UpdateWindow(hWnd0);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return static_cast<int>(msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  if (message == WM_PAINT) {
    if (hWnd == hWnd0) DrawMain();
    if (hWnd == hWnd1) DrawPopup();
  }
  if (message == WM_DESTROY) {
    if (hWnd == hWnd0)  PostQuitMessage(0);
    else PostMessage(hWnd, WM_CLOSE, 0, 0);
  }
  if (message == WM_COMMAND) {
    if (HIWORD(wParam) == BN_CLICKED) OnButtonClick(wParam);
  }
  else return DefWindowProc(hWnd, message, wParam, lParam);
  return 0;
}

// add ui elements
void AddButton(std::string name, HWND hWnd, int id, Vec2 pos, Vec2 size) {
  HFONT hFont, hTmp;
  hFont =
      CreateFont(20, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 2, 0, L"Product Sans Bold");
  hTmp = (HFONT)SelectObject(hdc, hFont);
  SetBkMode(hdc, TRANSPARENT);

  std::wstring wide_string = std::wstring(name.begin(), name.end());
  const wchar_t* result = wide_string.c_str();
  HWND hwndButton = CreateWindowEx(
      0, L"BUTTON", result, WS_CHILD | WS_VISIBLE, pos.x, pos.y,
      size.x, size.y, hWnd, (HMENU)id, GetModuleHandle(NULL), NULL);

  SendMessage(hwndButton, WM_SETFONT, (WPARAM)hFont,
              (LPARAM)MAKELONG(TRUE, 0));
  // SendMessage((HWND)hwndButton, (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP,
  //(LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1)));
}
HWND AddInputText(std::string name, HWND hWnd, int id, Vec2 pos, Vec2 size) {
  HFONT hFont, hTmp;
  hFont = CreateFont(20, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 2, 0,
                     L"Product Sans");
  hTmp = (HFONT)SelectObject(hdc, hFont);
  SetBkMode(hdc, TRANSPARENT);

  if (name == "") return (HWND)NULL;
  std::wstring wide_string = std::wstring(name.begin(), name.end());
  const wchar_t* result = wide_string.c_str();
  HWND hwndT = CreateWindowEx(0, L"EDIT", result,
      WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL,
                              pos.x, pos.y, size.x, size.y, hWnd, (HMENU)id,
                              GetModuleHandle(NULL), NULL);

  SendMessage(hwndT, WM_SETFONT, (WPARAM)hFont, (LPARAM)MAKELONG(TRUE, 0));
  return hwndT;
}

// get text box values
std::string GetVal(HWND w) {
  char t[100];
  wchar_t wt[100];
  GetWindowText(w, &wt[0], 100);
  std::wstring ws(wt);
  std::string str(ws.begin(), ws.end());
  return str;
}
int GetInt(HWND w, int i) {
  try {
    return std::stoi(GetVal(w));
  } catch (std::invalid_argument) {
    return i;
  }
}

// uptate ui
void RedrawWindow(HWND hWnd) { InvalidateRect(hWnd, NULL, NULL); }
void SetText(std::string s) {
  text = s + "                                                                          ";
  RedrawWindow(hWnd0); 
  //MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Windows Desktop Guided Tour"), NULL);
}

// popup window
void PopUpWindow(int id) {
  std::string func_name;

  std::string s1;
  std::string s2;
  std::string s3;
  std::string s4;

  if (id == 0) func_name = "Insert";
  if (id == 1) func_name = "InsertMultiple";
  if (id == 2) func_name = "Erase";
  if (id == 3) func_name = "InsertSubstring";
  if (id == 4) func_name = "ReplaceSymbol";
  if (id == 5) func_name = "ReplaceSubstring";
  if (id == 6) func_name = "RemoveZeroes";
  if (id == 7) func_name = "RemoveAsterisks";

  if (id == 0) s1 = "String to insert";
  if (id == 1) s1 = "Strings to insert";
  if (id == 2) s1 = "Erase position";
  if (id == 3) s1 = "Substring to insert";
  if (id == 4) s1 = "New symbol";
  if (id == 5) s1 = "Old substring";
  if (id == 6) s1 = "Start index";
  if (id == 7) s1 = "Start index";

  if (id == 0) s2 = "Insert position";
  if (id == 1) s2 = "Insert position";
  if (id == 2) s2 = "";
  if (id == 3) s2 = "Insert string position";
  if (id == 4) s2 = "Replace string position";
  if (id == 5) s2 = "New substring";
  if (id == 6) s2 = "End index";
  if (id == 7) s2 = "End index";

  if (id == 0) s3 = "";
  if (id == 1) s3 = "";
  if (id == 2) s3 = "";
  if (id == 3) s3 = "Insert symbol position";
  if (id == 4) s3 = "Replace symbol position";
  if (id == 5) s3 = "Start index";
  if (id == 6) s3 = "";
  if (id == 7) s3 = "";

  if (id == 0) s4 = "";
  if (id == 1) s4 = "";
  if (id == 2) s4 = "";
  if (id == 3) s4 = "";
  if (id == 4) s4 = "";
  if (id == 5) s4 = "End index";
  if (id == 6) s4 = "";
  if (id == 7) s4 = "";

  now_name = func_name;

  hWnd1 = CreateWindow(szWindowClass, _T("Input arguments"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                   CW_USEDEFAULT, 500, 250, NULL, NULL, hInst, NULL);
  AddButton("da)", hWnd1, id + 100, {170, 170});
  text1 = AddInputText(s1, hWnd1, 2, {20, 25}, {440, id == 1 ? 100 : 30});
  text2 = AddInputText(s2, hWnd1, 3, {20, id == 1 ? 130 : 60}, {440, 30});
  text3 = AddInputText(s3, hWnd1, 3, {20, 95}, {440, 30});
  text4 = AddInputText(s4, hWnd1, 3, {20, 130}, {440, 30});

  ShowWindow(hWnd1, nCmd);
  UpdateWindow(hWnd1);
}
void EndInput(int id) {
    
  if (id == 0) w.Insert(GetVal(text1), GetInt(text2));
  if (id == 1) w.InsertMultiple(w.Split(GetVal(text1), "\n"), GetInt(text2));
  if (id == 2) w.Erase(GetInt(text1));
  if (id == 3) w.InsertSubstring(GetVal(text1), GetInt(text2), GetInt(text3));
  if (id == 4) w.ReplaceSymbol(GetVal(text1)[0], GetInt(text1), GetInt(text2));
  if (id == 5) w.ReplaceSubstring(GetVal(text1), GetVal(text2), GetInt(text3, 0), GetInt(text3, -1));
  if (id == 6) w.RemoveZeroes(GetInt(text1, 0), GetInt(text2, -1));
  if (id == 7) w.RemoveAsterisks(GetInt(text1, 0), GetInt(text2, -1));

  SetText(w.GetAll());
  PostMessage(hWnd1, WM_CLOSE, 0, 0);
}

// events
void Start() {
  AddButton("Insert", hWnd0, 0, {1000, 50});
  AddButton("Insert multiple", hWnd0, 1, {1000, 85});
  AddButton("Erase", hWnd0, 2, {1000, 120});

  AddButton("Insert substring", hWnd0, 3, {1000, 200});
  AddButton("Replace symbol", hWnd0, 4, {1000, 235});
  AddButton("Replace substring", hWnd0, 5, {1000, 270});

  AddButton("Remove zeroes", hWnd0, 6, {1000, 350});
  AddButton("Remove asterisks", hWnd0, 7, {1000, 385});

  w.Insert("Perfect windows xp buttons <3");
  w.Insert("Perfect Product Sans font <3");
  w.Insert("python be like: import da");
  w.Insert("c++ 20 be like: import <iostream>;");
  w.Insert("ha ha #include <Windows.h> goes brrrrrrrr");
  w.Insert("-");
  w.Insert("(Zeroes) 000000 01 0100 00000010 666 0 1488");
  w.Insert("-");
  w.Insert("(Asterisks) * ** *** **** ***** ****** ***** **** *** ** *");
  w.Insert("-");
  w.Insert("(Long string) Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris vitae urna egestas, placerat felis tincidunt, ultrices leo. Nullam id suscipit metus. Curabitur ornare magna ut nibh lobortis, non condimentum nulla efficitur. Pellentesque mauris nulla, varius a condimentum sed, dignissim eu erat. Donec quam magna, luctus id finibus eget, ornare vitae metus. Etiam congue eros orci, ac faucibus leo elementum id. Sed cursus imperdiet lacinia. Sed auctor felis sit amet tristique tincidunt. Sed nec laoreet odio. Suspendisse potenti. Fusce in est gravida, ultrices metus quis, venenatis ligula. Nulla facilisi. Nulla pretium ligula nec erat tempus, convallis feugiat odio posuere. Praesent interdum.");
}
void DrawMain() {
  PAINTSTRUCT ps;
  hdc = BeginPaint(hWnd0, &ps);
  HFONT hFont, hTmp;
  hFont =
      CreateFont(20, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 2, 0, L"Consolas");
  hTmp = (HFONT)SelectObject(hdc, hFont);
  SetBkMode(hdc, TRANSPARENT);

  int j = 0;
  for (auto i : w.strings) {
    
    
    std::string tmp_str;
    for (int p = 0, k = 0; p < i->size(); ++p, ++k) {
      tmp_str += (*i)[p];
      if (k > 105 || p == i->size()-1) {
        TCHAR text_t[1000] = L"";
        _tcscpy_s(text_t, CA2T((tmp_str).c_str()));
        TextOut(hdc, 20, j * 20 + 40, text_t, _tcslen(text_t));
        tmp_str = "";
        k = 0;
        ++j;
      }
    }
  }

  hFont = CreateFont(40, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 2, 0,
                     L"Product Sans Black");
  hTmp = (HFONT)SelectObject(hdc, hFont);
  SetBkMode(hdc, TRANSPARENT);

  TextOut(hdc, 1025, 5, L"Inserts", _tcslen(L"Inserts"));
  TextOut(hdc, 1025, 155, L"Modify", _tcslen(L"Modify"));
  TextOut(hdc, 990, 305, L"Algorithmic", _tcslen(L"Algorithmic"));
  EndPaint(hWnd0, &ps);
}
void DrawPopup() {
  PAINTSTRUCT ps;
  hdc = BeginPaint(hWnd1, &ps);
  HFONT hFont, hTmp;
  hFont = CreateFont(20, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 2, 0,
                     L"Product Sans Black");
  hTmp = (HFONT)SelectObject(hdc, hFont);
  SetBkMode(hdc, TRANSPARENT);

  TCHAR text_t[1000] = L"";
  _tcscpy_s(text_t, CA2T(now_name.c_str()));
  TextOut(hdc, 20, 5, text_t, _tcslen(text_t));
  EndPaint(hWnd1, &ps);
}
void OnButtonClick(int id) {
  if (id == 0) PopUpWindow(0);
  if (id == 1) PopUpWindow(1);
  if (id == 2) PopUpWindow(2);
  if (id == 3) PopUpWindow(3);
  if (id == 4) PopUpWindow(4);
  if (id == 5) PopUpWindow(5);
  if (id == 6) PopUpWindow(6);
  if (id == 7) PopUpWindow(7);

  if (id == 100) EndInput(0);
  if (id == 101) EndInput(1);
  if (id == 102) EndInput(2);
  if (id == 103) EndInput(3);
  if (id == 104) EndInput(4);
  if (id == 105) EndInput(5);
  if (id == 106) EndInput(6);
  if (id == 107) EndInput(7);
}