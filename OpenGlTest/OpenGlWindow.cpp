#include <Windows.h>
#include <math.h>
#include <windowsx.h>
#include "OpenGlWindow.h"
#include <gl/GL.h>
#include <algorithm>

//--------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static int initalX = 0;
    static int initalY = 0;
    static bool mouseDown = false;
    static int endX = 0;
    static int endY = 0;
    switch (msg)
    {
    case WM_CLOSE: DestroyWindow(hwnd); break;
    case WM_DESTROY: PostQuitMessage(0); break;
    case WM_SIZE: 
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        int min = min(width, height);

        glViewport((width - min) / 2, (height - min) / 2, min, min); break;
    }
    case WM_LBUTTONDOWN:
    {
        mouseDown = true;
        initalX = GET_X_LPARAM(lParam);
        initalY = GET_Y_LPARAM(lParam);
        break;
    }
    case WM_LBUTTONUP:
    {
        mouseDown = false;
        break;
    }
    case WM_MOUSEMOVE:
    {
        if (!mouseDown)
            break;
        int offsetX = initalX - GET_X_LPARAM(lParam);
        int offsetY = initalY - GET_Y_LPARAM(lParam);
        initalX = GET_X_LPARAM(lParam);
        initalY = GET_Y_LPARAM(lParam);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glRotatef(2, (float)-offsetY, (float)-offsetX, 0);
        glPushMatrix();
        break;
    }
    case WM_MOUSEWHEEL:
    {
        float zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glTranslatef(0, 0, zDelta / 500.0f);
        glPushMatrix();
    }
    default: return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

//--------------------------------------------------------------
OpenGlWindow::OpenGlWindow()
{
    WNDCLASS wc;
    memset(&wc, 0, sizeof(wc));
    LPCWSTR windowClass = L"Static";
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = windowClass;

    RegisterClass(&wc);

    HWND window = CreateWindow(windowClass, L"My Window", WS_OVERLAPPEDWINDOW, 0, 0, _width, _height, NULL, NULL, NULL, this);

    ShowWindow(window, SW_SHOW);
    PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
    memset(&pixelFormatDescriptor, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixelFormatDescriptor.nVersion = 1;
    pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pixelFormatDescriptor.cColorBits = 32;
    pixelFormatDescriptor.cDepthBits = 32;

    _drawingContext = GetDC(window);
    int pixelFormat = ChoosePixelFormat(_drawingContext, &pixelFormatDescriptor);
    SetPixelFormat(_drawingContext, pixelFormat, &pixelFormatDescriptor);
    HGLRC renderContext = wglCreateContext(_drawingContext);
    wglMakeCurrent(_drawingContext, renderContext);
    glViewport(0, 0, _width, _height);
}

//--------------------------------------------------------------
void OpenGlWindow::SwapBuffer()
{
    SwapBuffers(_drawingContext);
}

//--------------------------------------------------------------
void OpenGlWindow::Update()
{
    MSG msg;
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
