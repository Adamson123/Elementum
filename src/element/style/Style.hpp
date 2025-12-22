#pragma once
#include <string>

using namespace std;

struct Color
{
    int r;
    int g;
    int b;
    int a;

    Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {};
};

class Style
{
public:
    Color color = {0, 0, 0, 0};
    int zIndex = 0;
};