#include "TextEditor.hpp"
#include "../element/window/Window.hpp"
#include "../element/FontManager.hpp"
#include "../element/style/style-applier/StyleApplier.hpp"
#include "../element/painter/Painter.hpp"
#include "../element/style/style-computer/StyleComputer.hpp"

TextEditor::~TextEditor() = default;
TextEditor::TextEditor(float windowWidth, float windowHeight) : windowHeight(windowHeight), windowWidth(windowWidth) {};
