#ifndef GAME_HPP
#define GAME_HPP

#include <unordered_map>
#include <memory>
#include <string>

extern "C" {
#include <libraVideo.h>
}

#include "Entity.hpp"

#define LEFT_PADDLE_STARTING_POS (LC_FRect){ 25, 300 - Paddle::PADDLE_HEIGHT / 2.0f, \
    Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT }
#define RIGHT_PADDLE_STARTING_POS (LC_FRect){ 800 - (25 + Paddle::PADDLE_WIDTH), \
    300 - Paddle::PADDLE_HEIGHT / 2.0f, Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT }
#define BALL_STARTING_POS (LC_FRect){ 400 - Ball::BALL_LENGTH / 2.0f, 300 - Ball::BALL_LENGTH / 2.0f, \
        Ball::BALL_LENGTH , Ball::BALL_LENGTH}

enum class GameState {
    ACTIVE,
    PAUSED,
    START,
    END,
    MENU
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
    std::unordered_map<std::string, std::unique_ptr<Entity>> entities;
    int32 player1Score { 0 };
    int32 player2Score { 0 };
    std::string winner;
    GameState state { GameState::START };

    void RenderScore(int32 score, const vec3 pos) const;
    void HandleCollisions(Ball &ball, const Paddle &leftPaddle, const Paddle &rightPaddle, const Wall &topWall,
                          const Wall &bottomWall) const;
    void CalculateBallDirection(Ball &ball, const Paddle &paddle) const;
    void ResetGame();
};

#endif // GAME_HPP

