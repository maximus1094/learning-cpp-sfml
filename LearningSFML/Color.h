#pragma once

class Color
{
private:
    int R;
    int G;
    int B;
    int A;

public:
    Color();
    Color(int r, int g, int b, int a = 255);
};