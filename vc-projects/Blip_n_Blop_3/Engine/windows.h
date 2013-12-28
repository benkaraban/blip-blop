#ifndef WINDOWS_H
#define WINDOWS_H

#include <cstdlib> // so NULL is defined everywhere

using namespace std;

#define CALLBACK
#define WINAPI

#define TRUE true
#define FALSE false

typedef unsigned short WORD;
typedef WORD ATOM;
typedef long LONG;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef char CHAR;
typedef bool BOOL;
typedef void VOID;
typedef DWORD *LPDWORD;
typedef unsigned int UINT;
typedef VOID* PVOID;
typedef PVOID LPVOID;
typedef PVOID HANDLE;
typedef LONG HRESULT;
typedef size_t SIZE_T;
#define CONST const
typedef CONST CHAR *LPCSTR;
typedef HANDLE HDC;
typedef HANDLE HWND;
typedef unsigned int UINT_PTR;
typedef UINT_PTR WPARAM;
typedef long LONG_PTR;
typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;
typedef HANDLE HINSTANCE;
typedef HANDLE HBITMAP;
typedef CHAR *LPSTR;
typedef HANDLE HMENU;
typedef DWORD COLORREF;

#ifdef UNICODE
typedef WCHAR TCHAR;
typedef LPCWSTR LPCTSTR;
#else
typedef char TCHAR;
typedef LPCSTR LPCTSTR;
#endif

#define CS_HREDRAW 0x1
#define CS_VREDRAW 0x2
typedef long(*WNDPROC)(HWND, UINT, WPARAM, LPARAM);

typedef struct tagBITMAP {
	LONG   bmType;
	LONG   bmWidth;
	LONG   bmHeight;
	LONG   bmWidthBytes;
	WORD   bmPlanes;
	WORD   bmBitsPixel;
	LPVOID bmBits;
} BITMAP, *PBITMAP;


typedef struct tagWNDCLASS {
	UINT      style;
	WNDPROC   lpfnWndProc;
	int       cbClsExtra;
	int       cbWndExtra;
	HINSTANCE hInstance;
	int     hIcon; //TODO
	int   hCursor; //TODO
	int    hbrBackground; //TODO
	LPCTSTR   lpszMenuName;
	LPCTSTR   lpszClassName;
} WNDCLASS, *PWNDCLASS;

#define DUMMYUNIONNAMEN(x)

typedef struct _POINTL {
	LONG x;
	LONG y;
} POINTL, *PPOINTL;
#define CCHDEVICENAME 32
#define CCHFORMNAME 32
typedef struct _devicemode {
	TCHAR dmDeviceName[CCHDEVICENAME];
	WORD  dmSpecVersion;
	WORD  dmDriverVersion;
	WORD  dmSize;
	WORD  dmDriverExtra;
	DWORD dmFields;
	union {
		struct {
			short dmOrientation;
			short dmPaperSize;
			short dmPaperLength;
			short dmPaperWidth;
			short dmScale;
			short dmCopies;
			short dmDefaultSource;
			short dmPrintQuality;
		};
		struct {
			POINTL dmPosition;
			DWORD  dmDisplayOrientation;
			DWORD  dmDisplayFixedOutput;
		};
	};
	short dmColor;
	short dmDuplex;
	short dmYResolution;
	short dmTTOption;
	short dmCollate;
	TCHAR dmFormName[CCHFORMNAME];
	WORD  dmLogPixels;
	DWORD dmBitsPerPel;
	DWORD dmPelsWidth;
	DWORD dmPelsHeight;
	union {
		DWORD dmDisplayFlags;
		DWORD dmNup;
	};
	DWORD dmDisplayFrequency;
#if (WINVER >= 0x0400)
	DWORD dmICMMethod;
	DWORD dmICMIntent;
	DWORD dmMediaType;
	DWORD dmDitherType;
	DWORD dmReserved1;
	DWORD dmReserved2;
#if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
	DWORD dmPanningWidth;
	DWORD dmPanningHeight;
#endif
#endif
} DEVMODE, *PDEVMODE, *LPDEVMODE;

typedef struct tagRGBQUAD {
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
} RGBQUAD;
#define DM_BITSPERPEL 0x1
#define DM_PELSWIDTH 0x2
#define DM_PELSHEIGHT 0x4
#define DM_DISPLAYFREQUENCY 0x8
#define DISP_CHANGE_SUCCESSFUL 0x1
#define CDS_TEST 0x1
#define CDS_FULLSCREEN 0x2
#define MB_OK 0x1
#define MB_ICONERROR 0x2
#define MB_ICONWARNING 0x4
#define MB_YESNO 0x8
#define MB_ICONQUESTION 0x16
#define IDYES 6

#define WS_POPUP 0x1

#define FAR
#define NEAR

enum {
	WM_SETCURSOR,
	WM_ACTIVATE,
	WM_CLOSE,
	WM_DESTROY,
	WM_TIMER,
};

void ZeroMemory(PVOID Destination, SIZE_T Length);

LONG ChangeDisplaySettings(DEVMODE *lpDevMode, DWORD dwflags);
int MessageBox(HWND hWnd,LPCTSTR lpText,LPCTSTR lpCaption,UINT uType);

void SetCursor(bool);
WORD HIWORD(DWORD dwValue);
VOID WINAPI PostQuitMessage(int nExitCode);
LRESULT WINAPI DefWindowProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
ATOM WINAPI RegisterClass(const WNDCLASS *lpWndClass);
#define SM_CXSCREEN 0x1
#define SM_CYSCREEN 0x2
int WINAPI GetSystemMetrics(int nIndex);
HWND WINAPI CreateWindowEx(DWORD dwExStyle,LPCTSTR lpClassName,LPCTSTR lpWindowName,DWORD dwStyle,int x,int y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,LPVOID lpParam);
BOOL WINAPI ShowWindow(HWND hWnd,int nCmdShow);
BOOL UpdateWindow(HWND hWnd);

typedef VOID(*TIMERPROC)(HWND hwnd,UINT uMsg,UINT_PTR idEvent,DWORD dwTime);
UINT_PTR WINAPI SetTimer(HWND hWnd,UINT_PTR nIDEvent,UINT uElapse,TIMERPROC lpTimerFunc);
BOOL WINAPI DestroyWindow(HWND hWnd);

void Sleep(int);
DWORD WINAPI GetTickCount(void);

COLORREF RGB(BYTE byRed,BYTE byGreen,BYTE byBlue);



#endif
