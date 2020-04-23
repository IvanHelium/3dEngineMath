

#include <iostream>
#include<Windows.h>
#include <strsafe.h>
#include <cmath>
#include <string>  
#include <sstream>
#include "Engine3D.h"
#include "Draw.h"




LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL DrawLine(HDC, int, int, int, int);

PAINTSTRUCT ps;

static int x, y;
static int a, b;

Engine3D engine3D;
float elapsedTime;
RECT Rect;
WCHAR textBuffer[50];


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR szCmdLine, int iCmdShow)
{
    static char szAppName[] = "DrawingWindow";
    HWND hwnd;
    MSG msg;
    WNDCLASSEX wndclass;
    elapsedTime = 0.0;


    wndclass.cbSize = sizeof(wndclass);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wndclass);

    hwnd = CreateWindow(
        szAppName, // window class name 
        "DrawingWindow", // window caption 
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, // window style 
        CW_USEDEFAULT, // initial x position 
        CW_USEDEFAULT, // initial y position 
        CW_USEDEFAULT, // initial x size 
        CW_USEDEFAULT, // initial y size 
        NULL, // parent window handle 
        NULL, // window menu handle 
        hInstance, // program instance handle 
        NULL
    );
    
    //set rectangle in start (screen height and width
    GetClientRect(hwnd, &Rect);
    engine3D.setRect(Rect);
    engine3D.OnUserCreate();

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

    PAINTSTRUCT ps;
    HDC hdc, hCmpDC;
    HBITMAP hBmp;

    //for printing windows caption
    

    switch (iMsg) {

    case WM_CREATE:
        SetTimer(hwnd, 0, 50, NULL);
        break;
    case WM_TIMER:
        InvalidateRect(hwnd, &Rect, FALSE);
        elapsedTime += 0.0001f;

        break;
    case WM_PAINT:
        GetClientRect(hwnd, &Rect);
        hdc = BeginPaint(hwnd, &ps);

        // Создание теневого контекста для двойной буферизации
        hCmpDC = CreateCompatibleDC(hdc);
        hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left,
            Rect.bottom - Rect.top);
        SelectObject(hCmpDC, hBmp);

        // Закраска фоновым цветом
        LOGBRUSH br;
        br.lbStyle = BS_SOLID;
        br.lbColor = 0x00000F;  //0xEECCCC
        HBRUSH brush;
        brush = CreateBrushIndirect(&br);
        FillRect(hCmpDC, &Rect, brush);
        DeleteObject(brush);


        engine3D.setHDC(hCmpDC);
        engine3D.setRect(Rect);
        // Здесь рисуем на контексте hCmpDC


        
        swprintf((LPWSTR)textBuffer, 50, L"elapsedTime :  %f", (float)elapsedTime);
        TextOut(hCmpDC, 10, 20, (LPCSTR)textBuffer, 42);
        
        
        engine3D.OnUserUpdate(elapsedTime);

        // Копируем изображение из теневого контекста на экран
        SetStretchBltMode(hdc, COLORONCOLOR);
        BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
            hCmpDC, 0, 0, SRCCOPY);

        // Удаляем ненужные системные объекты
        DeleteDC(hCmpDC);
        DeleteObject(hBmp);
        hCmpDC = NULL;

        EndPaint(hwnd, &ps);
        break;
    case WM_LBUTTONDOWN:

        break;
    case WM_MOUSEMOVE:
           
        return 0;
    case WM_LBUTTONUP:
    {
        
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
