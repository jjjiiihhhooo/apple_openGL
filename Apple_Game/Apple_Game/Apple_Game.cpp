#include "Apple_Game.h"

#include "iStd.h"
#include "Game.h"

bool runApp;
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
    WCHAR szTitle[32] = L"APPLE_GAME";
    WCHAR szWindowClass[32] = L"AG";

    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLEGAME));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_HELLOUNREAL);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassExW(&wcex);

    runApp = false;
    int x = 0, y = 0, w = 640, h = 480;
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        0, 0, 1920, 1080, nullptr, nullptr, hInstance, nullptr);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
        
    loadApp(hWnd, loadGame, freeGame, drawGame, keyGame);

    MoveWindow(hWnd, x, y, w, h, true);

    MSG msg;
    runApp = true;
    while (runApp)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            drawApp(iFPS::share()->update());
        }
    }

    freeApp();

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        printf("WM_CREATE\n");
        break;
    case WM_CLOSE:
        printf("WM_CLOSE\n");
        if (MessageBox(NULL, L"종료하겠습니까?", L"종료하기", MB_YESNO) == IDYES)
        {
            printf("예\n");
            runApp = false;
        }
        else
        {
            printf("아니오 \n");
            return 0;
        }
        break;
    case WM_LBUTTONDOWN:
        //keyApp(iKeyStatBegan, )
        break;
    case WM_LBUTTONUP:
        //keyApp(iKeyStatEnded, )
        break;
    case WM_MOUSEMOVE:
        //keyApp(iKeyStatMoved, )
    case WM_DESTROY:
        printf("WM_DESTROY\n");
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

