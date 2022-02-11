#include <string>
#include <vector>
#include <inttypes.h>

#pragma once
class Texture
{
public:
    Texture(std::string path);
    ~Texture();
    uint8_t * Data() { return _data.data(); };
    int Width() { return _width; };
    int Height() { return _height; };

    void Bind();
    void Unbind();
private:
    void Load(std::string path);
    int _id;
    int _width;
    int _height;
    std::vector<uint8_t> _data;
};

