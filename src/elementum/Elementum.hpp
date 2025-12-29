#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

class FontManager;
class Window;
class StyleApplier;
class Painter;
class StyleComputer;

/**
 * @brief The Elementum class is the main engine responsible for managing UI rendering and layout,
 * coordinating font management, styling, painting, and event handling.
 *  It provides lifecycle methods for initialisation, running, and shutdown,
 *  as well as access to core manager components and window properties.
 *
 * Coordinates between font management, styling, painting, and event handling
 */
class Elementum
{
public:
    Elementum(float windowWidth, float windowHeight, SDL_Renderer *renderer);
    ~Elementum();

    // Lifecycle methods
    /*
     * @brief Initializes the engine and sets up the initial state
     */
    void Init();

    /*
     * @brief Runs the engine's main loop, updating and rendering UI elements
     */
    void Run();

    /*
     * @brief Cleans up resources and shuts down the engine
     */
    void End();

    /*
     * @brief Handles incoming SDL events
     * @param event Pointer to the SDL event to handle
     */
    void Event(SDL_Event *event);

    // Getters
    /*
     * @brief Gets initial window width that was set by the user
     */
    float GetInitialWindowWidth() const { return windowWidth; }
    /*
     * @brief Gets initial window height that was set by the user
     */
    float GetInitialWindowHeight() const { return windowHeight; }

    // Manager components
    std::unique_ptr<FontManager> fontManager;
    std::unique_ptr<Window> window;
    std::unique_ptr<StyleApplier> styleApplier;
    std::unique_ptr<Painter> painter;
    std::unique_ptr<StyleComputer> styleComputer;
    SDL_Renderer *renderer;

private:
    float windowWidth;
    float windowHeight;
};
