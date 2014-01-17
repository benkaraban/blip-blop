#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <unistd.h>

#include <SDL.h>

#include "windows.h"

HANDLE WINAPI CreateFile(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, void* unused, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
    assert(dwDesiredAccess == GENERIC_READ);
    assert(dwCreationDisposition == OPEN_EXISTING);
    const char* mode = "r";
    FILE* file = fopen(lpFileName, mode);
    if (!file) {
        printf("[PORTAGE] CreateFile can't create %s\n", lpFileName);
    }
    return file;
}

BOOL WINAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
{
    FILE* file = (FILE*) hFile;
    *lpNumberOfBytesRead = fread(lpBuffer, nNumberOfBytesToRead, 1, file);
    return *lpNumberOfBytesRead > 0;
}

BOOL WINAPI CloseHandle(HANDLE hObject)
{
    FILE* file = (FILE*) hObject;
    return fclose(file) == 0;
}

long _filelength(int fd)
{
    long size = lseek(fd, 0L, SEEK_END);
    lseek(fd, 0L, SEEK_SET);
    return size;
}

void ZeroMemory(PVOID Destination, SIZE_T Length) {
    memset(Destination, 0, Length);
}

LONG ChangeDisplaySettings(DEVMODE *lpDevMode, DWORD dwflags) {}
int MessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType)
{
    printf("MessageBox(%s)\n", lpText);
}

void SetCursor(void*) {}
WORD HIWORD(DWORD dwValue) {}
VOID WINAPI PostQuitMessage(int nExitCode) {}
LRESULT WINAPI DefWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {}
ATOM WINAPI RegisterClass(const WNDCLASS *lpWndClass) {}
int WINAPI GetSystemMetrics(int nIndex) {}
HWND WINAPI CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {}
BOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow) {}
BOOL UpdateWindow(HWND hWnd) {}
UINT_PTR WINAPI SetTimer(HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc) {}
BOOL WINAPI DestroyWindow(HWND hWnd) {}
void Sleep(int ms)
{
    SDL_Delay(ms);
}
DWORD WINAPI GetTickCount(void) {
    return SDL_GetTicks();
}

COLORREF RGB(BYTE byRed, BYTE byGreen, BYTE byBlue) {
    return byRed | (byGreen << 8) | (byBlue << 16);
}

HMODULE WINAPI GetModuleHandle(LPCTSTR lpModuleName) {}

HANDLE WINAPI LoadImage(HINSTANCE hinst, LPCTSTR lpszName, UINT uType, int cxDesired, int cyDesired, UINT fuLoad) {}

int GetObject(HGDIOBJ hgdiobj, int cbBuffer, LPVOID lpvObject) {}
BOOL DeleteObject(HGDIOBJ hObject) {}
HDC CreateCompatibleDC(HDC hdc) {}
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj) {}

BOOL StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop) {}

COLORREF GetPixel(HDC hdc, int nXPos, int nYPos) {}
COLORREF SetPixel(HDC hdc, int X, int Y, COLORREF crColor) {}
BOOL SetPixelV(HDC hdc, int X, int Y, COLORREF crColor) {}

BOOL DeleteDC(HDC hdc) {}
LPVOID WINAPI LockResource(HGLOBAL hResData) {}
HGLOBAL WINAPI LoadResource(HMODULE hModule, HRSRC hResInfo) {}
HRSRC WINAPI FindResource(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType) {}

DWORD timeGetTime(void) {
    return SDL_GetTicks();
}
BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency) {
    *lpFrequency = SDL_GetPerformanceFrequency();
    return true;
}
BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount) {
    *lpPerformanceCount = SDL_GetPerformanceCounter();
    return true;
}

BOOL WINAPI PeekMessage(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg) {}
LRESULT WINAPI DispatchMessage(const MSG *lpmsg) {}
BOOL WINAPI TranslateMessage(const MSG *lpMsg) {}
BOOL WINAPI GetMessage(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax) {}

char* _itoa(int value, char* str, int base) {}


extern "C" {
    void FSOUND_Sample_Free() {}
    void FSOUND_Sample_Load() {}
    void FSOUND_Sample_SetLoopMode() {}
    void FSOUND_PlaySound() {}
    void FSOUND_StopSound() {}
    void FMUSIC_FreeSong() {}
    void FSOUND_Stream_Close() {}
    void FMUSIC_LoadSong() {}
    void FSOUND_Stream_OpenFile() {}
    void FSOUND_GetError() {}
    void FMUSIC_PlaySong() {}
    void FSOUND_Stream_Play() {}
    void FMUSIC_StopSong() {}
    void FSOUND_Stream_Stop() {}
    void FMUSIC_SetMasterVolume() {}
    void FSOUND_Close() {}
    void FSOUND_Init() {}
    void FSOUND_SetPriority() {}
}
