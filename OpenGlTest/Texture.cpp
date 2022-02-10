#include "Texture.h"
#include <Windows.h>
#include <fstream>
#include <gl/GL.h>
#include <gl/glext.h>

PFNGLACTIVETEXTUREPROC glActiveTexture;

//--------------------------------------------------------------
Texture::Texture(std::string path)
{
    _height = 0;
    _width = 0;

    glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");

    GLuint texture;
    glGenTextures(1, &texture);
    _id = texture;

    Bind();


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NONE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NONE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    Load(path);

    Unbind();
}

//--------------------------------------------------------------
void Texture::Load(std::string path)
{
    std::wstring tmp = std::wstring(path.begin(), path.end());
    LPCWSTR lpcwstr = tmp.c_str();
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, lpcwstr, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    BITMAP bitmap;
    BITMAPINFO info;

    HDC dc = CreateCompatibleDC(NULL);
    std::memset(&info, 0, sizeof(BITMAPINFO));
    HBITMAP oldBitmap = (HBITMAP)SelectObject(dc, hBitmap);
    GetObject(hBitmap, sizeof(bitmap), &bitmap);

    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biWidth = _width = bitmap.bmWidth;
    info.bmiHeader.biHeight = _height = bitmap.bmHeight;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = bitmap.bmBitsPixel;
    info.bmiHeader.biCompression = BI_RGB;
    info.bmiHeader.biSizeImage = ((_width * bitmap.bmBitsPixel + 31) / 32) * 4 * _height;

    _data.resize(info.bmiHeader.biSizeImage);
    GetDIBits(dc, hBitmap, 0, _height, &_data[0], &info, DIB_RGB_COLORS);
    SelectObject(dc, oldBitmap);

    _height = std::abs(_height);

    //Convert pixel format
    for (int i = 0; i < _data.size() - 2; i += 4)
    {
        uint8_t tmp = _data[i];
        _data[i] = _data[i + 2];
        _data[i + 2] = tmp;
    }

    DeleteDC(dc);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data.data());
}

//--------------------------------------------------------------
void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);
}

//--------------------------------------------------------------
void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

