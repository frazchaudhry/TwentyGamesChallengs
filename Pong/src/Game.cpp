#include "Game.hpp"
#include <SDL3/SDL_log.h>
#include <cstdlib>
#include <libraVideo.h>
#include <memory>
#include <vec2.h>

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
    if (!SDL_GL_SetSwapInterval(1)) {
        SDL_Log("Failed to disable Vsync.");
        return false;
    }

    Setup();

    return true;
}

void Game::Setup() {
    const LC_Color white = LC_Color_Create(255.0f, 255.0f, 255.0f, 1.0f);

    // Setup Walls
    entities.emplace("top", std::make_unique<Wall>("top", (LC_FRect){0, 0, static_cast<float>(screenWidth), 25},
        white, true));
    entities.emplace("bottom", std::make_unique<Wall>("bottom", (LC_FRect){0, static_cast<float>(screenHeight) - 25,
        static_cast<float>(screenWidth), 25}, white, true));

    // Setup Divider
    for (int32 i = 0, y = 40; y < 560; i++, y += 30) {
        Divider divider;
        divider.id = "divider-" + std::to_string(i+1);
        divider.transform = { 400 - 5 / static_cast<float>(2), static_cast<float>(y), 5, 20 };
        divider.color = LC_Color_Create(255.0f, 255.0f, 255.0f, 0.3f);

        entities.emplace(divider.id, std::make_unique<Divider>(divider.id, divider.transform, divider.color));
    }

    // Setup Paddles
    entities.emplace("leftPaddle", std::make_unique<Paddle>("leftPaddle", (LC_FRect){ 25,
        300 - Paddle::PADDLE_HEIGHT / static_cast<float>(2), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT }, white));
    entities.emplace("rightPaddle", std::make_unique<Paddle>("rightPaddle", (LC_FRect){ 800 - (25 + Paddle::PADDLE_WIDTH),
        300 - Paddle::PADDLE_HEIGHT / static_cast<float>(2), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT }, white));

    // Setup Ball
    entities.emplace("Ball", std::make_unique<Ball>("Ball", (LC_FRect){ 400 - Ball::BALL_LENGTH / static_cast<float>(2),
        300 - Ball::BALL_LENGTH / static_cast<float>(2),
        Ball::BALL_LENGTH , Ball::BALL_LENGTH}, white));
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

    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_SPACE) {
        state = GameState::ACTIVE;
    }

    entities["leftPaddle"]->ProcessInput(event);
    entities["rightPaddle"]->ProcessInput(event);

    return SDL_APP_CONTINUE;
}

void Game::Update(const double deltaTime) {
    const auto leftPaddle = static_cast<Paddle*>(entities["leftPaddle"].get());
    const auto rightPaddle = static_cast<Paddle*>(entities["rightPaddle"].get());
    const auto topWall = static_cast<Wall*>(entities["top"].get());
    const auto bottomWall = static_cast<Wall*>(entities["bottom"].get());
    const auto ball = static_cast<Ball*>(entities["Ball"].get());

    leftPaddle->Update(deltaTime, screenHeight);
    rightPaddle->Update(deltaTime, screenHeight);

    if (state == GameState::ACTIVE) {
        HandleCollisions(*ball, *leftPaddle, *rightPaddle, *topWall, *bottomWall);
        ball->Update(deltaTime, screenHeight);
    }
}

void Game::Render() {
    // Clear background
    LC_GL_ClearBackground(LC_Color_Create(0.0f, 0.0f, 0.5f, 1.0f));

    // Render Entities
    for (const auto &entity : entities) {
        entity.second->Render(renderer);
    }

    // Render Score
    RenderScore(player1Score, (vec3){ 400.0f - 60.0f, 110.0f, 0.0f });
    RenderScore(player2Score, (vec3){ 400.0f + 25.0f, 110.0f, 0.0f });


    // Swap buffers
    if (!LC_GL_SwapBuffer(renderer->window, errorLog)) {
        SDL_Log("%s\n", errorLog);
    }
}

void Game::RenderScore(const int32 score, const vec3 pos) const {
    char scoreString[2];
    snprintf(scoreString, 2, "%d", score);
    const LC_GL_Text scoreText = {
        .string = scoreString,
        .position { pos[0], pos[1], pos[2] },
        .color { 255.0f, 255.0f, 255.0f, 1.0f },
        .scale = 2.0f
    };

    LC_GL_RenderText(renderer, &scoreText);
}

void Game::Unload() const {
    LC_GL_FreeResources(renderer);

    LC_Arena_FreeAll(arena);
    delete arena;
    free(backingBuffer);
}

void Game::HandleCollisions(Ball &ball, const Paddle &leftPaddle, const Paddle &rightPaddle, const Wall &topWall,
                            const Wall &bottomWall) const {
    bool isCollided = false;
    if (ball.transform.x > static_cast<float>(screenWidth) / 2) {
        isCollided = LC_FRect_CheckCollisionAABB(&ball.transform, &rightPaddle.transform);
        if (isCollided) {
            ball.velocity[0] *= -1;
            ball.transform.x = rightPaddle.transform.x - ball.transform.w;
            glm_vec2_normalize(ball.velocity);
        }
    } else {
        isCollided = LC_FRect_CheckCollisionAABB(&ball.transform, &leftPaddle.transform);
        if (isCollided) {
            ball.velocity[0] *= -1;
            ball.transform.x = leftPaddle.transform.x + leftPaddle.transform.w + 1;
            glm_vec2_normalize(ball.velocity);
        }
    }
    if (ball.transform.y > static_cast<float>(screenHeight) / 2) {
        isCollided = LC_FRect_CheckCollisionAABB(&ball.transform, &bottomWall.transform);
        if (isCollided) {
            ball.velocity[1] *= -1;
            ball.transform.y = bottomWall.transform.y - ball.transform.h;
            glm_vec2_normalize(ball.velocity);
        }
    } else {
        isCollided = LC_FRect_CheckCollisionAABB(&ball.transform, &topWall.transform);
        if (isCollided) {
            ball.velocity[1] *= -1;
            ball.transform.y = topWall.transform.h;
            glm_vec2_normalize(ball.velocity);
        }
    }
}
