#include "Game.hpp"
#include <SDL3/SDL_log.h>
#include <cstdlib>
#include <libraVideo.h>
#include <memory>
#include <string>

bool Game::Init(const int32 width, const int32 height) {
    backingBuffer = malloc(100 * 1024);
    arena = new LC_Arena();
    LC_Arena_Initialize(arena, backingBuffer, 100 * 1024);

    renderer = static_cast<LC_GL_Renderer*>(LC_Arena_Allocate(arena, sizeof(LC_GL_Renderer)));
    this->screenWidth = width;
    this->screenHeight = height;
    LC_GL_InitializeRenderer(arena, renderer, width, height);

    fontFilePath = "assets/fonts/pong-score-extended.ttf";

    if (LC_GL_InitializeVideo(arena, renderer, "Pong", fontFilePath.c_str(), errorLog)) {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Could not initialize Video.%s", errorLog);
        return false;
    }

    // Disabling Vsync
    if (!SDL_GL_SetSwapInterval(0)) {
        SDL_Log("Failed to disable Vsync.");
        return false;
    }

    Setup();

    return true;
}

void Game::Setup() {
    const LC_Color white = LC_Color_Create(255.0f, 255.0f, 255.0f, 1.0f);

    // Setup Walls
    entities.push_back(std::make_unique<Wall>("top", (LC_Rect){0, 0, screenWidth, 25}, white, true));
    entities.push_back(std::make_unique<Wall>("bottom", (LC_Rect){0, screenHeight -25, screenWidth, 25}, white, true));

    // Setup Divider
    for (int32 i = 0, y = 40; y < 560; i++, y += 30) {
        Divider divider;
        divider.id = "divider-" + std::to_string(i+1);
        divider.transform = { 400 - 5 / 2, y, 5, 20 };
        divider.color = LC_Color_Create(255.0f, 255.0f, 255.0f, 0.3f);

        entities.push_back(std::make_unique<Divider>(divider.id, divider.transform, divider.color));
    }
}

SDL_AppResult Game::ProcessInput(const SDL_Event *event) {
    if (event->key.key == SDLK_ESCAPE ||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    if (renderer && event->type == SDL_EVENT_WINDOW_RESIZED) {
        SDL_GetWindowSize(renderer->window, &screenWidth, &screenHeight);
        LC_GL_FramebufferSizeCallback(screenWidth, screenHeight);
    }
    return SDL_APP_CONTINUE;
}

void Game::Update([[maybe_unused]]float deltaTime) {

}

void Game::Render() {
    // Clear background
    LC_GL_ClearBackground(LC_Color_Create(0.0f, 0.0f, 0.5f, 1.0f));

    // Render Entities
    for (const auto &entity : entities) {
        entity->Render(renderer);
    }

    // Render Score

    // Swap buffers
    if (!LC_GL_SwapBuffer(renderer->window, errorLog)) {
        SDL_Log("%s\n", errorLog);
    }
}

void Game::Unload() const {
    LC_GL_FreeResources(renderer);

    LC_Arena_FreeAll(arena);
    delete arena;
    free(backingBuffer);
}

Game::~Game() {

}
