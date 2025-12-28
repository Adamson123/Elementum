#include "../elementum/Elementum.hpp"
#include "../elementum/element/FontManager.hpp"

void Elementum::End()
{
    fontManager->clearFonts();
}