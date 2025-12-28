#include "Elementum.hpp"
#include "../element/window/Window.hpp"
#include "../element/FontManager.hpp"
#include "../element/style/style-applier/StyleApplier.hpp"
#include "../element/painter/Painter.hpp"
#include "../element/style/style-computer/StyleComputer.hpp"

Elementum::~Elementum() = default;
Elementum::Elementum(float windowWidth, float windowHeight, SDL_Renderer *renderer) : windowHeight(windowHeight), windowWidth(windowWidth)
{
    window = make_unique<Window>(0, 0, windowWidth, windowHeight);
    fontManager = make_unique<FontManager>();
    styleApplier = make_unique<StyleApplier>();
    painter = make_unique<Painter>();
    styleComputer = make_unique<StyleComputer>();

    this->renderer = renderer;
    painter->renderer = renderer;

    window->fontManager = fontManager.get();
    window->styleApplier = styleApplier.get();
    window->painter = painter.get();
};
