#include <iostream>
#include <windows.h>
#include <winuser.h>

#include "util.hpp"
#include "MainMenu.hpp"
#include "MouseEvents.hpp"

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    state_of_game = MAINMENU;


    LPCSTR class_name = "Mario Rip Off";

    LPCSTR WindowName = "mario rip off";

    WNDCLASS wc = { };

    wc.lpfnWndProc = MainWndProc;
    wc.lpszClassName = class_name;
    wc.hInstance = hInst;

    RegisterClass(&wc);

    HWND hWnd = CreateWindowExA(
        0,
        class_name,
        WindowName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,
        NULL,
        hInst,
        NULL
    );
    if(hWnd == 0)
    {
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);

    MSG msg = { };
    while(GetMessage(&msg, NULL,0 ,0 ))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    SetWindowPos(hWnd, 0, 0, 0, 1200, 800, 0);

    return 0;
}


LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_SIZE:
            {
                RECT rect;
                GetWindowRect(hwnd, &rect);
                SetWindowPos(hwnd, 0, rect.left, rect.top, 1200, 800, 0);
                break;
            }
            break;
        case WM_CREATE:
            SetTimer(hwnd, 0, 10, (TIMERPROC) NULL);
            break;
        case WM_MOUSEMOVE:
        {
            mouse_move(hwnd);
            break;
        }
        case WM_TIMER:
            switch(state_of_game){
                case(MAINMENU):
                {
                    paint_mainmenu(hwnd, true);
                    break;
                }
                case(LOADED_LEVEL):
                {   
                    current_level->paintEverything();
                    break;
                }
                case(CREATE_LEVEL):
                {
                    current_create_level->paintEverything();
                    break;
                }
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_LBUTTONDOWN:
            mouse_click(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}







