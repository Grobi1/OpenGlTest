#include <Windows.h>
#include "OpenGlWindow.h"
#include <gl/GL.h>

//--------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE: DestroyWindow(hwnd); break;
    case WM_DESTROY: PostQuitMessage(0); break;
    case WM_SIZE: glViewport(0, 0, LOWORD(lParam), HIWORD(lParam)); break;
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
    //UpdateWindow(window);
    PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
    memset(&pixelFormatDescriptor, 0, sizeof(PIXELFORMATDESCRIPTOR));
    pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixelFormatDescriptor.nVersion = 1;
    pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;

    //pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;

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
