// MenuGraphic.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "MenuGraphic.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

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
    LoadStringW(hInstance, IDC_MENUGRAPHIC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MENUGRAPHIC));

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MENUGRAPHIC));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDR_MENU1);
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
    static int shape,xLeft, yTop, xRight, yBottom;
    HDC hdc;
    POINT pt[3];
    static HPEN hpen;
    static HBRUSH hbrush;
    static HBRUSH hSolidBrush, hDiacrossBrush;
    static int stylePen;
    static COLORREF colorPen;
    switch (message)
    { 
    case WM_LBUTTONDOWN:
        xLeft = LOWORD(lParam);
        yTop = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:
        xRight = LOWORD(lParam);
        yBottom = HIWORD(lParam);
        hdc = GetDC(hWnd);
        hpen = CreatePen(stylePen, 1, colorPen);
        //hbrush = CreateSolidBrush(RGB(255, 255, 0));
        //SelectObject(hdc, GetStockObject(BLACK_PEN));
        hSolidBrush = CreateSolidBrush(RGB(255, 255, 0));
        hDiacrossBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(0, 255, 255));
        SelectObject(hdc, hpen);
        if (shape == ID_GRAPHIC_RECTANGLE) {
            //SelectObject(hdc, hpen);
            //SelectObject(hdc, hbrush);
            //SelectObject(hdc, hSolidBrush);
            Rectangle(hdc, xLeft, yTop, xRight, yBottom);
        }
        else {
            //SelectObject(hdc, GetStockObject(BLACK_PEN));
            if (shape == ID_GRAPHIC_ELIPSE) {
                //SelectObject(hdc, hDiacrossBrush);
                Ellipse(hdc, xLeft, yTop, xRight, yBottom);
            }
            if (shape == ID_GRAPHIC_TAMGIACCAN) {

                pt[0].x = xLeft + (xRight - xLeft) / 2;
                pt[0].y = yTop;
                pt[1].x = xLeft;
                pt[1].y = yBottom;
                pt[2].x = xRight;
                pt[2].y = yBottom;
                Polygon(hdc, pt, 3);
            }
        }


        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_BORDERCOLOR_BLUE:
                colorPen = RGB(0, 255, 255);
                break;
            case ID_BORDERCOLOR_RED:
                colorPen = RGB(255, 0, 0);
                break;
            case ID_BORDERCOLOR_PURPLE:
                colorPen = RGB(148, 0, 211);
                break;
            case ID_BORDERSTYLE_SOLID:
                stylePen = PS_SOLID;
                break;
            case ID_BORDERSTYLE_DOT:
                stylePen = PS_DOT;
                break;
            case ID_BORDERSTYLE_DASHDOT:
                stylePen = PS_DASHDOT;
                break;
            case ID_BORDERSTYLE_DASH:
                stylePen = PS_DASH;
                break;
            case ID_GRAPHIC_RECTANGLE:
            case ID_GRAPHIC_ELIPSE:
            case ID_GRAPHIC_TAMGIACCAN:
                shape = wmId;
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
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        DeleteObject(hpen);
        DeleteObject(hSolidBrush);
        DeleteObject(hDiacrossBrush);
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
