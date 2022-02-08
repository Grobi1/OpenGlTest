#pragma once
#include "Mat4.h"
//typedef void (*MouseMoveFunction)(float offsetX, float offsetY);
//typedef void (*MouseWheelFunction)(float delte);

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

