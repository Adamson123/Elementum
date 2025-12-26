#include "TextEditor.hpp"
#include "../element/window/Window.hpp"
#include "../element/FontManager.hpp"
#include "../element/style/StyleApplier.hpp"

TextEditor::~TextEditor() = default;
TextEditor::TextEditor(float windowWidth, float windowHeight) : windowHeight(windowHeight), windowWidth(windowWidth) {};
