#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <memory>
#include <string>

extern "C" {
#include <libraVideo.h>
}

#include "Entity.hpp"

enum GameState {
};

enum PaddleState {
    STOP,
    UP,
    DOWN
};

class Game {
public:
    Game() = default;
    ~Game() = default;

    bool Init(int32 width, int32 height);
    void Setup();
    SDL_AppResult ProcessInput(const SDL_Event *event);
    void Update(double deltaTime);
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
    std::map<std::string, std::unique_ptr<Entity>> entities;
    int32 player1Score { 0 };
    int32 player2Score { 0 };
    const int32 PADDLE_WIDTH { 10 };
    const int32 PADDLE_HEIGHT { 50 };
    const int32 PADDLE_VELOCITY { 300 };
    PaddleState leftPaddleState { STOP };
    PaddleState rightPaddleState { STOP };

    void RenderScore(int32 score, const vec3 pos) const;
};

#endif // GAME_HPP

