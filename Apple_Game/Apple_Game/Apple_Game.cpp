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

bool mouseMoving = false;

void ctrlKey(bool pressed, int& keydown, int key)
{
    int keys[][2] = {
        {87, keydown_w}, {65, keydown_a}, {83, keydown_s}, {68, keydown_d},
        //{87, keydown_w}, {65, keydown_a}, {83, keydown_s}, {68, keydown_d},
        //{87, keydown_w}, {65, keydown_a}, {83, keydown_s}, {68, keydown_d},
        {32, keydown_space},
    };
    int nKey = sizeof(keys) / sizeof(int) / 2;

    if (pressed)
    {
        for (int i = 0; i < nKey; i++)
        {
            if (key == keys[i][0])
            {
                keydown |= keys[i][1];
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < nKey; i++)
        {
            if (key == keys[i][0])
            {
                keydown &= ~keys[i][1];
                break;
            }
        }
    }
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
    case WM_KEYDOWN:
        printf("WM_KEYDOWN %d\n", wParam);
        ctrlKey(true, keystat, wParam);
        ctrlKey(true, keydown, wParam);
        break;
    case WM_KEYUP:
        printf("WM_KEYUP %d\n", wParam);
        ctrlKey(false, keystat, wParam);
        break;
    case WM_LBUTTONDOWN:
        keyApp(iKeyStatBegan, convertCoord(LOWORD(lParam), HIWORD(lParam)));
        mouseMoving = true;
        break;
    case WM_LBUTTONUP:
        keyApp(iKeyStatEnded, convertCoord(LOWORD(lParam), HIWORD(lParam)));
        mouseMoving = false;
        break;
    case WM_MOUSEMOVE:
        keyApp(iKeyStatMoved, convertCoord(LOWORD(lParam), HIWORD(lParam)));
        break;

    case WM_MOVE:
        if (runApp)
            drawApp(iFPS::share()->update());
        break;
    case WM_SIZING:
    {
        RECT* rt = reinterpret_cast<LPRECT>(lParam);

        printf("WM_SIZING(%d, %d)\n",
            rt->right - rt->left,
            rt->bottom - rt->top);
        wParam;
    }
    break;
    case WM_SIZE:
        printf("WM_SIZE(%d, %d)\n", LOWORD(lParam), HIWORD(lParam));
        resize(LOWORD(lParam), HIWORD(lParam));
        if (runApp)
            drawApp(iFPS::share()->update());
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        printf("WM_DESTROY\n");
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void resize(int width, int height)
{
    float& dw = devSize.width;
    float& dh = devSize.height;
    float& x = viewport.origin.x;
    float& y = viewport.origin.y;
    float& vw = viewport.size.width;
    float& vh = viewport.size.height;

    // viewport
    float r0 = width / dw;
    float r1 = height / dh;
    if (r0 < r1)
    {
        // width 기준
        x = 0;
        vw = width;

        // vw : vh = dw : dh
        // dw * vh = vw * dh
        vh = vw * dh / dw;
        y = (height - vh) / 2;
    }
    else// if (r0 >= r1)
    {
        // height 기준
        y = 0;
        vh = height;

        // vw : vh = dw : dh
        vw = dw * vh / dh;
        x = (width - vw) / 2;
    }

    // vWidth : vHeight = devSize.width : devSize.height
}


iPoint convertCoord(float x, float y)
{
    iPoint p;
    p.x = (x - viewport.origin.x) / viewport.size.width * devSize.width;
    p.y = (y - viewport.origin.y) / viewport.size.height * devSize.height;
    //printf("(%.0f,%.0f) => (%.0f,%.0f)\n", x, y, p.x, p.y);
    return p;
}
