#include <iostream>
#include "./Painter.hpp"
#include "../Element.hpp"
#include "../FontManager.hpp"

// Painter::~Painter() = default;

void Painter::paint(Element *element)
{
    if (!renderer)
    {
        throw runtime_error("No renderer was attached");
    }

    paintBackground(element);
    paintText(element);
    // paintBorder(element);
}

void Painter::paintBackground(Element *element)
{
    ComputedStyle computedStyle = element->computedStyle;
    Style style = element->style;

    // SDL_Log("Computed style width - %f", computedStyle.width);

    SDL_FRect rect = {computedStyle.x, computedStyle.y, computedStyle.width, computedStyle.height};
    SDL_SetRenderDrawColor(renderer, style.backgroundColor.r, style.backgroundColor.g, style.backgroundColor.b, style.backgroundColor.a);

    SDL_RenderFillRectF(renderer, &rect);
}

void Painter::paintText(Element *element)
{

    if (element->text.empty())
        return;

    Style style = element->style;
    TTF_Font *font = element->fontManager->get(style.fontFamily, style.fontSize);

    // 1️⃣ Render text to surface
    SDL_Surface *surface = TTF_RenderText_Solid(font, element->text.c_str(), style.color);
    if (!surface)
    {
        cout << "Surface error: " << TTF_GetError() << endl;
        return;
    }
    // 2️⃣ Convert surface to texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        cout << "Texture error: " << SDL_GetError() << endl;
        return;
    }

    // 3️⃣ Query texture size
    SDL_Rect dstRect;
    dstRect.x = element->computedStyle.x;
    dstRect.y = element->computedStyle.y;
    SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);

    // 4️⃣ Copy texture to renderer
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    // 5️⃣ Cleanup texture
    SDL_DestroyTexture(texture);
}

void Painter::paintBorder(Element *element)
{
    ComputedStyle rect = element->computedStyle;
    Style style = element->style;
    float borderWidth = rect.borderWidth;

    if (borderWidth)
    {

        // SDL_FRect rect = {computedStyle.x, computedStyle.y, computedStyle.width, computedStyle.height};

        // // Set border color (R, G, B, A)
        SDL_SetRenderDrawColor(renderer, style.borderColor.r, style.borderColor.g, style.borderColor.b, style.borderColor.a);

        // // Draw rectangle outline (border only)
        // SDL_RenderDrawRectF(renderer, &rect);
        SDL_FRect top = {
            rect.x,
            rect.y,
            rect.width,
            borderWidth};

        SDL_FRect bottom = {
            rect.x,
            rect.y + rect.height - borderWidth, // 👈 FIXED BUG
            rect.width,
            borderWidth};

        SDL_FRect left = {
            rect.x,
            rect.y,
            borderWidth,
            rect.height};

        SDL_FRect right = {
            rect.x + rect.width - borderWidth,
            rect.y,
            borderWidth,
            rect.height};

        SDL_RenderFillRectF(renderer, &top);
        SDL_RenderFillRectF(renderer, &bottom);
        SDL_RenderFillRectF(renderer, &left);
        SDL_RenderFillRectF(renderer, &right);
    }
}