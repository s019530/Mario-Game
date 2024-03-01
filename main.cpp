#include <iostream>
#include <windows.h>
#include <winuser.h>

#include "LevelOne.hpp"
#include "backgroundPainting.hpp"
#include "util.hpp"

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



typedef enum gameState{
    MAINMENU, 
    LEVELONE
}gameState;

int state_of_game;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    state_of_game = LEVELONE;


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
                switch(state_of_game)
                {
                    case(LEVELONE):
                        {
                            levelOneSetup(hwnd);
                            break;
                        }
                }

                RECT rect;
                GetWindowRect(hwnd, &rect);
                SetWindowPos(hwnd, 0, rect.left, rect.top, 1200, 800, 0);
                break;
            }
        /*case WM_KEYDOWN:
            {
                switch(state_of_game)
                {
                    case(LEVELONE):
                        {
                            levelOneKeyHandler(hwnd, wParam);
                            break;
                        }
                }
                break;
            }    */

        case WM_CREATE:
            SetTimer(hwnd, 0, 10, (TIMERPROC) NULL);
            break;
        

        case WM_TIMER:
            if(isKeyDown(CK_W))
            {
                levelOneKeyHandler(hwnd, CK_W);
            }
            else if(isKeyDown(CK_A))
            {
                levelOneKeyHandler(hwnd, CK_A);
            }
            else if(isKeyDown(CK_D))
            {
                levelOneKeyHandler(hwnd, CK_D);
            }
            else{
                paintBlueSkyBackground(hwnd);
                paintCharacter(hwnd);
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}







