// MouseExample.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "MouseExample.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HMENU hmenuPopUp;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MOUSEEXAMPLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MOUSEEXAMPLE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MOUSEEXAMPLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MOUSEEXAMPLE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   hmenuPopUp = LoadMenu(hInst, MAKEINTRESOURCE(IDC_MOUSEEXAMPLE));
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HMENU subMenu;
    static POINT pt[100];
    static POINT point;
    static POINT pts;
    static int count = 0, n = 1, s = 0;
    static TCHAR timeLeft[16];
    HDC hdc;
    static int stylePen;
    static bool isDrawing = false;
    static HPEN hpen;
    static HBRUSH hBrush;
    static COLORREF colorPen;
    switch (message)
    {
    case WM_LBUTTONDOWN:
        pt[count].x = LOWORD(lParam);
        pt[count].y = HIWORD(lParam);
        pts.x = LOWORD(lParam);
        pts.y = HIWORD(lParam);
        hdc = GetDC(hWnd);
        hpen = CreatePen(stylePen, 1, colorPen);
        SelectObject(hdc, hpen);
        SetPixel(hdc, pt[count].x, pt[count].y, RGB(255, 255, 0));
        ReleaseDC(hWnd,hdc);
        count++;
        isDrawing = true;
        break;
    case WM_RBUTTONDOWN:
        InvalidateRect(hWnd, NULL, true);
        count = 0;
        subMenu = GetSubMenu(hmenuPopUp, 2);
        point.x = LOWORD(lParam);
        point.y = HIWORD(lParam);
        ClientToScreen(hWnd, &point);
        TrackPopupMenu(subMenu, TPM_RIGHTBUTTON, point.x, point.y, 0, hWnd, NULL);
        break;
    case WM_LBUTTONDBLCLK:
        hdc = GetDC(hWnd);
        //hpen = CreatePen(stylePen, 1, colorPen);
        SelectObject(hdc, hpen);
        for (int i = 0;i < count - 1;i++) {
            MoveToEx(hdc, pt[i].x, pt[i].y, NULL);
            LineTo(hdc, pt[i+1].x, pt[i+1].y);
            /*for (int j = i + 1;j < count;j++) {
                MoveToEx(hdc, pt[i].x, pt[i].y, NULL);
                LineTo(hdc, pt[j].x, pt[j].y);
            }*/
        }
        ReleaseDC(hWnd, hdc);
        break;
    case WM_MOUSEMOVE:
        if (isDrawing) {
            int currentX = LOWORD(lParam);
            int currentY = HIWORD(lParam);
            HDC hdc = GetDC(hWnd);
            //hpen = CreatePen(stylePen, 1, colorPen);
            SelectObject(hdc, hpen);
            // Vẽ đoạn thẳng từ điểm bắt đầu đến điểm hiện tại
            MoveToEx(hdc, pts.x, pts.y, NULL);
            LineTo(hdc, currentX, currentY);
            ReleaseDC(hWnd, hdc);
            // Cập nhật lại điểm bắt đầu
            pts.x = currentX;
            pts.y = currentY;
        }
        break;
    case WM_LBUTTONUP:
        // Kết thúc quá trình vẽ khi thả chuột trái
        isDrawing = false;
  
        break;
    case WM_RBUTTONDBLCLK:
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_COLOR_BLUE:
                colorPen = RGB(32, 146, 123);
                break;
            case ID_COLOR_RED:
                colorPen = RGB(255, 0, 0);
                break;
            case ID_COLOR_YELLOW:
                colorPen = RGB(16, 235, 56);
                break;
            case ID_STYLE_DASH:
                stylePen = PS_DASH;
                break;
            case ID_STYLE_DOT:
                stylePen = PS_DOT;
                break;
            case ID_STYLE_SOLID:
                stylePen = PS_SOLID;
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            //PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            //EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
