#pragma once

class OpenGlWindow
{
public: 
	OpenGlWindow();
	void SwapBuffer();
	void Update();
private:
	int _width = 512;
	int _height = 512;

	HDC _drawingContext;
};

