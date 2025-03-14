#pragma once

#include <vector>

#include "Color.h"

class ColorPalette
{
private:
    std::vector<Color> colors;

public:
    Color White;
    Color Green;
    Color Orange;
    Color DeepPurple;

    ColorPalette();

    Color GetRandomColor();
};