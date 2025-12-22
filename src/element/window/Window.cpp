#include "Window.hpp"
#include <memory>
#include "../Element.hpp"
#include "../rectangle/Rectangle.hpp"

using namespace std;

Window::Window(float x, float y, float width, float height) : Element(x, y, width, height) {}

unique_ptr<Rectangle> Window::createRectangle()
{
    auto rectangle = make_unique<Rectangle>(0, 0, 0, 0);
    rectangle->window = this;
    return std::move(rectangle);
}

unique_ptr<Rectangle> Window::createRectangle(int x, int y, int width, int height)
{
    auto rectangle = make_unique<Rectangle>(x, y, width, height);
    rectangle->window = this;
    return std::move(rectangle);
}