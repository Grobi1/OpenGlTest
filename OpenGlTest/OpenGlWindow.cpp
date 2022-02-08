#include <Windows.h>
#include <math.h>
#include <windowsx.h>
#include "OpenGlWindow.h"
#include <gl/GL.h>
#include <algorithm>
#include "Mat4.h"


//--------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static OpenGlWindow * instance;
    static Mat4 viewMatrix;
    static int leftInitalX = 0;
    static int leftInitalY = 0;
    static bool leftMouseDown = false;
    static int rightInitalX = 0;
    static int rightInitalY = 0;
    static bool rightMouseDown = false;
    static int width;
    static int height;
    switch (msg)
    {
    case WM_CLOSE: DestroyWindow(hwnd); break;
    case WM_DESTROY: PostQuitMessage(0); break;
    case WM_SIZE: 
    {
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        int min = min(width, height);

        glViewport((width - min) / 2, (height - min) / 2, min, min); break;
    }
    case WM_LBUTTONDOWN:
    {
        leftMouseDown = true;
        leftInitalX = GET_X_LPARAM(lParam);
        leftInitalY = GET_Y_LPARAM(lParam);
        break;
    }
    case WM_LBUTTONUP:
    {
        leftMouseDown = false;
        break;
    }
    case WM_MOUSEMOVE:
    {
        if (leftMouseDown)
        {
            int offsetX = leftInitalX - GET_X_LPARAM(lParam);
            int offsetY = leftInitalY - GET_Y_LPARAM(lParam);
            leftInitalX = GET_X_LPARAM(lParam);
            leftInitalY = GET_Y_LPARAM(lParam);
            if (instance->_viewMatrix)
                instance->_viewMatrix->Translate(-offsetX / ((float)width / 2), offsetY / ((float)height / 2), 0);
        }
        if (rightMouseDown)
        {
            int offsetX = rightInitalX - GET_X_LPARAM(lParam);
            int offsetY = rightInitalY - GET_Y_LPARAM(lParam);
            rightInitalX = GET_X_LPARAM(lParam);
            rightInitalY = GET_Y_LPARAM(lParam);
            if (instance->_viewMatrix)
            {
                float length = sqrtf(offsetX * offsetX + offsetY * offsetX);
                instance->_viewMatrix->Rotate(length / 100000.f, offsetX / 100.f, offsetY / 100.f, 0);
            }
        }
        break;
    }
    case WM_RBUTTONDOWN:
    {
        rightMouseDown = true;
        rightInitalX = GET_X_LPARAM(lParam);
        rightInitalY = GET_Y_LPARAM(lParam);
        break;
    }
    case WM_RBUTTONUP:
    {
        rightMouseDown = false;
        break;
    }
    case WM_KEYDOWN:
    {
        if (!instance->_viewMatrix)
            break;
        if (wParam == VK_UP)
            instance->_viewMatrix->Translate(0, 0, 0.1);
        if (wParam == VK_DOWN)
            instance->_viewMatrix->Translate(0, 0, -0.1);
        break;
    }
    case WM_MOUSEWHEEL:
    {
        float zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        if (instance->_viewMatrix)
        {
            float zoom = zDelta / 120 / 100 + 1;
            instance->_viewMatrix->Scale(zoom, zoom, zoom);
        }
        break;
    }
    case WM_NCCREATE:
    {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        instance = static_cast<OpenGlWindow*>(lpcs->lpCreateParams);
        //DONT BREAK
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
