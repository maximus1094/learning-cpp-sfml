#include "Color.h"

// Default - hot pink
Color::Color()
{
    R = 255;
    G = 105;
    B = 180;
    A = 255;
}

Color::Color(int r, int g, int b, int a)
{
    R = r;
    G = g;
    B = b;
    A = a;
}