#include "Elementum.hpp"
#include "./element/window/Window.hpp"
#include "./element/FontManager.hpp"
#include "./element/style/style-applier/StyleApplier.hpp"
#include "./element/painter/Painter.hpp"
#include "./element/style/style-computer/StyleComputer.hpp"

Elementum::~Elementum() = default;
Elementum::Elementum(float windowWidth, float windowHeight, SDL_Renderer *renderer) : windowHeight(windowHeight), windowWidth(windowWidth)
{
    window = std::make_unique<Window>(0, 0, windowWidth, windowHeight);
    fontManager = std::make_unique<FontManager>();
    styleApplier = std::make_unique<StyleApplier>();
    painter = std::make_unique<Painter>();
    styleComputer = std::make_unique<StyleComputer>();

    this->renderer = renderer;
    painter->renderer = renderer;
    painter->fontManager = fontManager.get();

    window->styleApplier = styleApplier.get();
    window->painter = painter.get();
};
