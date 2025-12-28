#include "../elementum/Elementum.hpp"
#include "../element/FontManager.hpp"

void Elementum::End()
{
    fontManager->clearFonts();
}