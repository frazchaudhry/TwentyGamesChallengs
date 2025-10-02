#ifndef GAME_HPP
#define GAME_HPP

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
    START,
    END,
    TITLE
};

enum class TitleMenuState {
    Play,
    Exit
};

enum class EndMenuState {
    TitleScreen,
    PlayAgain
};

class Game {
    static constexpr int32 NUM_DIVIDERS = 18;
    const std::string GAME_TITLE { "PONG" };
    void *backingBuffer;
    char errorLog[1024];
    int32 screenWidth;
    int32 screenHeight;
    std::string fontFilePath;
    LC_Arena *arena;
    LC_GL_Renderer *renderer;
    Wall topWall;
    Wall bottomWall;
    Divider dividers[NUM_DIVIDERS];
    Paddle leftPaddle;
    Paddle rightPaddle;
    Ball ball;
    int32 player1Score { 0 };
    int32 player2Score { 0 };
    std::string winnerText;
    GameState state { GameState::TITLE };
    TitleMenuState titleState { TitleMenuState::Play };
    EndMenuState endState { EndMenuState::TitleScreen };

    void RenderScore(int32 score, const vec3 pos) const;
    void HandleCollisions();
    void CalculateBallDirection(const Paddle &paddle);
    void ResetGame();

public:
    Game() = default;
    ~Game() = default;

    bool Init(int32 width, int32 height);
    void Setup();
    SDL_AppResult ProcessInput(const SDL_Event *event);
    void Update(double deltaTime);
    void Render();
    void Unload() const;
};

#endif // GAME_HPP

