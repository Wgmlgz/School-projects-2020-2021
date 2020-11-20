#include "WindowHandler.h"



int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
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

  hWnd0 = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                   CW_USEDEFAULT, 1200, 720, NULL, NULL, hInstance, NULL);
  
  Start();

  if (!hWnd0) {
    MessageBox(NULL, _T("Call to CreateWindow failed!"),
               _T("Windows Desktop Guided Tour"), NULL);

    return 1;
  }

  // The parameters to ShowWindow explained:
  // hWnd: the value returned from CreateWindow
  // nCmdShow: the fourth parameter from WinMain
  nCmd = nCmdShow;
  ShowWindow(hWnd0, nCmdShow);
  UpdateWindow(hWnd0);
  
  

  // Main message loop:
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  PAINTSTRUCT ps;
  
  

  if (message == WM_CREATE) {
      SetTimer(hWnd, 1, 20, NULL);
  }
  else if (message == WM_PAINT) {
    if (hWnd == hWnd0) {
      hdc = BeginPaint(hWnd, &ps);
      HFONT hFont, hTmp;
      hFont = CreateFont(20, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 2, 0, L"Consolas");
      hTmp = (HFONT)SelectObject(hdc, hFont);
      SetBkMode(hdc, TRANSPARENT);


      int j = 0;
      for (auto i : w.strings) {
        TCHAR text_t[1000] = L"";
        _tcscpy_s(text_t, CA2T((*i).c_str()));



        TextOut(hdc, 20, j * 20, text_t, _tcslen(text_t));
        ++j;
      }

      hFont = CreateFont(40, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 2, 0,
                         L"Product Sans Black");
      hTmp = (HFONT)SelectObject(hdc, hFont);
      SetBkMode(hdc, TRANSPARENT);

      TextOut(hdc, 1025, 5, L"Inserts", _tcslen(L"Inserts"));
      TextOut(hdc, 1025, 155, L"Modify", _tcslen(L"Modify"));
      TextOut(hdc, 990, 305, L"Algorithmic", _tcslen(L"Algorithmic"));
      EndPaint(hWnd, &ps);
    }
    if (hWnd == hWnd1) {
      hdc = BeginPaint(hWnd, &ps);
      HFONT hFont, hTmp;
      hFont = CreateFont(20, 0, 0, 0, FW_MEDIUM, 0, 0, 0, 0, 0, 0, 2, 0, L"Product Sans Black");
      hTmp = (HFONT)SelectObject(hdc, hFont);
      SetBkMode(hdc, TRANSPARENT);


      TCHAR text_t[1000] = L"";
      _tcscpy_s(text_t, CA2T(now_name.c_str()));
      TextOut(hdc, 20, 5, text_t, _tcslen(text_t));
      EndPaint(hWnd, &ps);
    }
  }
  else if (message == WM_DESTROY) {
    if (hWnd == hWnd0) PostQuitMessage(0);
    else PostMessage(hWnd, WM_CLOSE, 0, 0);
  }
  else if (message == WM_COMMAND) {
    if (HIWORD(wParam) == BN_CLICKED) {
      SetText(std::to_string(LOWORD(lParam)));
      if (wParam == 0) PopUpWindow(0);
      if (wParam == 1) PopUpWindow(1);
      if (wParam == 2) PopUpWindow(2);
      if (wParam == 3) PopUpWindow(3);
      if (wParam == 4) PopUpWindow(4);
      if (wParam == 5) PopUpWindow(5);
      if (wParam == 6) PopUpWindow(6);
      if (wParam == 7) PopUpWindow(7);

      //if (wParam == 100) {
      //  now_name = GetVal(text1) + "                                           ";
      //  //MessageBox(hWnd0, wt, wt, NULL);
      //  RedrawWindow1();
      //}
      if (wParam == 100) EndInput(0);
      if (wParam == 101) EndInput(1);
      if (wParam == 102) EndInput(2);
      if (wParam == 103) EndInput(3);
      if (wParam == 104) EndInput(4);
      if (wParam == 105) EndInput(5);
      if (wParam == 106) EndInput(6);
      if (wParam == 107) EndInput(7);
    }
  }
  else {
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

void Start() {
  AddButton("Insert", hWnd0, 0, {1000, 50});
  AddButton("InsertMultiple", hWnd0, 1, {1000, 85});
  AddButton("Erase", hWnd0, 2, {1000, 120});

  AddButton("InsertSubstring", hWnd0, 3, {1000, 200});
  AddButton("ReplaceSymbol", hWnd0, 4, {1000, 235});
  AddButton("ReplaceSubstring", hWnd0, 5, {1000, 270});

  AddButton("RemoveZeroes", hWnd0, 6, {1000, 350});
  AddButton("RemoveAsterisks", hWnd0, 7, {1000, 385});

  w.Insert("dfdsfdfdfdsfdsfsdf dsfdsf dsf dsfdsf dsf");
  w.Insert("  fdsf sdf sdf ds fsdf sdf sd*");
  w.Insert(" sfd f sd sdf s sfdff sd ");
  w.Insert("  fdsdfsdfs*");
  w.Insert("* fdsf d f dsfsdfsdfsdfsdfdsfsdfsfsdfsdfsdfsdfdsfsdfss*");
  w.Insert("*fsd fd fs sd fsd fsd fsd fs *");
  w.Insert("*******");
  w.Insert("*** dsfsdf sdf sdf ds dsf ds ffd fds ****");
}
std::string GetVal(HWND w) {
  char t[100];
  wchar_t wt[100];
  GetWindowText(w, &wt[0], 100);
  std::wstring ws(wt);
  std::string str(ws.begin(), ws.end());
  return str;
}
int GetInt(HWND w, int i = 0) {
  try {
    return std::stoi(GetVal(text1));
  } catch (std::invalid_argument) {
    return 0;
  }
}
void AddButton(std::string name, HWND hWnd, int id, Vec2 pos,
                                  Vec2 size) {
  std::wstring wide_string = std::wstring(name.begin(), name.end());
  const wchar_t* result = wide_string.c_str();
  HWND hwndButton = CreateWindowEx(
      0, L"BUTTON", result, WS_CHILD | WS_VISIBLE | BS_FLAT, 
      pos.x, pos.y, size.x, size.y,
      hWnd, (HMENU)id, GetModuleHandle(NULL), NULL);
  //SendMessage((HWND)hwndButton, (UINT)BM_SETIMAGE, (WPARAM)IMAGE_BITMAP,
              //(LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1)));
}
HWND AddInputText(std::string name, HWND hWnd, int id, Vec2 pos, Vec2 size) {
  if (name == "") return (HWND)NULL;
  std::wstring wide_string = std::wstring(name.begin(), name.end());
  const wchar_t* result = wide_string.c_str();
  HWND hwndT = CreateWindowEx(0, L"EDIT", result,
                              WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
      pos.x, pos.y, size.x, size.y,
      hWnd1, (HMENU)id, GetModuleHandle(NULL), NULL);
  /*TCHAR lpszLatin[] =
      L"Lorem ipsum dolor sit amet, consectetur "
      L"adipisicing elit, sed do eiusmod tempor "
      L"incididunt ut labore et dolore magna "
      L"aliqua. Ut enim ad minim veniam, quis "
      L"nostrud exercitation ullamco laboris nisi "
      L"ut aliquip ex ea commodo consequat. Duis "
      L"aute irure dolor in reprehenderit in "
      L"voluptate velit esse cillum dolore eu "
      L"fugiat nulla pariatur. Excepteur sint "
      L"occaecat cupidatat non proident, sunt "
      L"in culpa qui officia deserunt mollit "
      L"anim id est laborum."; 
  SendMessage(hwndT, WM_SETTEXT, 0, (LPARAM)lpszLatin); */
  return hwndT;
}
void SetText(std::string s) {
  text = s + "                                                                          ";
  RedrawWindow(); 
  //MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Windows Desktop Guided Tour"), NULL);
}
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
  AddButton(std::to_string(id + 100), hWnd1, id + 100, {200, 170});
  text1 = AddInputText(s1, hWnd1, 2, {20, 25}, {440, id == 1 ? 100 : 30});
  text2 = AddInputText(s2, hWnd1, 3, {20, id == 1 ? 130 : 60}, {440, 30});
  text3 = AddInputText(s3, hWnd1, 3, {20, 95}, {440, 30});
  text4 = AddInputText(s4, hWnd1, 3, {20, 130}, {440, 30});

  ShowWindow(hWnd1, nCmd);
  UpdateWindow(hWnd1);
}
void RedrawWindow() {
  InvalidateRect(hWnd0, NULL, NULL);
}
void RedrawWindow1() {
    InvalidateRect(hWnd1, NULL, NULL);
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