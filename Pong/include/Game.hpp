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
    PAUSED,
    END,
    TITLE
};

enum class TitleMenuState {
    TWOPLAYERS,
    ONEPLAYER,
    Exit
};

enum class PauseMenuState {
    Resume,
    TitleScreen
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
    LC_GL_Text title = {
        .string = const_cast<char*>("PONG"),
        .position = { 300.0f, 150.0f, 0.0f },
        .color = { 255.0f, 255.0f, 255.0f, 255.0f },
        .scale = 3.0f,
        .width = 0,
        .height = 0
    };
    LC_GL_Text playText = {
        .string = const_cast<char*>("2 PLAYERS"),
        .position = { 370.0f, 350.0f, 0.0f },
        .color = { 255.0f, 255.0f, 255.0f, 1.0f },
        .scale = 1.0f,
        .width = 0,
        .height = 0
    };
    LC_GL_Text playSinglePlayerText = {
        .string = const_cast<char*>("1 PLAYER"),
        .position = { 370.0f, 400.0f, 0.0f },
        .color = { 255.0f, 255.0f, 255.0f, 1.0f },
        .scale = 1.0f,
        .width = 0,
        .height = 0
    };
    LC_GL_Text exitText = {
        .string = const_cast<char*>("EXIT"),
        .position = { 370.0f, 450.0f, 0.0f },
        .color = { 255.0f, 255.0f, 255.0f, 1.0f },
        .scale = 1.0f,
        .width = 0,
        .height = 0
    };
    LC_GL_Text menuTitle = {
        .string = const_cast<char*>(""),
        .position = { 300.0f, 200.0f, 0.0f },
        .color = { 255.0f , 255.0f, 255.0f, 1.0f },
        .scale = 1.0f,
        .width = 0,
        .height = 0
    };
    LC_GL_Text option1 = {
        .string = const_cast<char*>("TITLE SCREEN"),
        .position = { 320.0f, 400.0f, 0.0f },
        .color = { 255.0f, 255.0f, 255.0f, 1.0f },
        .scale = 1.0f,
        .width = 0,
        .height = 0
    };
    LC_GL_Text option2 = {
        .string = const_cast<char*>("PLAY AGAIN"),
        .position = { 320.0f, 450.0f, 0.0f },
        .color = { 255.0f, 255.0f, 255.0f, 1.0f },
        .scale = 1.0f,
        .width = 0,
        .height = 0
    };
    std::string winnerText;
    GameState state { GameState::TITLE };
    TitleMenuState titleState { TitleMenuState::TWOPLAYERS };
    PauseMenuState pausedState { PauseMenuState::Resume };
    EndMenuState endState { EndMenuState::TitleScreen };

    SDL_AppResult ProcessTitleInput(const SDL_Event *event);
    SDL_AppResult ProcessGameInput(const SDL_Event *event);
    SDL_AppResult ProcessPausedInput(const SDL_Event *event);
    SDL_AppResult ProcessEndInput(const SDL_Event *event);
    void RenderScore(int32 score, const vec3 pos) const;
    void HandleCollisions();
    void CalculateBallDirection(const Paddle &paddle);
    void ResetGame();

public:
    bool isAi { false };

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

