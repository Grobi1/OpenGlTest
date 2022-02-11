#pragma once
#include "Mat4.h"

class OpenGlWindow
{
public: 
	OpenGlWindow();
	void SwapBuffer();
	void Update();
	Mat4* _viewMatrix;
private:
	int _width = 512;
	int _height = 512;

	HDC _drawingContext;
};

