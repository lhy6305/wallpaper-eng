#include <windows.h>
#include <fstream>
using namespace std;

HWND twid; // target window handle

extern "C"
{
    extern "C" __declspec(dllexport) void hook(_In_ int tid);
}

BOOLEAN WINAPI DllMain(IN HINSTANCE hDllHandle, IN DWORD nReason, IN LPVOID Reserved){
    string strTempPath;
    char wchPath[MAX_PATH];
    if (GetTempPathA(MAX_PATH, wchPath)){
        strTempPath = wchPath;
    }

    ifstream fi(strTempPath + "tmp_lhy6305_wallpaperwindow.hwnd");
    if(fi.good()){
        string tmp;
        fi>>tmp;
        twid = (HWND)strtoul(tmp.c_str(), NULL, 10);
        fi.close();
    }
    if(twid == NULL){
        MessageBox(NULL, "invalid twid", "", MB_OK);
    }
    return true;
}

LRESULT HookProcKeyboard(int nCode, WPARAM wParam, LPARAM lParam){
    LRESULT rtn = CallNextHookEx(NULL, nCode, wParam, lParam);
    if(lParam & 0x40000000){
        PostMessage(twid, 257, wParam, lParam);
    }else{
        PostMessage(twid, 256, wParam, lParam);
    }
    return rtn;
}

LRESULT HookProcMouse(int nCode, WPARAM wParam, LPARAM lParam){
    LRESULT rtn = CallNextHookEx(NULL, nCode, wParam, lParam);
    MOUSEHOOKSTRUCTEX* mouse = (MOUSEHOOKSTRUCTEX*)lParam;
    if(wParam == 522){
        PostMessage(twid, wParam, MAKEWPARAM(0, GET_WHEEL_DELTA_WPARAM(mouse->mouseData)), MAKELPARAM(mouse->pt.x, mouse->pt.y));
    }else{
        PostMessage(twid, wParam, 0, MAKELPARAM(mouse->pt.x, mouse->pt.y));
    }
    return rtn;
}

void hook(_In_ int tid){
    if (SetWindowsHookEx(WH_KEYBOARD, HookProcKeyboard, GetModuleHandle("1.dll"), tid) == NULL){
        MessageBox(NULL, "WH_KEYBOARD hook install failed", "", MB_OK);
    }
    if (SetWindowsHookEx(WH_MOUSE, HookProcMouse, GetModuleHandle("1.dll"), tid) == NULL){
        MessageBox(NULL, "WH_MOUSE hook install failed", "", MB_OK);
    }
}