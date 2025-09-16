#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <string>
#include <vector>

extern "C" {
#include <libraVideo.h>
}

#include "Entity.hpp"

struct GameState {
};

class Game {
public:
    Game() = default;
    ~Game() = default;

    bool Init(int32 width, int32 height);
    void Setup();
    SDL_AppResult ProcessInput(const SDL_Event *event);
    void Update(float deltaTime);
    void Render();
    void Unload() const;

private:
    void *backingBuffer;
    char errorLog[1024];
    int32 screenWidth;
    int32 screenHeight;
    std::string fontFilePath;
    LC_Arena *arena;
    LC_GL_Renderer *renderer;
    std::vector<std::unique_ptr<Entity>> entities;
    int32 player1Score = 0;
    int32 player2Score = 0;

    void RenderScore(int32 score, const vec3 pos) const;
};

#endif // GAME_HPP

