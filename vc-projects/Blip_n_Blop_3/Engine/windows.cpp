#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <unistd.h>

#include <SDL.h>

#include "windows.h"

#define STUB { \
    printf("stub %s %d\n", __func__, __LINE__); \
}

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

LONG ChangeDisplaySettings(DEVMODE *lpDevMode, DWORD dwflags) STUB
int MessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType)
{
    printf("MessageBox(%s)\n", lpText);
}

void SetCursor(void*) STUB
WORD HIWORD(DWORD dwValue) STUB
VOID WINAPI PostQuitMessage(int nExitCode) STUB
LRESULT WINAPI DefWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) STUB
ATOM WINAPI RegisterClass(const WNDCLASS *lpWndClass) STUB
int WINAPI GetSystemMetrics(int nIndex) STUB
HWND WINAPI CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) STUB
BOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow) STUB
BOOL UpdateWindow(HWND hWnd) {
}
UINT_PTR WINAPI SetTimer(HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc) STUB
BOOL WINAPI DestroyWindow(HWND hWnd) STUB
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

HMODULE WINAPI GetModuleHandle(LPCTSTR lpModuleName) STUB

HANDLE WINAPI LoadImage(HINSTANCE hinst, LPCTSTR lpszName, UINT uType, int cxDesired, int cyDesired, UINT fuLoad) STUB

int GetObject(HGDIOBJ hgdiobj, int cbBuffer, LPVOID lpvObject) STUB
BOOL DeleteObject(HGDIOBJ hObject) STUB
HDC CreateCompatibleDC(HDC hdc) STUB
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj) STUB

BOOL StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop) STUB

COLORREF GetPixel(HDC hdc, int nXPos, int nYPos) STUB
COLORREF SetPixel(HDC hdc, int X, int Y, COLORREF crColor) STUB
BOOL SetPixelV(HDC hdc, int X, int Y, COLORREF crColor) STUB

BOOL DeleteDC(HDC hdc) STUB
LPVOID WINAPI LockResource(HGLOBAL hResData) STUB
HGLOBAL WINAPI LoadResource(HMODULE hModule, HRSRC hResInfo) STUB
HRSRC WINAPI FindResource(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType) STUB

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
LRESULT WINAPI DispatchMessage(const MSG *lpmsg) STUB
BOOL WINAPI TranslateMessage(const MSG *lpMsg) STUB
BOOL WINAPI GetMessage(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax) {}

char* _itoa(int value, char* str, int base) {
    SDL_itoa(value, str, base);
}


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
