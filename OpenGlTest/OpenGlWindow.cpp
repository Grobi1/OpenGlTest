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
    static int width;
    static int height;

    static float currentPositionX;
    static float currentPositionY;
    static float currentPositionZ;
    static float currentRotationX;
    static float currentRotationY;
    static float currentRotationZ;
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
            {
                currentRotationX += offsetY / (float)width;
                currentRotationY += -offsetX / (float)height;
            }
        }
        break;
    }
    case WM_KEYDOWN:
    {
        if (!instance->_viewMatrix)
            break;
        if (wParam == VK_UP)
            currentPositionZ += 0.1f;
        if (wParam == VK_DOWN)
            currentPositionZ -= 0.1f;
        if (wParam == VK_RIGHT)
            currentPositionX -= 0.1f;
        if (wParam == VK_LEFT)
            currentPositionX += 0.1f;
        if (wParam == VK_ESCAPE)
        {
            currentPositionX = 0.f;
            currentPositionY = 0.f;
            currentPositionZ = 0.f;
            currentRotationX = 0.f;
            currentRotationY = 0.f;
            currentRotationZ = 0.f;
        }
        break;
    }
    case WM_NCCREATE:
    {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
        instance = static_cast<OpenGlWindow*>(lpcs->lpCreateParams);
        break;
    }
    }
    if (instance && instance->_viewMatrix)
    {
        *instance->_viewMatrix = Mat4::Translate(currentPositionX, currentPositionY, currentPositionZ) * Mat4::RotateX(currentRotationX) * Mat4::RotateY(currentRotationY) * Mat4::RotateZ(currentRotationZ);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
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
