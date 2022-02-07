#include <string>
#include <vector>
#include <inttypes.h>

#pragma once
class Bitmap
{
public:
    Bitmap(std::string path);
    uint8_t * Data() { return _data.data(); };
    int Width() { return _width; };
    int Height() { return _height; };
private:
    std::vector<uint8_t> _data;
    int _width;
    int _height;
};

