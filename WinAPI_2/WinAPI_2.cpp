#ifndef UNICODE
#define UNICODE
#endif 

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <string.h>

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
const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 970;
const int n = 10;
const int m = 10;
const WCHAR text[] = L"Test Test Test";
const int fontSize = 50.0f;
HDC hdcBuffer = NULL;
HBITMAP hBitmap = NULL;
HBITMAP hOldBitmap = NULL;
HFONT hFont = NULL;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
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


void CircleText(HWND hwnd, HDC hdc) {
    int centerX = 200;
    int centerY = 200;
    int radius = 100;   
    int fontSize = 15;

    size_t pcch = 22;
    int n = pcch;
    double angle = 270;
    double text_angle = 0;
    double delta_angle = 360.0 / n;
    double center_x = 200;
    double center_y = 200;
    double start_x = 200;
    double start_y = 100;
    double x = start_x;
    double y = start_y;
    int radius_2 = 100 + fontSize;
    PLOGFONT plf = (PLOGFONT)LocalAlloc(LPTR, sizeof(LOGFONT));
    HGDIOBJ hfnt, hfntPrev; 
    WCHAR lpszRotate[22] = TEXT("String to be rotated.");
    HRESULT hr;
    hr = StringCchCopy(plf->lfFaceName, 6, TEXT("Arial"));        
    plf->lfWeight = FW_NORMAL;
    plf->lfHeight = MulDiv(fontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
    SetBkMode(hdc, TRANSPARENT);
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255)); // Создаем синий перо
    HGDIOBJ hOldPen = SelectObject(hdc, hPen);  
    Ellipse(hdc, centerX - radius_2, centerY - radius_2, centerX + radius_2, centerY + radius_2); // Рисуем окружность
    Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);  
    int size = GetOutlineTextMetrics(hdc, 0, NULL);
    OUTLINETEXTMETRICA* otm = (OUTLINETEXTMETRICA*)malloc(size);
    GetOutlineTextMetricsA(hdc, size, otm);
    double text_radius = radius + plf->lfHeight;
    for (int i=0;i<n;i++)
    {
        x = center_x + cos(angle * PI / 180)* text_radius;
        y = center_y + sin(angle * PI / 180)* text_radius;
        angle += delta_angle;
        plf->lfEscapement = text_angle;
        text_angle -= delta_angle*10;
        hfnt = CreateFontIndirect(plf);
        hfntPrev = SelectObject(hdc, hfnt);
        WCHAR test[2] = {lpszRotate[i]};
        hr = StringCchLength(test, 22, &pcch);
        TextOut(hdc, x, y,test, pcch);
        SelectObject(hdc, hfntPrev);
        DeleteObject(hfnt);
    }
    SetBkMode(hdc, OPAQUE);
    LocalFree((LOCALHANDLE)plf);
}


void DrawTable(HWND hwnd, HDC hdc) {
    float x = 0.0;
    float y = 0.0;
    RECT client_rect, cell_rect;
    GetClientRect(hwnd, &client_rect);
    int width = client_rect.right - client_rect.left;
    int height = client_rect.bottom - client_rect.top;
    for (int i = 0; i < m-1; i++)
    {
        x += (width / m);
        MoveToEx(hdc, x, 0, NULL);
        LineTo(hdc, x, height);
    }
    for (int i = 0; i < n; i++)
    {
        x = 0.0;
        for (int j = 0; j < m; j++)
        {
            int textSize = ARRAYSIZE(text) - 1;          
            cell_rect.left = x+2;
            cell_rect.top = y+2;
            cell_rect.right = x + (width / m);
            cell_rect.bottom = y+ (height / n);          
            DrawTextW(hdc, text, textSize, &cell_rect, DT_WORDBREAK);            
            x += (width / m);
        }
        y += (height / n);
        MoveToEx(hdc, 0, y, NULL);
        LineTo(hdc, width, y);
    }
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
    {
        if (hFont != NULL) {
            DeleteObject(hFont);
        }

        if (hdcBuffer != NULL) {
            DeleteDC(hdcBuffer);
        }

        if (hBitmap != NULL) {
            SelectObject(hdcBuffer, hOldBitmap);
            DeleteObject(hBitmap);
        }

        PostQuitMessage(0);
        return 0;
    }
    case WM_SIZE: {
        RECT rect, client_rect, cell_rect;
        GetClientRect(hwnd, &client_rect);
        int width = client_rect.right - client_rect.left;
        int height = client_rect.bottom - client_rect.top;
        int array_len = ARRAYSIZE(text) - 1;
        int temp = fontSize;
        int text_rows = (temp * array_len) / (width / m);
        while ((temp * text_rows) > (height / n)) {
            temp -= 1.0f;
            text_rows = (temp * array_len) / (width / m);
        }
        if (hFont != NULL) {
            DeleteObject(hFont);
        }
        hFont = CreateFont(temp, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, L"Arial");
        HDC hdc = GetDC(hwnd);
        hdcBuffer = CreateCompatibleDC(hdc);
        hBitmap = CreateCompatibleBitmap(hdc, width, height);
        hOldBitmap = (HBITMAP)SelectObject(hdcBuffer, hBitmap);
        ReleaseDC(hwnd, hdc);
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    } 
    case WM_ERASEBKGND:
        return 1;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        /*HBRUSH hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        FillRect(hdcBuffer, &clientRect, hWhiteBrush);
        DeleteObject(hWhiteBrush);
        if (hFont != NULL) {
            SelectObject(hdcBuffer, hFont);
        }
        DrawTable(hwnd, hdcBuffer);
        BitBlt(hdc, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom, hdcBuffer, 0, 0, SRCCOPY);
       */ 
        CircleText(hwnd, hdc);

        EndPaint(hwnd, &ps);
        break;
    } 
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
