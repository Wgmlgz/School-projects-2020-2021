#include "PolyUi.h"
#include <Windows.h>

using namespace PolynomialsFrontend;
[STAThread] int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);
  Application::Run(gcnew PolyUi);
  return 0;
}