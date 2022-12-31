#include "ColorPalette.h"
#include "Rng.h"

ColorPalette::ColorPalette()
{
    Green = Color(0, 200, 83, 0);
    Orange = Color(255, 109, 0, 0);
    DeepPurple = Color(98, 0, 234, 0);

    colors.push_back(Green);
    colors.push_back(Orange);
    colors.push_back(DeepPurple);
}

Color ColorPalette::GetRandomColor()
{
    int randomIndex = ((int)(randomnumber() * 10000)) % colors.size() - 1;

    return colors[randomIndex];
}