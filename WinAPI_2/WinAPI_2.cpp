#ifndef UNICODE
#define UNICODE
#endif 

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include "Resource.h"
#include <commctrl.h>
#include <Windows.h>
#include <winuser.h>
#include <windowsx.h>
#include "strsafe.h"
#include <cmath> 
#include <math.h> 

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

const double PI = 3.14159265358979323846;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);
    HWND hwnd = CreateWindowEx(
        0,                                // Optional window styles.
        CLASS_NAME,                       // Window class
        L"Time killer",                   // Window text
        WS_OVERLAPPEDWINDOW,// Window style
        CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );
    if (hwnd == NULL)
    {
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    MSG msg = { };
    while (GetMessageW(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    wchar_t msg[32];
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CREATE:
    {

        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        //// Задайте параметры кисти для рисования круга
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // Красная кисть
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        
        RECT rc;
        HGDIOBJ hfnt, hfntPrev;
        WCHAR lpszRotate[22] = TEXT("String to be rotated.");
        HRESULT hr;
        size_t pcch = 22;
        PLOGFONT plf = (PLOGFONT)LocalAlloc(LPTR, sizeof(LOGFONT));
        hr = StringCchCopy(plf->lfFaceName, 6, TEXT("Arial"));        
        plf->lfWeight = FW_NORMAL;
        GetClientRect(hwnd, &rc);
        SetBkMode(hdc, TRANSPARENT);
        double angle = 0;
        double delta_angle = 360 / 22;
        double center_x = 200;
        double center_y = 200;
        double radius = 100;
        double start_x = 200;
        double start_y = 100;
        double x = start_x;
        double y = start_y;
        for (int i=0;i<=22;i++)
        {

            x = center_x + cos(angle * 3.14 / 180)*100;
            y = center_y + sin(angle * 3.14 / 180)*100;
            angle += delta_angle;
            MoveToEx(hdc, center_x, center_y, NULL);
            LineTo(hdc, x, y);
            /*plf->lfEscapement = angle;
            angle += delta_angle;
            hfnt = CreateFontIndirect(plf);
            hfntPrev = SelectObject(hdc, hfnt);
            WCHAR test[2] = {lpszRotate[0] };
            hr = StringCchLength(test, 22, &pcch);
            TextOut(hdc, rc.right / 2 + angle/50, rc.bottom / 2,
                test, pcch);
            SelectObject(hdc, hfntPrev);
            DeleteObject(hfnt);*/
        }
        SetBkMode(hdc, OPAQUE);
        LocalFree((LOCALHANDLE)plf);

       /* int centerX = 100; 
        int centerY = 100; 
        int radius = 100;  
        Ellipse(hdc, WINDOW_WIDTH/2 - radius, WINDOW_HEIGHT/ 2 - radius, WINDOW_WIDTH / 2 + radius, WINDOW_HEIGHT / 2 + radius);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBrush);
        MoveToEx(hdc, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, NULL);
        LineTo(hdc, WINDOW_WIDTH / 2 + 100, WINDOW_HEIGHT / 2);
        double angle = 30 * 3.14 / 180;
        MoveToEx(hdc, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, NULL);
        LineTo(hdc, WINDOW_WIDTH / 2 + cos(angle) * 100, WINDOW_HEIGHT / 2 + sin(angle) * 100);*/

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        
        break;
    }
    case WM_LBUTTONUP:
    {
        
        break;
    }
    case WM_MOUSEMOVE:
    {
        
        break;
    }
    case WM_TOUCH:
    {
        break;
    }
    case WM_KEYDOWN:
    {
        
        break;
    }
    case WM_MOUSEWHEEL:
    {
        
        break;
    }
    case WM_TIMER:
    {
        
        break;
    }
    case WM_COMMAND:
    {
        
        break;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}